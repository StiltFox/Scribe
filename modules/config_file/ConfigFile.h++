#ifndef StiltFox_SCRIBE_MODULES_CONFIG_FILE_CONFIGFILE_H
#define StiltFox_SCRIBE_MODULES_CONFIG_FILE_CONFIGFILE_H
#include "File.h++"

namespace StiltFox::Scribe::Configuration
{
    #ifdef win32
        const static std::string LOCATION = "%appdata%\\{}\\{}\\{}.cfg";
    #else
        const static std::string LOCATION = "~/.config/{}/{}/{}.cfg";
    #endif

    File getConfigurationFile(const std::string& companyName, const std::string& programName, const std::string& configName);
}

#endif
