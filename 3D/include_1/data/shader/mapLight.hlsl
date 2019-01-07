struct VS_IN
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
	float4 l : TEXCOORD1;
};

cbuffer cb0 : register(b0)
{
	float4x4  g_matWorld : packoffset(c0);
	matrix  g_matView : packoffset(c4);
	matrix  g_matProj : packoffset(c8);

	float  g_fTimer : packoffset(c12.x);
	float  y : packoffset(c12.y);
	float  z : packoffset(c12.z);
	float  w : packoffset(c12.w);

	float4 g_Color : packoffset(c13);
	matrix  g_matInvWorld : packoffset(c14);
};
cbuffer cb1: register(b1)
{
	float4 g_vLightDir: packoffset(c0);
	float4 g_vLightPos: packoffset(c1);
	float4 g_vEyeDir: packoffset(c2);
	float4 g_vEyePos: packoffset(c3);
	float4 g_vSpotInfo: packoffset(c4);
	float4 g_vLightColor: packoffset(c5);
};
Texture2D     g_txDiffuse : register(t0);
SamplerState  g_samLinear : register(s0);


VS_OUTPUT VS(VS_IN v)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	float4 vWorld = mul(float4(v.p, 1.0f), g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	vOut.p = vProj;
	vOut.n = mul(v.n, (float3x3)g_matInvWorld);
	vOut.c = v.c;// g_Color;

	vOut.l.xyz = vWorld.xyz;
	vOut.l.w = distance(vWorld.xyz, g_vLightPos.xyz);
	vOut.t = v.t;
	return vOut;
}

float4 Diffuse(float3 vNormal, float3 vWorld, float3 vLight, uint iNumLight, bool bDirectLight)
{
	float fIntensity = 0.0f;
	float fLuminance = 0.0;
	float4 cLightColor = float4(0, 0, 0, 1);
	for (uint iLight = 0; iLight < iNumLight; iLight++)
	{
		//float3 vLight = normalize(vWorld - g_vLightPos.xyz);
		float fLength = distance(vWorld, g_vLightPos.xyz);

		fIntensity = saturate(dot(-vLight, vNormal));
		if (bDirectLight == false)
		{
			fLuminance = smoothstep(
				fLength - 5,
				fLength,
				g_vLightPos.w);
		}
		else
		{
			fLuminance = 1.0f;
		}
		cLightColor += float4(0, 0, 1, 1) * fLuminance*fIntensity;
	}
	cLightColor.a = 1.0f;
	return cLightColor;
}

float4 Specular(float3 vNormal, float3 vWorld, float3 vLight, uint iNumLight, bool bDirectLight)
{
	float fIntensity = 0.0f;
	float fLuminance = 0.0;
	float4 cLightColor = float4(0, 0, 0, 1);
	for (uint iLight = 0; iLight < iNumLight; iLight++)
	{
		//float3 vLight = normalize(vWorld - g_vLightPos.xyz);
		float fLength = distance(vWorld, g_vLightPos.xyz);
#ifndef HALF_VECTOR
		float3 vReflect = reflect(g_vEyeDir.xyz, vNormal);
		fIntensity = saturate(dot(-vLight, vReflect));
		float fPower = pow(fIntensity, g_vEyeDir.w);
#else
#endif
		if (bDirectLight == false)
		{
			fLuminance = smoothstep(
				fLength - 5,
				fLength,
				g_vLightPos.w);
		}
		else
		{
			fLuminance = 1.0;
		}
		cLightColor += float4(1, 0, 0, 1) * fLuminance * fPower;
	}
	cLightColor.a = 1.0f;
	return cLightColor;
}
float4 ComputeSpotLight(float3 vVertexPos, float3 vVertexNormal, int nNumLights)
{
	float4 vSpotLightColor = float4(0, 0, 0, 1);
	for (int iLight = 0; iLight < nNumLights; iLight++)
	{
		float fInner = g_vSpotInfo.x;
		float fOutner = g_vSpotInfo.y;
		float fFalloff = g_vSpotInfo.z;
		float fRange = g_vSpotInfo.w;
		float4 vLight;
		vLight.xyz = normalize(vVertexPos - g_vLightPos.xyz);
		vLight.w = distance(vVertexPos, g_vLightPos.xyz);
		float fDot = dot(vLight.xyz, g_vLightDir.xyz);
		float fPhi = fInner - fOutner;

		// 거리에 따라 블랜딩
		float fIntensity = saturate(dot(vVertexNormal, -vLight.xyz));
		// 원 거리의 블랜딩
		float fLuminance = smoothstep(vLight.w - fFalloff, vLight.w, fRange);
		//내부콘
		if (fDot > fInner)
		{
			vSpotLightColor += float4(g_vLightColor.rgb* fLuminance/**fIntensity*/, 1.0f);
		}
		//외부콘
		else if (fDot > fOutner)
		{
			// 내부에서 외부 각의 블랜닝
			float fLuminanceB = 1.0f - (fInner - fDot) / fPhi;
			fLuminance = min(fLuminance, fLuminanceB);
			vSpotLightColor += float4(g_vLightColor.rgb * fLuminance/**fIntensity*/, 1.0f);
		}

	}
	return vSpotLightColor;
}
float4 PS(VS_OUTPUT v) : SV_Target
{
	float4 cAmbient = float4(0.2f,0.2f, 0.2f, 1.0f);

	// Point Lightting
	float3 vLight = normalize(v.l.xyz - g_vLightPos.xyz);
	float4 cDiffuse = Diffuse(v.n, v.l.xyz, vLight.xyz, 1, false);
	float4 cSpecular = Specular(v.n, v.l.xyz, vLight.xyz, 1, false);

	// Direction Lightting
	//vLight = g_vLightDir.xyz;
	//cDiffuse += Diffuse(v.n, v.l.xyz, vLight.xyz, 1, true);
	//cSpecular += Specular(v.n, v.l.xyz, vLight.xyz, 1, true);

	float4 cSpot = ComputeSpotLight(v.l.xyz, v.n, 1);
	float4 vTexColor = g_txDiffuse.Sample(g_samLinear, v.t);
	vTexColor = vTexColor * (cSpot + cSpecular + cDiffuse + cAmbient);
	vTexColor.a = 1.0f;
	return vTexColor;
}
float4 PSLine(VS_OUTPUT v) : SV_Target
{
	return v.c;
}
float4 PSColor(VS_OUTPUT v) : SV_Target
{
	return g_Color;
}
