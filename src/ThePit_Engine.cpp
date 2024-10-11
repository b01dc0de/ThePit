#include "ThePit_Engine.h"

thepit_state GlobalState;

void thepit_init(void* State)
{
	thepit_state* CurrState = static_cast<thepit_state*>(State);
}

void thepit_frame(void* State)
{
	thepit_state* CurrState = static_cast<thepit_state*>(State);
}

void thepit_cleanup(void* State)
{
	thepit_state* CurrState = static_cast<thepit_state*>(State);
}

void thepit_event(const sapp_event* Event, void* State)
{
	thepit_state* CurrState = static_cast<thepit_state*>(State);
}
