struct PS_IN {
	float4 pos : SV_POSITION;
 	float4 tex : TEXCOORD;
};

struct VS_IN {
	float4 pos : POSITION0;
    float4 tex : TEXCOORD0;
};

cbuffer ConstBufMatrix : register(b0) {
    float4x4 transform;
};

Texture2D DiffuseMap : register(t0);
SamplerState Sampler : register(s0);

float4 PSMain(PS_IN input) : SV_Target {
    float4 tex = DiffuseMap.SampleLevel(Sampler, input.tex.xy, 0);
    
    return tex;
}

PS_IN VSMain(VS_IN input) {
    PS_IN output = (PS_IN) 0;
	
    output.pos = mul(input.pos, transform);
    output.tex = input.tex;
	
    return output;
}
