#include "Common.h"

#include "../libs/sokol/sokol_app.h"
// #include "../libs/sokol/sokol_gfx.h"
#include "../libs/sokol/sokol_time.h"
#include "../libs/sokol/sokol_audio.h"
#include "../libs/sokol/sokol_log.h"
//#include "sokol_fetch.h"

#include "Engine.h"

extern sapp_desc sokol_main(int argc, char* argv[])
{
	THE_PIT_UNUSED(argc);
	THE_PIT_UNUSED(argv);

	sapp_desc thepit_desc = {};
	{
		thepit_desc.user_data = &thepit::GlobalState;
		thepit_desc.init_userdata_cb = thepit::Init;
		thepit_desc.frame_userdata_cb = thepit::Frame;
		thepit_desc.cleanup_userdata_cb = thepit::Cleanup;
		thepit_desc.event_userdata_cb = thepit::HandleEvent;
		thepit_desc.width = ThePit_Width;
		thepit_desc.height = ThePit_Height;
		thepit_desc.sample_count = 1;
		thepit_desc.high_dpi = true;
		thepit_desc.fullscreen = false;
		thepit_desc.window_title = "DO NOT FALL IN THE PIT";
	}
	return thepit_desc;
}

