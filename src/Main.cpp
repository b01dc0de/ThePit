#define SOKOL_IMPL
//#define SOKOL_APP_IMPL
// TODO: What's the difference between SOKOL_IMPL and SOKOL_APP_IMPL?
#include "Common.h"
#include "Engine.h"

extern sapp_desc sokol_main(int argc, char* argv[])
{
	ThePit::Engine::global_argc = argc;
	ThePit::Engine::global_argv = argv;

	sapp_desc thepit_desc = {};
	{
		thepit_desc.init_cb = ThePit::Engine::Init;
		thepit_desc.frame_cb = ThePit::Engine::Frame;
		thepit_desc.cleanup_cb = ThePit::Engine::Cleanup;
		thepit_desc.event_cb = ThePit::Engine::HandleEvent;
		thepit_desc.width = ThePit::Engine::WindowWidth;
		thepit_desc.height = ThePit::Engine::WindowHeight;
		thepit_desc.sample_count = 1;
		thepit_desc.high_dpi = true;
		thepit_desc.fullscreen = false;
		thepit_desc.window_title = "DO NOT FALL IN THE PIT";
		thepit_desc.logger.func = slog_func;
	}
	return thepit_desc;
}
