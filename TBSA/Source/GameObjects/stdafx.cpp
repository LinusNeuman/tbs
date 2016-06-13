// stdafx.cpp : source file that includes just the standard includes
// Game.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

extern float TweenSine(float aZeroToOne)
{
	return (sin(-3.14159265359f / 2 + aZeroToOne * 3.14159265359f) + 1) / 2;
}