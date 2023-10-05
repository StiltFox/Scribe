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

        bool canWrite() const;
        bool canRead() const;
        bool canExecute() const;
        bool exists() const;
        bool touch();
        bool mkdir();
        bool remove();
        bool isDirectory() const;
        int getSize() const;
        bool copy(const std::string&) const;
        virtual bool write(const std::string&);
        virtual bool append(const std::string&);
        std::string read() const;
        std::string readFirstNCharacters(int) const;
        std::string readLastNCharacters(int) const;
        std::string getPath() const;
        std::string getExtension() const;
        std::string getNameWithoutExtension() const;
        std::unordered_set<std::string> list() const;
        std::unordered_set<std::string> list(const std::function<void(const std::string&)>&) const;

        File& operator=(std::string);
    };
}
#endif