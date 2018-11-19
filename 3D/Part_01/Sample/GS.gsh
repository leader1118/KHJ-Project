struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
};
struct GS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	uint vp : SV_ViewportArrayIndex;
};
cbuffer cb0
{
	float  g_fTimer : packoffset(c0.x);
	float  active : packoffset(c0.y);
	float  z : packoffset(c0.z);
	float  w : packoffset(c0.w);
};

[maxvertexcount(9)]
void GS( triangle VS_OUTPUT input[3],
	     inout TriangleStream<GS_OUTPUT> triStream)
{
	float3 cPos = (input[0].p.xyz +
		input[1].p.xyz +
		input[2].p.xyz) / 3.0f;
	float4 cColor = (input[0].c +
		input[1].c +
		input[2].c ) / 3.0f;

	GS_OUTPUT newVertex;
	newVertex.vp = active;

	for (int i = 0; i < 3; i++)
	{
		newVertex.p = input[i].p;
		newVertex.c = input[i].c;
		triStream.Append(newVertex);

		int iNext = (i + 1) % 3;
		newVertex.p = input[iNext].p;
		newVertex.c = input[iNext].c;
		triStream.Append(newVertex);

		newVertex.p = float4(cPos,1.0f);
		newVertex.c = float4(0,0,0,1);
		triStream.Append(newVertex);

		triStream.RestartStrip();
	}
	triStream.RestartStrip();
}