#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

#include "../libs/sokol/sokol_gfx.h"
#include "../libs/sokol/sokol_glue.h"

struct sapp_event;

namespace thepit
{
	struct State
	{
		sg_pipeline pip;
		sg_bindings bind;
		sg_pass_action pass_action;
	};
	extern State GlobalState;

	void Init(void* State);
	void Frame(void* State);
	void Cleanup(void* State);
	void HandleEvent(const sapp_event* Event, void* State);
}

#endif // ENGINE_H
