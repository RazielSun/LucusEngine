
#ifndef _LUCUS_ENGINE_PLATFORMS_H
#define	_LUCUS_ENGINE_PLATFORMS_H

// #if !(( defined ( DEBUG ) && defined ( _DEBUG )) || defined ( NDEBUG ))
// 	#error DEBUG and _DEBUG or NDEBUG *must* be defined!
// #endif

// //http://predef.sourceforge.net/preos.html#sec19
// #if defined( __APPLE__ ) && defined( __MACH__ )

// 	#include "TargetConditionals.h"

// 	#if TARGET_OS_IPHONE

// 		#define MOAI_OS_IPHONE

// //		#if TARGET_IPHONE_SIMULATOR
// //			#define MOAI_OS_IPHONE_SIMULATOR
// //		#else
// //			#define MOAI_OS_IPHONE_DEVICE
// //		#endif

// 	#else
// 		#define MOAI_OS_OSX
// 	#endif

// #elif defined( _WIN32 )
// 	#define MOAI_OS_WINDOWS

// #elif defined( EMSCRIPTEN )
// 	#define MOAI_OS_HTML

// #elif defined( __linux )
// 	#ifdef ANDROID
// 		#define MOAI_OS_ANDROID
// 	#else
// 		#define MOAI_OS_LINUX
// 	#endif
// #else
// 	#define MOAI_OS_UNKNOWN
// #endif

// #ifdef __QNX__
//   #define MOAI_PHONE
//   #define MOAI_OS_BLACKBERRY
// #endif

// #ifdef _MSC_VER
// 	#define MOAI_COMPILER_MSVC
//   //  #ifndef va_copy
//   //  	#define va_copy(d,s) ((d) = (s))
// 	//  #endif
// 	#define __func__ __FUNCTION__
// #else
// 	#define MOAI_COMPILER_GCC

// #endif

#ifndef LUCUS_ENGINE_OS_WINDOWS
	#define LUCUS_ENGINE_HAS_UNISTD
	#include <unistd.h>
#endif

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <math.h>
// #include <errno.h>
// #include <float.h>
// #include <stdarg.h>
#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
// #include <time.h>
// #include <signal.h>
// #include <setjmp.h>

#ifdef __cplusplus
	#include <algorithm>
	// #include <cstdio>
	#include <cstdlib>
	#include <utility>
	#include <fstream>
	#include <exception>
	#include <map>
	#include <unordered_map>
	// #include <set>
	#include <string>
 	#include <iostream>
	// #include <sstream>
	#include <vector>
	#include <atomic>
#endif

#endif	/* _LUCUS_ENGINE_PLATFORMS_H */