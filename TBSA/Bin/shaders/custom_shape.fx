#include "common.fx"

struct VertexInputType
{
    float4 position : POSITION;
    float4 color : TEXCOORD0;
	float2 tex : TEXCOORD1;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 color : TEXCOORD0;
	float textureMappingData : TEXCOORD1;
	float2 tex : TEXCOORD2;
};

float2x2 ComputeParticleRotation(float aRotation)
{ 
	float c = cos(aRotation);
	float s = sin(aRotation);
	return float2x2(c, -s, s, c);
}

Texture2D shaderTexture : register( t0 );

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	float2 Resolution = myResolution.xy;
	float ratio = Resolution.y / Resolution.x;

    // Change the position vector to be 4 units for proper matrix calculations.
	
    input.position.w = 1.0f;	
	//input.position.x *= ratio;
	input.position.xy *= myRotationAndSizeCustom.yz;
	
	float2x2 theRotation = ComputeParticleRotation(myRotationAndSizeCustom.x);
	input.position.xy = mul(input.position.xy, theRotation);
	input.position.xy += myPositionCustom;
	
    // Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = input.position;
	output.tex = input.tex;
    
	output.color = input.color;
	output.textureMappingData = myRotationAndSizeCustom.w;
	
    return output;
}

float4 CalculateLight(PixelInputType input)
{
	float4 DiffuseColor = input.color;
	float4 AmbientColor = float4(0.5f, 0.5f, 0.5f, 0.1f);
	float4 AmbientLight = AmbientColor * DiffuseColor;
	
	float2 Resolution = myResolution.xy;
	
	
	float4 finalColor = DiffuseColor + myAmbience;
	finalColor.a = DiffuseColor.a;
	for(uint i=0; i< myNumberOfLights; i++)
	{
		float2 direction = float2(myLights[i].myPosition.xy - (input.position.xy / Resolution.xy));	
		direction.x *= (Resolution.x / Resolution.y);
		
		float theLength = length(direction);
		theLength = normalize(theLength);
		
		float distance = (1 / length(direction)) * myLights[i].myPosition.w;
		finalColor += (DiffuseColor * distance * myLights[i].myLightColor) * myLights[i].myPosition.z;
		

	}
	return finalColor + AmbientLight;
}

SamplerState SampleType;
float4 PShader(PixelInputType input) : SV_TARGET
{
	float4 Diffuse = shaderTexture.Sample(SampleType, input.tex) * input.color;
	input.color = Diffuse;
	if(input.textureMappingData > 0.0f)
	{
		return CalculateLight(input);

	}
    return input.color;
}