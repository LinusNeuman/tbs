#include "common.fx"

Texture2D shaderTexture;

SamplerState SampleType
{
	Filter = MIN_MAG_MIP_POINT;
    AddressU = Wrap;
    AddressV = Wrap;
};

struct VertexInputType
{
    float4 position : POSITION;
	uint4 myVertexIndex : TEXCOORD0;
    float2 tex : TEXCOORD1;
	float2 instancePosition : TEXCOORD2;
	float4 instanceColor : TEXCOORD3;
	float4 instanceRotationAndSize : TEXCOORD4;
	float4 instanceUV : TEXCOORD5;
	float4 instancePivot : TEXCOORD6;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float4 color : TEXCOORD1;
	float totalSize : TEXCOORD2;
};

float2x2 ComputeParticleRotation(float aRotation)
{ 
	float c = cos(aRotation);
	float s = sin(aRotation);
	return float2x2(c, -s, s, c);
}

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;
	
	input.position.x -= input.instancePivot.x;
	input.position.y += input.instancePivot.y;
	    
	input.position.xy *= input.instanceRotationAndSize.yz;
		
	float2x2 theRotation = ComputeParticleRotation(input.instanceRotationAndSize.x);
	input.position.xy = mul(input.position.xy, theRotation);	
	
	input.position.x += input.instancePosition.x;
    input.position.y += input.instancePosition.y;
	
	float2 Resolution = myResolution.xy;
	float ratio = Resolution.y / Resolution.x; 
	
	output.position = input.position;
	output.position.x *= ratio;
		    
	output.tex.x = input.instanceUV.x + (input.tex.x * input.instanceUV.z);
	output.tex.y = input.instanceUV.y + (input.tex.y * input.instanceUV.w);
	//output.tex.y -= 0.0025f;
	
	output.color = input.instanceColor;
	output.totalSize = input.instanceRotationAndSize.y;
	
    return output;
}

float4 PShader(PixelInputType input) : SV_TARGET
{
	float dist = shaderTexture.Sample( SampleType, input.tex).r;
	return float4(input.color.rgb, dist); 
}
