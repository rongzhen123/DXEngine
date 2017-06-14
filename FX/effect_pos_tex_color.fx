//***************************************************************************************
// color.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject
{
	float4x4 gWorldViewProj;
};
// Nonnumeric values cannot be added to a cbuffer.
Texture2D gDiffuseMap;
//Texture2D gNormalMap;

SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VertexIn
{
	float3 PosL  : POSITION;
	float2 Tex   : TEXCOORD;
	float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
	float2 Tex   : TEXCOORD;
	float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	//Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.Tex = vin.Tex;
	vout.Color = vin.Color;
	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 Color;
	Color = gDiffuseMap.Sample(samLinear, pin.Tex) * pin.Color;

	return Color;
}

technique11 PosTexColorTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
