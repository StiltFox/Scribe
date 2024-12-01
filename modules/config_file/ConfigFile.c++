#include "ConfigFile.h++"

using namespace std;
using namespace StiltFox::Scribe;

File Configuration::getConfigurationFile(const string& companyName, const string& programName, const string& configName)
{
    string finalLocation = LOCATION;

    if (size_t replacePosition = finalLocation.find("{}"); replacePosition != string::npos)
    {
        finalLocation.replace(replacePosition, 2, companyName);
        if (replacePosition = finalLocation.find("{}"); replacePosition != string::npos)
        {
            finalLocation.replace(replacePosition, 2, programName);
            if (replacePosition = finalLocation.find("{}"); replacePosition != string::npos)
            {
                finalLocation.replace(replacePosition, 2, configName);
            }
        }
    }

    return finalLocation;
}