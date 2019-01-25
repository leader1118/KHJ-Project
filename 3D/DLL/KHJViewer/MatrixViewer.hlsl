Texture2D g_txDiffuse : register(t0);
SamplerState samLinear : register(s0);

cbuffer cb0
{
    float4x4 g_matWorld : packoffset(c0);
    float4x4 g_matView : packoffset(c4);
    float4x4 g_matProj : packoffset(c8);
    float4 g_MeshColor : packoffset(c12);
};
struct TessedVertex
{
    uint BaseTriID;
    float2 bc;
};
Buffer<float4> g_BufferBoneWorld : register(t0);
StructuredBuffer<TessedVertex> g_TessedVertices : register(t1);

struct VS_OUTPUT
{
    float4 p : SV_POSITON;
    float4 c : COLORO;
    float2 t : TEXCOORDO;
};
struct PNC_VS_INPUT
{
    float4 p : POSITION;
    float3 n : NORMAL;
    float4 c : COLORO;
};

VS_OUTPUT VS(PNC_VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.p = mul(input.p, g_matWorld);
    output.p = mul(output.p, g_matView);
    output.p = mul(output.p, g_matProj);
    output.c = g_MeshColor;
    return output;
}
float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.c * float4(1.0f, 0.0f, 0.0f, 1.0f);
}