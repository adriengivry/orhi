/**
* @project: orhi (OpenRHI)
* @author: Jian Bang Xu
* @licence: MIT
*/

#pragma once

#if defined(_WIN32)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

#define NOGDI
#include <wrl.h>
#endif