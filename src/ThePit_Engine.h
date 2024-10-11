#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

struct thepit_state
{
	// TODO:
};
extern thepit_state GlobalState;

struct sapp_event;
void thepit_init(void* State);
void thepit_frame(void* State);
void thepit_cleanup(void* State);
void thepit_event(const sapp_event* Event, void* State);

#endif // THEPIT_ENGINE_H