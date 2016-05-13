#include "common_sprite.fx"

// Our custom data
cbuffer ObjectBufferCustom : register(b5) 
{
	float4 myCustomData;
};

// Don't touch
struct VertexInputType
{
    float4 position : POSITION; 
    float2 tex : TEXCOORD0;
};

// You can now use the variable myCustomData below!
PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
	
	float2 Resolution = myResolution.xy;
	float ratio = Resolution.y / Resolution.x;

    // Change the position vector to be 4 units for proper matrix calculations.
	
    input.position.w = 1.0f;
	
	input.position.x -= myPivot.x;
	input.position.y += myPivot.y;
	
	input.position.xy *= myRotationAndSize.yz ;
	
	float2x2 theRotation = ComputeParticleRotation(myRotationAndSize.x);
	input.position.xy = mul(input.position.xy, theRotation);
	input.position.x *= ratio;
	input.position.xy += myPosition;
	output.position = input.position;
	output.tex = myUV.xy + (input.tex * myUV.z);
	output.color = myCustomData; 
	output.textureMappingData = myRotationAndSize.w;
	
    return output;  
}