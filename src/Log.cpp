#include "Log.h"

namespace ThePit
{

void Platform_LogMsg(const char* msg)
{
#if THEPIT_PLATFORM_WINDOWS()
    OutputDebugString(msg);
#elif THEPIT_PLATFORM_MACOS()
    std::puts(msg);
#elif THEPIT_PLATFORM_LINUX()
    std::puts(msg);
#endif // THEPIT_PLATFORM_
}

void LogMsg(const char* msg)
{
    Platform_LogMsg(msg);
}

void Logf(const char* fmt, ...)
{
    static const int max_msg_length = 1024;
    static char fmt_msg[max_msg_length];

    va_list args;
    va_start(args, fmt);
    int num_chars_write = vsnprintf(fmt_msg, max_msg_length, fmt, args);
    va_end(args);
}

void Assertf(bool condition, const char* expr, const char* filename, int line)
{
    if (!condition)
    {
		DBG_LOGF("ASSERT FAILED!\n\tExpression: %s\n\tFile: %s, Line: %d\n", expr, filename, line);
        DBG_BREAKPOINT();
    }
}

} // namespace
