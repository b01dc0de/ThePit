#include "ThePit.h"

//#define SOKOL_IMPL
#define SOKOL_APP_IMPL

// Define graphics library:
#define SOKOL_GLCORE
//#define SOKOL_GLES3
//#define SOKOL_D3D11
//#define SOKOL_METAL
//#define SOKOL_WGPU
//#define SOKOL_NOAPI

#define SOKOL_ASSERT(c) THE_PIT_ASSERT(c)
#define SOKOL_UNREACHABLE() THE_PIT_ASSERT(false)
//#define SOKOL_WIN32_FORCE_MAIN - define this on Win32 to use a main() entry point instead of WinMain
//#define SOKOL_NO_ENTRY - define this if sokol_app.h shouldn't "hijack" the main() function
//#define SOKOL_APP_API_DECL - public function declaration prefix(default: extern)
//#define SOKOL_API_DECL - same as SOKOL_APP_API_DECL
//#define SOKOL_API_IMPL - public function implementation prefix(default: -)
//#define SOKOL_DEBUG
//#define SOKOL_DLL

#include "sokol_app.h"

#include <stdio.h>

struct thepit_state
{
	// TODO:
};
thepit_state GlobalState;

void thepit_init(void* State);
void thepit_frame(void* State);
void thepit_cleanup(void* State);
void thepit_event(const sapp_event* Event, void* State);

sapp_desc thepit_appdesc()
{
	sapp_desc Result = {};
	{
		// user-provided callbacks without user data: //init_cb frame_cb cleanup_cb event_cb
		// user-provided callbacks with user data: init_userdata_cb frame_userdata_cb cleanup_userdata_cb event_userdata_cb
		Result.width = 1920;
		Result.height = 1080;
		Result.sample_count = 1;
		Result.high_dpi = true;
		Result.fullscreen;
		Result.window_title = "DO NOT FALL IN THE PIT";
	}
	return Result;
}

extern sapp_desc sokol_main(int argc, char* argv[])
{
	THE_PIT_UNUSED(argc);
	THE_PIT_UNUSED(argv);

	return thepit_appdesc();
}

