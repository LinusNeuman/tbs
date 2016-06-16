cbuffer MatrixBuffer : register(b0) 
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

Texture2D myNoiseTexture: register( t0 );
cbuffer CommonBuffer : register(b1) 
{
	float4 myResolution; //myResolution.x = screen width, myResolution.y = screen height, myResolution.z = unset, myResolution.w = unset
	float4 myTimings; //myTimings.x = totaltime, myTimings.y = delta time, myTimings.z = unset, myTimings.w = unset
	float4 myRandomValues; //myRandomValues.x = the random seed, myRandomValues.y = a random value ranging -1 to 1, myRandomValues.z = unset, myRandomValues.w = unset
};

struct SLight
{
	float4 myLightColor;
	float4 myPosition;//Position.xy, Intensity, Falloff
};

cbuffer LightBuffer : register(b2)
{
	SLight myLights[8];
	uint myNumberOfLights;
	float myAmbience;
	uint myUnused2;
	uint myUnused3;
};

cbuffer ObjectBuffer : register(b3) 
{
	float4 myRotationAndSize;
	float2 myPosition;
	float2 myUnUsed3;
	float4 myColor;
	float4 myPivot;
	float4 myUV;
};

cbuffer ObjectBufferCustom : register(b4) 
{
	float4 myRotationAndSizeCustom;
	float2 myPositionCustom;
	float2 myDummyCustom;
};