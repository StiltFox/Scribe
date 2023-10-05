#include "BufferedFile.h++"

using namespace std;
using namespace StiltFox::Scribe;

BufferedFile::BufferedFile(string name): BufferedFile(name.c_str()) {};

BufferedFile::BufferedFile(const char* name): File(name)
{
    buffer = read();
}

bool BufferedFile::write(const std::string& toWrite)
{
    buffer = toWrite;
    return true;
}

bool BufferedFile::append(const std::string& toAppend)
{
    return false;
}

std::string BufferedFile::getBuffer()
{
    return buffer;
}