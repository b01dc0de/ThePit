#ifndef THEPIT_COMMON_H
#define THEPIT_COMMON_H

#include "Platform.h"

/*----- BEGIN PLATFORM INCLUDES -----*/
#if THEPIT_PLATFORM_WINDOWS()
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#elif THEPIT_PLATFORM_MACOS()
    #include <signal.h>
#elif THEPIT_PLATFORM_LINUX()
    #include <signal.h>
#endif // PLATFORM INLCUDES
/*----- BEGIN PLATFORM INCLUDES -----*/
/* ----- BEGIN PLATFORM SPECIFIC DEFINES ----- */
// TODO: ...?
#if THEPIT_PLATFORM_WINDOWS()
#elif THEPIT_PLATFORM_MACOS()
#elif THEPIT_PLATFORM_LINUX()
#endif
/* -----  END  PLATFORM SPECIFIC DEFINES ----- */
/* ----- BEGIN COMPILER SPECIFIC DEFINES ----- */
#if THEPIT_COMPILER_MSVC()
    #define PLATFORM_DBG_BREAKPOINT() __debugbreak()
#elif THEPIT_COMPILER_CLANG()
    #define PLATFORM_DBG_BREAKPOINT() raise(SIGTRAP)
#elif THEPIT_COMPILER_GCC()
    #define PLATFORM_DBG_BREAKPOINT() raise(SIGTRAP)
#else
    #error "No THEPIT_COMPILER_ defined"
#endif
/* -----  END  COMPILER SPECIFIC DEFINES ----- */

// CKA_TODO: Implement different printf
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define LOG(msg) ThePit::Log(msg)
#define LOGF(...) ThePit::Logf(__VA_ARGS__)
#define THEPIT_ASSERT(expr) ThePit::Assertf((expr), #expr, __FILE__, __LINE__)
#define THEPIT_UNUSED(Var) (void)Var

/* ----- BEGIN CONFIG SPECIFIC DEFINES ----- */
#if THEPIT_CONFIG_DEBUG()
    #define DBG_LOGF(...) LOGF(__VA_ARGS__)
    #define DBG_LOG(...) LOG(__VA_ARGS__)
    #define DBG_BREAKPOINT() PLATFORM_DBG_BREAKPOINT()
#else THEPIT_CONFIG_RELEASE()
    #define DBG_LOGF(...) (void)0
    #define DBG_LOG(...) (void)0
    #define DBG_BREAKPOINT() (void)0
#endif // THEPIT_CONFIG
/* -----  END  CONFIG SPECIFIC DEFINES ----- */

#define SOKOL_GLCORE
/*	NOTE: Other Sokol graphics libs: SOKOL_GLES3, SOKOL_D3D11, SOKOL_METAL, SOKOL_WGPU, SOKOL_NOAPI */
#define SOKOL_ASSERT(c) THEPIT_ASSERT(c)
#define SOKOL_DEBUG
#define SOKOL_UNREACHABLE THEPIT_ASSERT(false)
/* Undefined for now:
	- SOKOL_WIN32_FORCE_MAIN 
	- SOKOL_NO_ENTRY 
	- SOKOL_APP_API_DECL 
	- SOKOL_API_DECL 
	- SOKOL_API_IMPL 
	- SOKOL_DLL
*/

// ThePit Common Includes
#include "Log.h"
#include "Math.h"
// ThePit Common Includes

/*-----BEGIN LIBS-----*/
// Sokol
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_audio.h"
#include "sokol_log.h"
#include "sokol_time.h"
//#include "sokol_fetch.h"
#include "sokol_glue.h"
// HandmadeMath
#include "lib/HandmadeMath.h"
/*------END  LIBS-----*/
/*-----BEGIN STD LIBS-----*/
#include <stdarg.h>
#include <stdlib.h> 
#include <stdio.h>
#include <stdint.h>
#include <string.h>
/*------END  STD LIBS-----*/

#endif // THEPIT_COMMON_H
