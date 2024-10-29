#include "FileUtils.h"
#include "Engine.h"
#include <cstdio>
#include <string>

namespace ThePit
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
            size_t read_bytes = fread(result_contents, sizeof(ByteT), file_size, file_handle);
            THEPIT_ASSERT(read_bytes == file_size);
            result_contents[file_size] = '\0';

            fclose(file_handle);
        }

        if (result_contents)
        {
            out_contents->contents = result_contents;
        }
    }

    // CKA_NOTE: This currently tries to find the base project directory using a naive method
    //      - This function parses for the first instance of 'ThePit' in the executable filename (global_argv[0])
    //      - If 'thepit.out' executable file is '/home/username/wrk/ThePit/out/build/platform/thepit'
    //      - Then this function would return "/home/username/wrk/ThePit"
    const char* GetProjectDir()
    {
        static const char* project_name = "ThePit";
        static const char* project_dir = nullptr;
        static std::string project_dir_str;
        if (!project_dir)
        {
            THEPIT_ASSERT(0 < global_argc);
            project_dir_str = global_argv[0];
            size_t ThePitDir = project_dir_str.find(project_name);
            project_dir_str = project_dir_str.substr(0, ThePitDir + strlen(project_name));
            project_dir = project_dir_str.c_str();
        }
        return project_dir;
    }
} // namespace ThePit
