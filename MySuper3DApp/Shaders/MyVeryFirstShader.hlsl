struct PS_IN {
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

struct VS_IN {
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

struct ConstData {
    float4 offset;
};

struct ConstDataMatrix {
    float4x4 offsetMatrix;
};

cbuffer ConstBuf : register(b0) {
    ConstData constData;
};

cbuffer ConstBufMatrix : register(b1) {
    ConstDataMatrix constDataMatrix; // MeshData
};


float4 PSMain(PS_IN input) : SV_Target {
    float4 col = input.col;
    
    return col;
}

PS_IN VSMain(VS_IN input) {
    PS_IN output = (PS_IN) 0;
	
    output.pos = input.pos + constData.offset; // multiply (float4(input.pos.xyz, 1.0f), MeshData.Transform)
    output.col = input.col;
	
    return output;
}
