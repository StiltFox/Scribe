#ifndef StiltFox_Scribe_BufferedFile
#define StiltFox_Scribe_BufferedFile
#include "File.h++"

namespace StiltFox::Scribe
{
    class BufferedFile : public File
    {
        std::string buffer;

        public:
        BufferedFile(const char*);
        BufferedFile(std::string);

        bool write(const std::string&) override;
        bool append(const std::string&) override;

        bool save();
        std::string getBuffer();
    };
}

#endif