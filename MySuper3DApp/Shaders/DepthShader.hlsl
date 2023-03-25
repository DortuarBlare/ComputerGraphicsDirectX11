#pragma pack_matrix(row_major)

struct PS_IN {
	float4 pos : SV_POSITION;
 	float4 tex : TEXCOORD;
    float4 normal : NORMAL;
};

struct VS_IN {
	float4 pos : POSITION0;
    float4 tex : TEXCOORD0;
    float4 normal : NORMAL0;
};

cbuffer ConstBufMatrix : register(b0) {
    float4x4 worldViewProjMatrix;
};

float4 PSMain(PS_IN input) : SV_Target {
    float depth = input.pos.z / input.pos.w;
    return float4(depth, depth, depth, 1);
}

PS_IN VSMain(VS_IN input) {
    PS_IN output = (PS_IN) 0;
    output.pos = mul(float4(input.pos.xyz, 1.0f), worldViewProjMatrix);
    return output;
}
