Texture2D		g_txDiffuse : register(t0);
SamplerState	g_samPoint : register(s0);

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
};
struct PS_INPUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

cbuffer cb0
{
	float4x4  g_matWorld : packoffset(c0);
	matrix  g_matView : packoffset(c4);
	matrix  g_matProj : packoffset(c8);

	float  g_fTimer : packoffset(c12.x);
	float  y : packoffset(c12.y);
	float  z : packoffset(c12.z);
	float  w : packoffset(c12.w);

	float4 g_Color : packoffset(c13);
};



VS_OUTPUT VS(VS_IN v)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	float4 vWorld = mul(float4(v.p,1.0f), g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	vOut.p = vProj.xyzz;
	vOut.n = v.n;
	vOut.c = v.c;// g_Color;
	vOut.t = v.t;
	return vOut;
}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT vIn) : SV_Target
{
	return g_txDiffuse.Sample(g_samPoint, vIn.t);
}
