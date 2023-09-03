#ifndef StiltFox_Scribe_File
#define StiltFox_Scribe_File
#include <functional>
#include <unordered_set>
#include <string>

namespace StiltFox::Scribe
{
    class File
    {
        std::string path;
        void createParentPath();

        public:
        File(const char*);
        File(std::string);

        bool canWrite();
        bool canRead();
        bool canExecute();
        bool exists();
        bool touch();
        bool mkdir();
        bool remove();
        bool isDirectory();
        int getSize();
        bool copy(const std::string&);
        bool write(const std::string&);
        bool append(const std::string&);
        std::string read();
        std::string readFirstNCharacters(int);
        std::string readLastNCharacters(int);
        std::string getPath();
        std::string getExtension();
        std::string getNameWithoutExtension();
        std::unordered_set<std::string> list();
        std::unordered_set<std::string> list(const std::function<void(const std::string&)>&);

        File& operator=(std::string);
    };
}
#endif