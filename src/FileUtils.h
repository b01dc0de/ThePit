#ifndef THEPIT_FILEUTILS_H
#define THEPIT_FILEUTILS_H

#include "Common.h"

namespace thepit
{
    using ByteT = unsigned char;

    struct FileContentsT
    {
        const char* filename;
        ByteT* contents;
    };

    void ReadFileContents(FileContentsT* out_contents);

	const char* GetProjectDir();
}

#endif // THEPIT_FILEUTILS_H
