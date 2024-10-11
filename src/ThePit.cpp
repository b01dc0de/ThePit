#include "ThePit.h"

#include "sokol_app.h"

#include "ThePit_Engine.h"

sapp_desc thepit_appdesc()
{
	sapp_desc Result = {};
	{
		Result.user_data = &GlobalState;
		Result.init_userdata_cb = thepit_init;
		Result.frame_userdata_cb = thepit_frame;
		Result.cleanup_userdata_cb = thepit_cleanup;
		Result.event_userdata_cb = thepit_event;
		Result.width = ThePit_Width;
		Result.height = ThePit_Height;
		Result.sample_count = 1;
		Result.high_dpi = true;
		Result.fullscreen = false;
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

