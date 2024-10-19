#ifndef COMMON_H
#define COMMON_H

// CKA_TODO: Implement different printf
#define LOGF(...) printf(__VA_ARGS__)
#define DBG_LOGF(...) LOGF(__VA_ARGS__)
#define DBG_BREAKPOINT() DebugBreak()
#define THE_PIT_ASSERT(Expr) \
	if (!(Expr)) \
	{ \
		DBG_LOGF("ASSERT FAILED!\n\tExpression: %s\n\tFile: %s, Line: %d\n", #Expr, __FILE__, __LINE__); \
	}
#define THE_PIT_UNUSED(Var) (void)Var

#define SOKOL_GLCORE
/*	Other 3D graphics libs:
	- SOKOL_GLES3
	- SOKOL_D3D11
	- SOKOL_METAL
	- SOKOL_WGPU
	- SOKOL_NOAPI
*/
#define SOKOL_ASSERT(c) THE_PIT_ASSERT(c)
#define SOKOL_UNREACHABLE THE_PIT_ASSERT(false)
/* Undefined for now:
	- SOKOL_WIN32_FORCE_MAIN 
	- SOKOL_NO_ENTRY 
	- SOKOL_APP_API_DECL 
	- SOKOL_API_DECL 
	- SOKOL_API_IMPL 
	- SOKOL_DEBUG
	- SOKOL_DLL
*/

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_time.h"
#include "sokol_audio.h"
#include "sokol_log.h"
//#include "sokol_fetch.h"
#include "sokol_glue.h"

const int ThePit_Width = 720;
const int ThePit_Height = 480;

#endif // THEPIT_COMMON_H
