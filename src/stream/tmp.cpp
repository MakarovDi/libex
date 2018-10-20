#include "ex/stream/tmp"
#include "ex/platform/detect"

#include <cstdlib>


namespace ex
{


std::string generate_tmp_file_name()
{
    const char *tmp_folder = "";

    if (!ex::compiler::msc())
    {
        // get temp folder location
        // TODO: C++17 std::filesystem::temp_directory_path

        const char* tmp_env_var[4] = { "TMP", "TEMP", "TMPDIR", "TEMPDIR" };

        for (int i = 0; i < (int)sizeof(tmp_env_var); ++i)
        {
            tmp_folder = std::getenv(tmp_env_var[i]);
            if (tmp_folder != nullptr) break;
        }

        if (tmp_folder == nullptr)
            throw std::runtime_error("can't get temporary folder location");
    }

    // generate unique filename

    char fname_buf[512];
    const char* tmp_name = std::tmpnam(fname_buf);

    if (tmp_name == nullptr)
        throw std::runtime_error("tmp filename generation failed");

    // build full path

    std::string tmp_file_name;
    tmp_file_name += tmp_folder;
    tmp_file_name += tmp_name;

    return tmp_file_name;
}



TmpFileStream::~TmpFileStream()
{
    close_file();

    std::remove(filename().c_str());
}


}
