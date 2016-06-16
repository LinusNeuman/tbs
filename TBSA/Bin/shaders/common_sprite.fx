#include "common.fx"

SamplerState SampleType;

#define DIFFUSE_MAP 0
#define NORMAL_MAP 1

Texture2D shaderTextures[2] : register( t1 );

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 color : TEXCOORD1;
	float textureMappingData : TEXCOORD2;
};

float2x2 ComputeParticleRotation(float aRotation) 
{
	float c = cos(aRotation); 
	float s = sin(aRotation);
	return float2x2(c, -s, s, c);
}

float4 PShader(PixelInputType input) : SV_TARGET
{
	float2 Resolution = myResolution.xy;

	float4 Diffuse = shaderTextures[DIFFUSE_MAP].Sample(SampleType, input.tex) * input.color;
	float3 Normal = normalize((shaderTextures[NORMAL_MAP].Sample(SampleType, input.tex).xyz * 2.0f) - 1.0f);
	
	float4 noise = myNoiseTexture.Sample(SampleType, input.tex);

	float3 AmbientColor = Diffuse.xyz * myAmbience;
	float3 DirectColor = float3(0, 0, 0);
	for (unsigned int index = 0; index < myNumberOfLights; index++)
	{
		float Intensity = myLights[index].myPosition.z;
		float Falloff = myLights[index].myPosition.w;

		float2 difference = float2((myLights[index].myPosition.xy - input.position.xy) / Resolution.xy);
		difference.x *= (Resolution.x / Resolution.y);
		difference.y *= -1; 

		float distance = length(difference); 

		float linearAttenuation = saturate((Falloff - distance) / Falloff);
		float physicalAttenuation = 1.0f/(1.0f + distance);
		float totalAttenuation = linearAttenuation * physicalAttenuation;

		float3 direction = normalize(float3(difference.xy, (Falloff / 2)));

		float lambert = dot(direction, Normal); 

		DirectColor += Diffuse.xyz * Intensity * totalAttenuation * myLights[index].myLightColor.xyz * lambert;
	} 
	
	
	return float4(AmbientColor + DirectColor, Diffuse.w);
}