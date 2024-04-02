#include <gtest/gtest.h>
#include <format>
#include "ConfigFile.h++"

using namespace std;
using namespace StiltFox::Scribe;
using namespace StiltFox::Scribe::Configuration;

TEST(ConfigFile, getConfigurationFile_Will_return_a_file_that_points_to_the_proper_config_location)
{
    //given we have information about the application, and a desired config file
    string companyName = "StiltFox";
    string programName = "Scribe";
    string config = "startup";

    //when we get the configuration
    File actual = getConfigurationFile(companyName, programName, config);

    //then we get back a file that points to the desired configuration file
    EXPECT_EQ(actual.getPath(), vformat(LOCATION, make_format_args(companyName, programName, config)));
}