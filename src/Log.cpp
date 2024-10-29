#include "Log.h"
#include <cstdio>

namespace ThePit
{

void Platform_DbgLog()
{
#if THEPIT_PLATFORM_WINDOWS()
#elif THEPIT_PLATFORM_MACOS()
#elif THEPIT_PLATFORM_LINUX()
#endif // THEPIT_PLATFORM
}

void DbgLogf()
{

}

void DbgLog()
{

}

void Assertf(bool condition, const char* expr, const char* filename, int line)
{
}

void Logf(const char* fmt, ...)
{

}

void LogMsg(const char* msg)
{

}

} // namespace
