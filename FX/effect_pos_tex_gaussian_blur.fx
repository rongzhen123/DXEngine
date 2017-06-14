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
float weight[5] = { 0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162 };
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
	//float4 Color;
	//Color = gDiffuseMap.Sample(samLinear, pin.Tex);
	//return Color;
	float3 Color;
float width, height;
uint numberofsamples;
float2 TexCoord = pin.Tex;
gDiffuseMap.GetDimensions(0, width, height, numberofsamples);
float2 tex_offset = 1.0 / float2(width, height);
Color = gDiffuseMap.Sample(samLinear, pin.Tex).rgb;
for (int i = 0; i < 5; ++i)
{
	Color += gDiffuseMap.Sample(samLinear, TexCoord + float2(tex_offset.x * i,0)).rgb * weight[i];
	Color += gDiffuseMap.Sample(samLinear, TexCoord - float2(tex_offset.x * i, 0)).rgb * weight[i];
	Color += gDiffuseMap.Sample(samLinear, TexCoord + float2(0,tex_offset.y * i)).rgb * weight[i];
	Color += gDiffuseMap.Sample(samLinear, TexCoord - float2(0,tex_offset.y * i)).rgb * weight[i];
}

/*int Samples = 128;

float Intensity = 0.125, Decay = 0.96875;
float2 Direction = float2(0.5, 0.5) - pin.Tex;
Direction /= Samples;

for (int Sample = 0; Sample < 56; Sample++)
{
Color += gDiffuseMap.Sample(samLinear, TexCoord).rgb * Intensity;
Intensity *= Decay;
TexCoord += Direction;
}*/
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
