#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "BufferedFile.h++"

using namespace std;
using namespace StiltFox::Scribe;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Buffered File initialization tests////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(BufferedFile, initalizing_a_buffered_file_will_read_the_contents_of_the_current_file_into_the_buffer)
{
    //given we have a file with data already in it
    ofstream existingFile(".bufferedfile_temp_-01");
    existingFile << "どうそよろしく";
    existingFile.close();

    //when we create a buffered file
    BufferedFile file = ".bufferedfile_temp_-01";

    //then we get the contents of the file in the buffer
    EXPECT_EQ(file.getBuffer(), "どうそよろしく");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////Buffered File write tests/////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(BufferedFile, write_will_write_to_buffer_instead_of_saving_to_file)
{
    //given we have a file on the system that we point to with a buffered file
    ofstream existingFile(".bufferedfile_temp_00");
    existingFile.close();
    BufferedFile file = ".bufferedFile_temp_00";

    //when we attempt to write to the buffered file
    file.write("this goes to the buffer");

    //then the file is not written to
    EXPECT_EQ(file.read(), "");
    EXPECT_EQ(file.getBuffer(), "this goes to the buffer");
    filesystem::remove_all(".bufferedFile_temp_00");
}

TEST(BufferedFile, write_will_always_return_true)
{
    //given we have a buffered file
    BufferedFile file = ".bufferedFile_temp_01";

    //when we attempt to write to the buffered file
    bool actual = file.write("the data here does not matter");

    //then we get back true
    EXPECT_TRUE(actual);
}

TEST(BufferedFile, write_will_not_create_a_new_file)
{
    //given we have a buffered file
    BufferedFile file = ".bufferedFile_temp_02";

    //when we attempt to write to the buffered file
    file.write("the data here does not matter");

    //then the file does not exist
    EXPECT_FALSE(filesystem::exists(".bufferedFile_temp_02"));
}

TEST(BufferedFile, write_will_overwrite_buffer)
{
    //given we have a buffered file
    BufferedFile file = ".bufferedFile_temp_03";

    //when we attempt to write the the buffered file mutliple times
    file.write("SCP-682 has breached containment multiple times");
    file.write("[redacted]");

    //then only the second write applies because it overwrites the buffer
    EXPECT_EQ(file.getBuffer(), "[redacted]");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////Buffered File append tests////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(BufferedFile, append_will_append_to_buffer_but_not_write_to_file)
{
    //given we have a file
    ofstream initialFile(".bufferedFile_temp_04");
    initialFile << "鬣狼 ";
    initialFile.close();
    BufferedFile file = ".bufferedFile_temp_04";

    //when we append to the file
    file.append("is majestic.");

    //then we append the text to the buffer and the file is not effected
    EXPECT_EQ(file.read(), "鬣狼 ");
    EXPECT_EQ(file.getBuffer(), "鬣狼 is majestic.");
    filesystem::remove_all(".bufferedFile_temp_04");
}

TEST(BufferedFile, append_will_always_return_true)
{
    //given we have a buffered file
    BufferedFile file = ".bufferedFile_temp_05";

    //when we attempt to write to the buffered file
    bool actual = file.append("the data here does not matter");

    //then we get back true
    EXPECT_TRUE(actual);
}

TEST(BufferedFile, append_will_not_create_a_new_file)
{
    //given we have a buffered file
    BufferedFile file = ".bufferedFile_temp_06";

    //when we attempt to write to the buffered file
    file.append("the data here does not matter");

    //then the file does not exist
    EXPECT_FALSE(filesystem::exists(".bufferedFile_temp_06"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////Buffered File save tests/////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(BufferedFile, save_will_write_the_buffer_to_the_underlying_file)
{
    //given we have an existing file with nothing in it
    ofstream existingFile(".bufferedFile_temp_07");
    existingFile.close();
    BufferedFile file = ".bufferedFile_temp_07";

    //when we modify the buffer then save
    file.write("鬣狼");
    file.save();

    //then the buffer is written to the file
    EXPECT_EQ(file.read(), "鬣狼");
    filesystem::remove_all("bufferedFile_temp_07");
}

TEST(BufferedFile, save_will_overwrite_an_existing_file)
{
    //given we have an existing file with data in it
    ofstream existingFile(".bufferedFile_temp_08");
    existingFile << "testing data goes here";
    existingFile.close();
    BufferedFile file = ".bufferedFile_temp_08";

    //when we modify the buffer then save
    file.write("野生の鬣狼は林檎を戦っている！");
    file.save();

    //then we overwrite the existing file
    EXPECT_EQ(file.read(), "野生の鬣狼は林檎を戦っている！");
    filesystem::remove_all(".bufferedFile_temp_08");
}

TEST(BufferedFile, save_will_create_the_file_if_it_does_not_exist)
{
    //given we have a file that does not exist
    BufferedFile file = ".bufferedFile_temp_09";

    //when we modify the buffer then save
    file.write("鬣狼は林檎を食べたろか？！？！");
    file.save();

    //then the file is created with the desired data
    EXPECT_TRUE(file.exists());
    EXPECT_EQ(file.read(), "鬣狼は林檎を食べたろか？！？！");
    filesystem::remove_all(".bufferedFile_temp_09");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////