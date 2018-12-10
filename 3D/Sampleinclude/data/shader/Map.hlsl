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
struct GS_OUTPUT
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
Texture2D     g_txDiffuse : register(t0);
SamplerState  g_samLinear : register(s0);

VS_OUTPUT VS(VS_IN v)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	float4 vWorld = mul(float4(v.p,1.0f), g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	vOut.p = vProj;
	vOut.n = v.n;
	vOut.c = v.c;// g_Color;
	vOut.t = v.t;
	return vOut;
}
VS_OUTPUT VS_NoMatrix(VS_IN v)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;	
	vOut.p = float4(v.p, 1.0f);
	vOut.n = v.n;
	vOut.c = v.c;// g_Color;
	vOut.t = v.t;
	return vOut;
}
float4 PS(VS_OUTPUT v) : SV_Target
{
	float4 vTexColor = g_txDiffuse.Sample(g_samLinear, v.t);
	return vTexColor * v.c;
}
float4 PSLine(VS_OUTPUT v) : SV_Target
{
	return v.c;
}
float4 PSColor(VS_OUTPUT v) : SV_Target
{
	return g_Color;
}
// ��Į ������ ũ�⸦ ����ȭ�Ͽ� 1�� �����.
GS_OUTPUT NormalizeVertex(GS_OUTPUT Vertex)
{
	GS_OUTPUT newvertex= (GS_OUTPUT)0;
	newvertex.p = float4(normalize(Vertex.p.xyz),1);
	// ������ ������ �߽����� �ϴ� �븻 ���Ͱ� �ȴ�.
	newvertex.n = normalize(Vertex.p.xyz);
	newvertex.c = Vertex.c;
	newvertex.t = Vertex.t;

	float4 vWorld = mul(float4(newvertex.p.xyz, 1.0f), g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	newvertex.p = vProj;
	return newvertex;
}
void TriAppend(GS_OUTPUT V0, GS_OUTPUT V1, GS_OUTPUT V2, 
	inout TriangleStream<GS_OUTPUT> TriStream)
{
	TriStream.Append(NormalizeVertex(V0));
	TriStream.Append(NormalizeVertex(V1));
	TriStream.Append(NormalizeVertex(V2));
	// �ﰢ�� ������ ��Ʈ������ ������� �Ѵ�.		
	TriStream.RestartStrip();
}

[maxvertexcount(12)]
void GS(triangle VS_OUTPUT input[3],
	inout TriangleStream<GS_OUTPUT> triStream)
{
	// ���̽��� ������ ���Ѵ�.
	GS_OUTPUT Center0, Center1, Center2;
	Center0.p = float4((input[0].p.xyz + input[1].p.xyz) / 2.0, 1.0f);
	Center0.n = (input[0].n.xyz + input[1].n.xyz) / 2.0;
	Center0.c = (input[0].c + input[1].c) / 2.0;
	Center0.t = (input[0].t.xy + input[1].t.xy) / 2.0;

	Center1.p = float4((input[1].p.xyz + input[2].p.xyz) / 2.0, 1.0f);
	Center1.n = (input[1].n.xyz + input[2].n.xyz) / 2.0;
	Center1.c = (input[1].c + input[2].c) / 2.0;
	Center1.t = (input[1].t.xy + input[2].t.xy) / 2.0;

	Center2.p = float4((input[0].p.xyz + input[2].p.xyz) / 2.0, 1.0f);
	Center2.n = (input[0].n.xyz + input[2].n.xyz) / 2.0;
	Center2.c = (input[0].c + input[2].c) / 2.0;
	Center2.t = (input[0].t.xy + input[2].t.xy) / 2.0;

	TriAppend(input[0], Center0, Center2, triStream);
	TriAppend(Center0, input[1], Center1, triStream);
	TriAppend(input[2], Center2, Center1, triStream);
	TriAppend(Center0, Center1, Center2, triStream);

	/*float3 cPos = (input[0].p.xyz +	input[1].p.xyz +input[2].p.xyz) / 3.0f;
	float4 cColor = (input[0].c +input[1].c +input[2].c) / 3.0f;
	float3 cNormal = (input[0].n +input[1].n +	input[2].n) / 3.0f;
	float2 cTex = (input[0].t +	input[1].t +input[2].t) / 3.0f;

	GS_OUTPUT newVertex=(GS_OUTPUT)0;

	for (int i = 0; i < 3; i++)
	{		
		newVertex = NormalizeVertex(input[i]);
		float4 vWorld = mul(float4(newVertex.p.xyz, 1.0f), g_matWorld);
		float4 vView = mul(vWorld, g_matView);
		float4 vProj = mul(vView, g_matProj);
		newVertex.p = vProj;
		triStream.Append(newVertex);

		int iNext = (i + 1) % 3;
		newVertex = NormalizeVertex(input[iNext]);
		vWorld = mul(float4(newVertex.p.xyz, 1.0f), g_matWorld);
		vView = mul(vWorld, g_matView);
		vProj = mul(vView, g_matProj);
		newVertex.p = vProj;
		triStream.Append(newVertex);

		newVertex.p = normalize(float4(cPos,1));
		newVertex.c = cColor;
		newVertex.n = newVertex.p.xyz;
		newVertex.t = cTex;
		vWorld = mul(float4(newVertex.p.xyz, 1.0f), g_matWorld);
		vView = mul(vWorld, g_matView);
		vProj = mul(vView, g_matProj);
		newVertex.p = vProj;
		triStream.Append(newVertex);

		triStream.RestartStrip();
	}
	triStream.RestartStrip();*/
}