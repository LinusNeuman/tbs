#pragma once
#include "tga2d/math/Vector2.h"


enum EShaderMap
{
	NORMAL_MAP,
	MAP_MAX,
};

struct SColor
{
	SColor(){}
	SColor(float aR, float aG, float aB, float aA)
		:myR(aR)
		,myG(aG)
		,myB(aB)
		,myA(aA)
	{}
	float myR, myG, myB, myA;    // color
};

struct SVertex
{
	float X, Y, Z;      // position
	float texX, texY;    // tex
};

struct SVertexInstanced
{
	float X, Y, Z, W;      // position
	unsigned int myVertexIndex, unused1, unused2, unused3;
	float texX, texY;    // tex
};

struct SSimpleVertex
{
	float X, Y, Z;      // position
	float myColorR ,myColorG ,myColorB, myColorA;
	float myU, myV;
};