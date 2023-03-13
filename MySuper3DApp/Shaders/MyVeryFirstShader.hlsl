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
    float4x4 invertedMatrix;
};

cbuffer SceneConstBuf : register(b1) {
    float4 lightDirection;
    float4 lightColor;
    float4 viewDirectionSpecular;
};

Texture2D DiffuseMap : register(t0);
SamplerState Sampler : register(s0);

float4 PSMain(PS_IN input) : SV_Target {
    float4 ambient = lightColor.w * float4(lightColor.xyz, 1.0f);
    float4 tex = DiffuseMap.SampleLevel(Sampler, input.tex.xy, 0);

    float4 norm = normalize(input.normal);
    float diff = max(dot(norm, lightDirection), 0.0f);
    float4 diffuse = diff * float4(lightColor.xyz, 1.0f);

    float4 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirectionSpecular.xyz, reflectDir.xyz), 0.0f), 16);
    float4 specular = viewDirectionSpecular.w * spec/* * float4(viewDirectionSpecular.xyz, 1.0f)*/;

    float4 result = (ambient + diffuse + specular) * tex;
	
    return float4(result.xyz, 1.0f);
}

PS_IN VSMain(VS_IN input) {
    PS_IN output = (PS_IN) 0;
    
    output.pos = mul(float4(input.pos.xyz, 1.0f), worldViewProjMatrix);
    output.tex = input.tex;
    output.normal = mul(float4(input.normal.xyz, 0.0f), invertedMatrix);
	
    return output;
}
