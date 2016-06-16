#include "common.fx"

struct VertexInputType
{
    float4 position : POSITION;
	float4 color : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 color : TEXCOORD0;
};

PixelInputType VShader(VertexInputType input)
{
    PixelInputType output;
	
    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;
	
	output.position = input.position;
	output.color = input.color;
    
    return output;
}


float4 PShader(PixelInputType input) : SV_TARGET
{
	float4 textureColor = input.color;
    return textureColor;
}