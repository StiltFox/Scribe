#include "TempFile.h++"

using namespace std;
using namespace StiltFox::Scribe;

TemporaryFile::TemporaryFile(const char* filePath, bool isDir, const string& data, filesystem::perms permissions) : File(filePath)
{
    if (exists()) remove();
    if (isDir)
    {
        mkdir();
    }
    else
    {
        touch();
        File::write(data);
    }
    filesystem::permissions(filePath, permissions, filesystem::perm_options::replace);
}

TemporaryFile::TemporaryFile(const char* path, bool isDir, filesystem::perms permissions) : TemporaryFile(path, isDir, "", permissions){}
TemporaryFile::TemporaryFile(const string& path, bool isDir, filesystem::perms permissions) : TemporaryFile(path.c_str(), isDir, "", permissions){}
TemporaryFile::TemporaryFile(const char* path, const char* data, filesystem::perms permissions) : TemporaryFile(path, false, data, permissions){}
TemporaryFile::TemporaryFile(const string& path, const string& data, filesystem::perms permissions) : TemporaryFile(path.c_str(), false, data, permissions){}

TemporaryFile::~TemporaryFile()
{
    filesystem::permissions(getPath(),filesystem::perms::all,filesystem::perm_options::replace);
    if (exists()) remove();
}