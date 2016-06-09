// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// reference additional headers your program requires here


#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/drawers/line_drawer.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>
#include <tga2d/drawers/debug_drawer.h>

#include <CU/DLDebug/DL_Debug.h>
#include <CU/NameSpaceAliases.h>

#include <CU/Vectors/Vector.h>
#include <CU/Vectors/Vector2.h>
#include <CU/Vectors/Vector4.h>
#include <CU/InputWrapper/SingletonInputWrapper.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <unordered_map>
#include <CU/Utility/CommonCasts.h>