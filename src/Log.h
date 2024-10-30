#ifndef THEPIT_LOG_H
#define THEPIT_LOG_H

#include "Common.h"

namespace ThePit
{
    void Logf(const char* fmt, ...);
    void Log(const char* msg);
    void Assertf(bool condition, const char* expr, const char* filename, int line);
} // namespace ThePit

#endif // THEPIT_LOG_H