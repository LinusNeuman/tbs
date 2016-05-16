#include "common.fx"

SamplerState SampleType;

Texture2D shaderTextures[2] : register( t1 );
Texture2D shaderTextureCustom : register( t4 );

#define DIFFUSE_MAP 0

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : TEXCOORD1;
	float textureMappingData : TEXCOORD2;
};

float4 PShader(PixelInputType input) : SV_TARGET
{
	float4 Diffuse = shaderTextureCustom.Sample(SampleType, input.tex) * input.color;
	return Diffuse;
}