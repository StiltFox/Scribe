#include <filesystem>
#include <fstream>
#include <functional>
#include <cerrno>
#include <unistd.h>
#include <cstring>
#include <utility>
#include "File.h++"

using namespace StiltFox::Scribe;
using namespace std;

File::File(const char* filePath)
{
    path = filePath;
}

File::File(string filePath)
{
    path = std::move(filePath);
}

File& File::operator=(string filePath)
{
    path = std::move(filePath);
    return *this;
}

string File::getPath()
{
    return path;
}

string File::getExtension()
{
    return ((filesystem::path) path).extension().string();
}

string File::getNameWithoutExtension()
{
    return ((filesystem::path) path).stem().string();
}

unordered_set<string> File::list()
{
    return list(nullptr);
}

unordered_set<string> File::list(const function<void(const string&)>& performOnEach)
{
    unordered_set<string> output;

    if (exists())
    {
        output.insert(path);
        for (auto const& dir_entry : filesystem::recursive_directory_iterator(path))
        {
            if (performOnEach != nullptr) performOnEach(dir_entry.path());
            output.insert(dir_entry.path());
        }
    }

    return output;
}

void File::createParentPath()
{
    filesystem::path pth(path.c_str());
    if (pth.has_parent_path()) filesystem::create_directories(pth.parent_path().c_str());
}

bool File::canWrite()
{
    return access(path.c_str(), W_OK) == 0 || errno != EACCES;
}

bool File::canRead()
{
    return access(path.c_str(), R_OK) == 0 || errno != EACCES && errno != ENOENT;
}

bool File::canExecute()
{
    return access(path.c_str(), X_OK) == 0 || errno != EACCES && errno != ENOENT;
}

bool File::exists()
{
    return access(path.c_str(), F_OK) == 0 && canRead();
}

bool File::touch()
{
    if (canWrite() && !exists())
    {
        createParentPath();
        ofstream output(path.c_str());
        output.close();
    }

    return exists() && !isDirectory();
}

bool File::mkdir()
{
    if (canWrite() && !exists()) filesystem::create_directories(path);
    return exists() && isDirectory();
}

bool File::remove()
{
    if (exists() && canWrite()) filesystem::remove_all(path);
    return !exists();
}

bool File::isDirectory()
{
    return canRead() && filesystem::is_directory(path);
}

inline int getFileSize(const string& path)
{
    int output = 0;

    ifstream stream(path, ios::in | ios::binary | ios::ate);
    if (stream.is_open()) output = (int)stream.tellg();
    stream.close();

    return output;
}

int File::getSize()
{
    int output = -1;

    if (exists())
    {
        if(isDirectory())
        {
            output = 0;
            for (auto const& dir_entry : filesystem::recursive_directory_iterator(path))
                if (!((File)dir_entry.path().string()).isDirectory())
                    output+= getFileSize(dir_entry.path().string());
        }
        else
        {
            output = getFileSize(path);
        }
    }

    return output;
}

bool File::copy(const string& copyTo)
{
    File dest = copyTo;
    bool canCopy = canRead() && dest.canWrite();
    if(canCopy)
    {
        if (isDirectory())
        {
            canCopy &= dest.mkdir();
            for (auto const& dir_entry : filesystem::recursive_directory_iterator(path))
            {
                string currentPath = dir_entry.path().string();
                string destPath = copyTo + currentPath.substr(currentPath.find_first_of(filesystem::path::preferred_separator));
                if (dir_entry.is_directory())
                {
                    filesystem::create_directories(destPath);
                }
                else
                {
                    filesystem::copy_file(currentPath, destPath,filesystem::copy_options::overwrite_existing);
                }
            }
        }
        else
        {
            filesystem::copy_file(path, copyTo, filesystem::copy_options::overwrite_existing);
        }
    }
    return canCopy && filesystem::exists(copyTo);
}

bool File::write(const string& toWrite)
{
    bool output = canWrite() && !isDirectory();

    if (output)
    {
        ofstream stream(path, ofstream::out | ofstream::trunc);
        if (stream.is_open()) stream << toWrite;
        stream.close();
    }

    return output;
}

bool File::append(const string& toWrite)
{
    bool output = canWrite() && !isDirectory();

    if (output)
    {
        ofstream stream(path, ofstream::out | ofstream::app);
        if (stream.is_open()) stream << toWrite;
        stream.close();
    }

    return output;
}

string File::read()
{
    return readFirstNCharacters(-1);
}

string File::readFirstNCharacters(int numChars)
{
    string output;

    if(exists() && !isDirectory())
    {
        ifstream stream(path, ios::in | ios::binary | ios::ate);

        if (stream.is_open())
        {
            int fileSize = (int)stream.tellg();
            int readSize = fileSize < numChars || numChars < 0 ? fileSize : numChars;

            char* buffer = new char[readSize + 1];
            memset(buffer, 0, readSize+1);

            stream.seekg(ios::beg);
            stream.read(buffer, readSize);
            stream.close();

            output = buffer;
            delete[] buffer;
        }
    }

    return output;
}

string File::readLastNCharacters(int numChars)
{
    string output;

    if(exists() && !isDirectory())
    {
        ifstream stream(path, ios::in | ios::binary | ios::ate);

        if (stream.is_open())
        {
            int fileSize = (int)stream.tellg();
            int readSize = fileSize < numChars || numChars < 0 ? fileSize : numChars;

            char* buffer = new char[readSize + 1];
            memset(buffer, 0, readSize+1);

            stream.seekg(-readSize, ios::end);
            stream.read(buffer, readSize);
            stream.close();

            output = buffer;
            delete[] buffer;
        }
    }

    return output;
}