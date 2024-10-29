#ifndef THEPIT_LOG_H
#define THEPIT_LOG_H

namespace ThePit
{
    void DbgLogf();
    void DbgLog();

    void Assertf(bool condition, const char* expr, const char* filename, int line);
    void Logf(const char* fmt, ...);
    void Log(const char* msg)
} // namespace ThePit

#endif // THEPIT_LOG_H