// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



//  reference additional headers your program requires here


#include <CU/Timer/Time.h>
#include <CU/DLDebug/DL_Debug.h>
#include <CU/NameSpaceAliases.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Vectors/Vector.h>
#include <CU/InputWrapper/SingletonInputWrapper.h>

// Audio
#include "../Audio/Source/Instances/SoundEffect.h"
#include "../Audio/Source/Instances/Song.h"