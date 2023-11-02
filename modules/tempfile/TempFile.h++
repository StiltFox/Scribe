/*
* Copyright: 2023 Stilt Fox LLC.
* Author: Cryos
* Email: cryos@stiltfox.com
* IM: https://matrix.to/#/@cryos:matrix.org
* Github: https://github.com/StiltFox
*/

#ifndef StiltFox_UniversalLibrary_TempFile
#define StiltFox_UniversalLibrary_TempFile
#include <filesystem>
#include "File.h++"

namespace StiltFox::Scribe
{
    /*
    * TemporaryFile:
    *   This class's purpose is to make temporary files that delete once the object goes out of scope
    * or is deleted. This class extends and uses all of the functions defined in File.
    */
    struct TemporaryFile : public File
    {
        /*
        * Summary:
        *   This constructor creates a temporary file. If the file already exists, the old file will be
        * deleted and replaced with a new one.
        * 
        * Inputs:
        *   path: a char array that points to the temporary file. The file name must be included in the path. ex: /tmp/my_file.tmp
        *         any missing directories will be created.
        *   data: a string representing the data you want the file to start with.
        *       default: ""
        *   permissions: a struct from std::filesystem that allows you to define the permissions the file will be created with.
        *       default: std::filesystem::perms::all
        */
        TemporaryFile(const char* path, std::string data = "", std::filesystem::perms permissions = std::filesystem::perms::all);

        /*
        * Summary:
        *   This constructor is the same as the one above, but it takes in a string instead. This is to help with compatibility
        *  with more modern C++ code.
        */
        TemporaryFile(std::string path, std::string data = "", std::filesystem::perms permissions = std::filesystem::perms::all);

        /*
        * Summary:
        *   This deconstructor will delete the file. This cannot be undone and it will not go to trash.
        */
        ~TemporaryFile();
    };
}
#endif