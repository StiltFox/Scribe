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