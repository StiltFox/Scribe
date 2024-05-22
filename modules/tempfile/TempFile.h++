#ifndef StiltFox_UniversalLibrary_TempFile
#define StiltFox_UniversalLibrary_TempFile
#include <filesystem>
#include "File.h++"

namespace StiltFox::Scribe
{
    class TemporaryFile : public File
    {
        TemporaryFile(const char* path, bool isDir, const std::string& data, std::filesystem::perms permissions);

    public:
        TemporaryFile(const std::string& path, bool isDir, std::filesystem::perms permissions = std::filesystem::perms::all);
        TemporaryFile(const char* path, bool isDir, std::filesystem::perms permissions = std::filesystem::perms::all);
        TemporaryFile(const std::string& path, const std::string& data = "", std::filesystem::perms permissions = std::filesystem::perms::all);
        TemporaryFile(const char* path, const char* data = "", std::filesystem::perms permissions = std::filesystem::perms::all);
        ~TemporaryFile();
    };
}
#endif