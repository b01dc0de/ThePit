#include "Common.h"

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_time.h"
#include "sokol_audio.h"
#include "sokol_log.h"
//#include "sokol_fetch.h"
#include "sokol_glue.h"

#include "Engine.cpp"

extern sapp_desc sokol_main(int argc, char* argv[])
{
	THE_PIT_UNUSED(argc);
	THE_PIT_UNUSED(argv);

	sapp_desc thepit_desc = {};
	{
		thepit_desc.user_data = &GlobalState;
		thepit_desc.init_userdata_cb = thepit_init;
		thepit_desc.frame_userdata_cb = thepit_frame;
		thepit_desc.cleanup_userdata_cb = thepit_cleanup;
		thepit_desc.event_userdata_cb = thepit_event;
		thepit_desc.width = ThePit_Width;
		thepit_desc.height = ThePit_Height;
		thepit_desc.sample_count = 1;
		thepit_desc.high_dpi = true;
		thepit_desc.fullscreen = false;
		thepit_desc.window_title = "DO NOT FALL IN THE PIT";
	}
	return thepit_desc;
}

