#include "FileUtils.h"
#include "Engine.h"
#include <cstdio>

namespace thepit
{
    void ReadFileContents(FileContentsT* out_contents)
    {
        THEPIT_ASSERT(out_contents->filename);
        ByteT* result_contents = nullptr;
        static const int max_len_filename = 256;
        char filename_buff[max_len_filename];
        sprintf(filename_buff, "%s/%s", GetProjectDir(), out_contents->filename);

        FILE* file_handle = nullptr;
        file_handle = fopen(filename_buff, "rb");
        THEPIT_ASSERT(nullptr != file_handle);
        if (file_handle)
        {
            fseek(file_handle, 0, SEEK_END);
            long file_size = ftell(file_handle);
            fseek(file_handle, 0, SEEK_SET);

            result_contents = new ByteT[file_size + 1];
            size_t read_bytes = fread(result_contents, sizeof(char), file_size, file_handle);
            THEPIT_ASSERT(read_bytes == file_size);
            result_contents[file_size] = '\0';

            fclose(file_handle);
        }

        if (result_contents)
        {
            out_contents->contents = result_contents;
        }
    }
}
