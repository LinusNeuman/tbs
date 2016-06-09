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

	Diffuse.x *= 2.0;
	Diffuse.y *= 0.0;
	Diffuse.z *= 2.0;
	//Diffuse = float4(Diffuse.x, Diffuse.y, Diffuse.z * 2.0, Diffue.w);

	return Diffuse;
}