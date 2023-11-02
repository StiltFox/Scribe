/*
* Copyright: 2023 Stilt Fox LLC.
* Author: Cryos
* Email: cryos@stiltfox.com
* IM: https://matrix.to/#/@cryos:matrix.org
* Github: https://github.com/StiltFox
*/

#ifndef StiltFox_Scribe_File
#define StiltFox_Scribe_File
#include <functional>
#include <unordered_set>
#include <string>

namespace StiltFox::Scribe
{
    /*
    * File:
    *   This Class's purpose is to provide an easy way to work with File IO.
    */
    class File
    {
        std::string path;
        void createParentPath();

        public:
        /*
        * Summary:
        *   This constructor simply creates a file object, with a path to the file it's supposed to work on.
        * 
        * Inputs:
        *   filePath: a path to the file to be worked with. This may be a regular file or
        *             a directory.
        */
        File(const char* filePath);

        /*
        * Summary:
        *   This constructor is the same as the one above, but it takes in a string instead. This is to help with compatibility
        *  with more modern C++ code.
        */
        File(std::string filePath);

        /*
        * Summary:
        *   Will return true if it's possible to write to the file.
        */
        bool canWrite() const;

        /*
        * Summary:
        *   Will return true if it's possible to read from the file.
        */
        bool canRead() const;

        /*
        * Summary:
        *   Will return true if it's possible to execute the file.
        */
        bool canExecute() const;

        /*
        * Summary:
        *   Will return true if the file exists.
        */
        bool exists() const;

        /*
        * Summary:
        *   Will attempt to create a blank file at the given path. It will return true on a successful
        * creation. Touch will not overwrite an existing file, and instead simply return true. If a required
        * directory does not exist, touch will create it.
        */
        bool touch();

        /*
        * Summary:
        *   Will attempt to create an empty directory at the given path. It will return true on a successful
        * creation. Mkdir will create required missing directories.
        */
        bool mkdir();

        /*
        * Summary:
        *   Will remove the file referenced and return true if it was successfully removed.
        */
        bool remove();

        /*
        * Summary:
        *   Will return true if the referenced file is a directory.
        */
        bool isDirectory() const;

        /*
        * Summary:
        *   Returns the size of the file if it's a regular file, or the size of all the files in the directory
        * recursively if it's a directory.
        */
        int getSize() const;

        /*
        * Summary:
        *   Will copy the file or folder to the requested location if possible. True is returned on success.
        */
        bool copy(const std::string&) const;

        /*
        * Summary:
        *   Will write to the file if it's a regular file. It returns true if writing was successful.
        */
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