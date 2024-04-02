#include <format>
#include "ConfigFile.h++"

using namespace std;
using namespace StiltFox::Scribe;

File Configuration::getConfigurationFile(const string& companyName, const string& programName, const string& configName)
{
    return vformat(LOCATION, make_format_args(companyName, programName, configName));
}