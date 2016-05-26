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
	float4 Diffuse = shaderTextures[DIFFUSE_MAP].Sample(SampleType, input.tex);

	//Sets color to greyscale
	float averageColor = (Diffuse.x + Diffuse.y + Diffuse.z) / 3.0f;
	averageColor *= 0.2f;

	Diffuse = float4(Diffuse.x/2.f, Diffuse.y, Diffuse.z, Diffuse.w);

	return Diffuse;
}