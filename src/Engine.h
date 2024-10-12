#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

struct thepit_EngineState
{
	sg_pipeline pip;
	sg_bindings bind;
	sg_pass_action pass_action;
};
extern thepit_EngineState GlobalState;

struct sapp_event;
void thepit_init(void* State);
void thepit_frame(void* State);
void thepit_cleanup(void* State);
void thepit_event(const sapp_event* Event, void* State);

#endif // THEPIT_ENGINE_H
