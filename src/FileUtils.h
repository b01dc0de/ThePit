#ifndef THEPIT_FILEUTILS_H
#define THEPIT_FILEUTILS_H

#include "Common.h"

namespace ThePit
{
    using ByteT = unsigned char;

    struct FileContentsT
    {
        const char* filename;
        ByteT* contents;
    };

    void ReadFileContents(FileContentsT* out_contents);

	const char* GetProjectDir();
} // namespace ThePit

#endif // THEPIT_FILEUTILS_H
