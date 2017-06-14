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

SamplerState samLinear
{
	//Filter = MIN_MAG_MIP_LINEAR;
	Filter = ANISOTROPIC;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VertexIn
{
	float3 PosL  : POSITION;
	float2 Tex   : TEXCOORD;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
	float2 Tex   : TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	//Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.Tex = vin.Tex;
	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float3 Color;
	int Samples = 128;
	float2 TexCoord = pin.Tex;
	float Intensity = 0.125, Decay = 0.96875;
	float2 Direction = float2(0.5, 0.5) - pin.Tex;
	Direction /= Samples;
	Color = gDiffuseMap.Sample(samLinear, pin.Tex).rgb;
	for (int Sample = 0; Sample < Samples; Sample++)
	{
		Color += gDiffuseMap.Sample(samLinear, TexCoord).rgb * Intensity;
		Intensity *= Decay;
		TexCoord += Direction;
	}
	float4 FragColor = float4(Color, 1.0);
	return FragColor;
}

technique11 PosTexTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
