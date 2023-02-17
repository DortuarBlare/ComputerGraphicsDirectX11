struct PS_IN {
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

struct VS_IN {
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

float4 PSMain(PS_IN input) : SV_Target {
    float4 col = input.col;
//#ifdef TEST
//	if (input.pos.x > 400) col = TCOLOR;
//#endif
    return col;
}

PS_IN VSMain(VS_IN input) {
    PS_IN output = (PS_IN) 0;
	
    output.pos = input.pos;
    output.col = input.col;
	
    return output;
}