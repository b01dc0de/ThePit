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
#define THEPIT_NOOP() (void)0

/* ----- BEGIN CONFIG SPECIFIC DEFINES ----- */
#if THEPIT_CONFIG_DEBUG()
    #define DBG_LOGF(...) LOGF(__VA_ARGS__)
    #define DBG_LOG(...) LOG(__VA_ARGS__)
    #define DBG_BREAKPOINT() PLATFORM_DBG_BREAKPOINT()
#elif THEPIT_CONFIG_RELEASE()
    #define DBG_LOGF(...) THEPIT_NOOP()
    #define DBG_LOG(...) THEPIT_NOOP()
    #define DBG_BREAKPOINT() THEPIT_NOOP() 
#endif // THEPIT_CONFIG
/* -----  END  CONFIG SPECIFIC DEFINES ----- */

/* ----- BEGIN THEPIT COMMON INCLUDES ----- */
#include "DataTypes.h"
#include "Log.h"
#include "Math.h"
/* -----  END  THEPIT COMMON INCLUDES ----- */

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

// SoLoud Audio Backend...
#define WITH_MINIAUDIO

/*-----BEGIN LIBS-----*/
// ImGUI
#include "imgui.h"
// Sokol
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_audio.h"
#include "sokol_log.h"
#include "sokol_time.h"
//#include "sokol_fetch.h"
#include "sokol_glue.h"
#include "util/sokol_imgui.h"
// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
//SoLoud
#include "soloud.h"
#include "soloud_wav.h"
/*------END  LIBS-----*/
/*-----BEGIN STD LIBS-----*/
#include <stdarg.h>
#include <stdlib.h> 
#include <stdio.h>
#include <stdint.h>
#include <string.h>
/*------END  STD LIBS-----*/

#endif // THEPIT_COMMON_H
