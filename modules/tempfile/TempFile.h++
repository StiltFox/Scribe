#ifndef StiltFox_UniversalLibrary_TempFile
#define StiltFox_UniversalLibrary_TempFile
#include <filesystem>
#include "File.h++"

namespace StiltFox::Scribe
{
    struct TemporaryFile : public File
    {
        TemporaryFile(const char* path, std::string data = "", std::filesystem::perms permissions = std::filesystem::perms::all);
        TemporaryFile(std::string path, std::string data = "", std::filesystem::perms permissions = std::filesystem::perms::all);
        ~TemporaryFile();
    };
}
#endif