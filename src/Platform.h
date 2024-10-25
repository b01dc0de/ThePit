#ifndef THEPIT_PLATFORM_H
#define THEPIT_PLATFORM_H

// Define THEPIT_PLATFORM
#if defined(_WIN32) && defined(_WIN64) && _WIN32 && _WIN64
    #define THEPIT_PLATFORM_WINDOWS() (1)
    #define THEPIT_PLATFORM_MACOS() (0)
    #define THEPIT_PLATFORM_LINUX() (0)
#elif defined(__APPLE__) && (__APPLE__)
    #define THEPIT_PLATFORM_WINDOWS() (0)
    #define THEPIT_PLATFORM_MACOS() (1)
    #define THEPIT_PLATFORM_LINUX() (0)
#elif defined(__linux__) && (__linux__) && (!__ANDROID__)
    #define THEPIT_PLATFORM_WINDOWS() (0)
    #define THEPIT_PLATFORM_MACOS() (0)
    #define THEPIT_PLATFORM_LINUX() (1)
#endif // Define THEPIT_PLATFORM

// Define THEPIT_COMPILER
#if defined(_MSC_VER) && _MSC_VER // NOTE: MSVC versions: _MSC_VER, _MSC_FULL_VER
    #define THEPIT_COMPILER_MSVC() (1)
    #define THEPIT_COMPILER_CLANG() (0)
    #define THEPIT_COMPILER_GCC() (0)
#elif defined(__clang__) && __clang__ // NOTE: Clang versions: __clang_major__, __clang_minor__, __clang_patchlevel__
    #define THEPIT_COMPILER_MSVC() (0)
    #define THEPIT_COMPILER_CLANG() (1)
    #define THEPIT_COMPILER_GCC() (0)
#elif defined(__GNUC__) && __GNUC__ // NOTE: GCC versions: __GNUC__, __GNUC_MINOR__
    #define THEPIT_COMPILER_MSVC() (0)
    #define THEPIT_COMPILER_CLANG() (0)
    #define THEPIT_COMPILER_GCC() (1)
#endif // Define THEPIT_COMPILER

/* ----- BEGIN ERROR HANDLING ----- */
// Check if at least 1 PLATFORM and 1 COMPILER are defined
#if (!(THEPIT_PLATFORM_WINDOWS() || THEPIT_PLATFORM_MACOS() || THEPIT_PLATFORM_LINUX()))
    #error "No THEPIT_PLATFORM_ defined"
#endif // No platforms defined check
#if (!THEPIT_COMPILER_MSVC()) && (!THEPIT_COMPILER_CLANG()) && (!THEPIT_COMPILER_GCC())
    #error "No THEPIT_COMPILER_ defined"
#endif // No compiler defined check

// Check if more than 1 PLATFORM or 1 COMPILER are defined
#if (THEPIT_PLATFORM_WINDOWS() && (THEPIT_PLATFORM_MACOS() || THEPIT_PLATFORM_LINUX()))
    #error "Multiple THEPIT_PLATFORM_s defined"
#elif (THEPIT_PLATFORM_MACOS() && (THEPIT_PLATFORM_WINDOWS() || THEPIT_PLATFORM_LINUX()))
    #error "Multiple THEPIT_PLATFORM_s defined"
#elif (THEPIT_PLATFORM_LINUX() && (THEPIT_PLATFORM_WINDOWS() || THEPIT_PLATFORM_MACOS()))
    #error "Multiple THEPIT_PLATFORM_s defined"
#endif // Multiple platforms defined check
#if (THEPIT_COMPILER_MSVC() && (THEPIT_COMPILER_CLANG() || THEPIT_COMPILER_GCC()))
    #error "Multiple THEPIT_COMPILERs defined"
#elif (THEPIT_COMPILER_CLANG() && (THEPIT_COMPILER_MSVC() || THEPIT_COMPILER_GCC()))
    #error "Multiple THEPIT_COMPILERs defined"
#elif (THEPIT_COMPILER_GCC() && (THEPIT_COMPILER_MSVC() || THEPIT_COMPILER_CLANG))
    #error "Multiple THEPIT_COMPILERs defined"
#endif // Multiple compilers defined check
/* -----  END  ERROR HANDLING ----- */

/* ----- BEGIN PLATFORM SPECIFIC DEFINES ----- */
// TODO: Define?
#if THEPIT_PLATFORM_WINDOWS()
#elif THEPIT_PLATFORM_MACOS()
#elif THEPIT_PLATFORM_LINUX()
#endif
/* -----  END  PLATFORM SPECIFIC DEFINES ----- */

/* ----- BEGIN COMPILER SPECIFIC DEFINES ----- */
#if THEPIT_COMPILER_MSVC()
    #define PLATFORM_DBG_BREAKPOINT() __debugbreak()
#elif THEPIT_COMPILER_CLANG()
    #define PLATFORM_DBG_BREAKPOINT() raise(SIGTRAP)
#elif THEPIT_COMPILER_GCC()
    #define PLATFORM_DBG_BREAKPOINT() raise(SIGTRAP)
#else
    #error "No THEPIT_COMPILER_ defined"
#endif
/* -----  END  COMPILER SPECIFIC DEFINES ----- */

#endif // THEPIT_PLATFORM_H