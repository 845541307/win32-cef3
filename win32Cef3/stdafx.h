// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#define MAX_URL_LENGTH			255
#define IDC_NAV_BACK			200
#define IDC_NAV_RELOAD			201
#define IDC_NAV_FORWARD			202
#define IDC_NAV_RUNJS			203

#define MYCHECK(ptr) \
if(ptr == NULL)\
	assert(false);

// reference additional headers your program requires here
