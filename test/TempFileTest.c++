#include <gtest/gtest.h>
#include <filesystem>
#include "TempFile.h++"

using namespace std;
using namespace StiltFox::Scribe;

TEST(TemporaryFile, TemporaryFile_will_create_the_requested_file)
{
    //given we create a temporary file
    TemporaryFile temp = ".temp_file_00";

    //then the file will exist on the system
    EXPECT_TRUE(filesystem::exists(".temp_file_00"));
    EXPECT_TRUE(filesystem::is_regular_file(".temp_file_00"));
}

TEST(TemporaryFile, TemporaryFile_will_delete_the_file_on_deconstruction)
{
    //given we create a temporary file
    auto* temp = new TemporaryFile(".temp_file_01");

    //when we delete the temporary file
    delete temp;

    //then the temporary file does not exist anymore
    EXPECT_FALSE(filesystem::exists(".temp_file_01"));
}

TEST(TemporaryFile, TemporaryFile_will_create_a_file_using_a_string_instead_of_a_const_char_array)
{
    //given we have a string
    string filename = ".temp_file_02";
    TemporaryFile temp = filename;

    //then the file will exist on the system
    EXPECT_TRUE(filesystem::exists(".temp_file_02"));
    EXPECT_TRUE(filesystem::is_regular_file(".temp_file_02"));
}

TEST(TemporaryFile, TemporaryFile_will_create_a_file_with_the_expected_contents)
{
    //given we have a temporary file that we want to have specific contents
    TemporaryFile temp(".temp_file_03", "this is the file contents");

    //then the file contains the expected data
    EXPECT_EQ(temp.read(), "this is the file contents");
}

TEST(TemporaryFile, TemporaryFile_will_create_a_folder_if_isDir_is_set_to_true)
{
    //given we create a temporary folder
    TemporaryFile temp(".temp_file_04", true);

    //then the folder will exist on the system
    EXPECT_TRUE(filesystem::exists(".temp_file_04"));
    EXPECT_TRUE(filesystem::is_directory(".temp_file_04"));
}

TEST(TemporaryFile, TemporaryFile_will_create_a_folder_with_a_string_instead_of_a_const_char_array)
{
    //given we create a temporary folder with a string
    string dirName = ".temp_file_05";
    TemporaryFile temp(dirName, true);

    //then the folder will exist on the system
    EXPECT_TRUE(filesystem::exists(".temp_file_05"));
    EXPECT_TRUE(filesystem::is_directory(".temp_file_05"));
}

TEST(TemporaryFile, TemporaryFile_will_delete_folder_and_all_contained_files_on_deconstruction)
{
    //given we create a temporary folder, with contents
    auto* directory = new TemporaryFile(".temp_file_06", true);
    File contentFile = ".temp_file_06/test.txt";
    File subDirectory = ".temp_file_06/subDir";
    File subDirectoryContent = ".temp_file_06/subDir/test.txt";
    contentFile.touch();
    subDirectory.mkdir();
    subDirectoryContent.touch();

    //when we delete the file
    delete directory;

    //then all sub files and directories are deleted
    EXPECT_FALSE(filesystem::exists(".temp_file_06"));
    EXPECT_FALSE(filesystem::exists(".temp_file_06/test.txt"));
    EXPECT_FALSE(filesystem::exists(".temp_file_06/subDir"));
    EXPECT_FALSE(filesystem::exists(".temp_file_06/subDir/test.txt"));
}