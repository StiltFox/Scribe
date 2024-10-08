#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include "File.h++"

#ifdef WIN32
    #define fileSeparator "\\"
#else
    #define fileSeparator "/"
#endif

using namespace StiltFox::Scribe;
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////File canWrite tests////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef WIN32
TEST(File, canWrite_will_return_true_if_we_can_write_to_the_File)
{
    //given we have a file that we have write permissions to
    ofstream goodFile(".FileOps_canWrite_good_File");
    goodFile.close();
    File file = ".FileOps_canWrite_good_File";

    //when we get write permissions
    bool actual = file.canWrite();

    //then we get back that we can write
    EXPECT_TRUE(actual);
    filesystem::remove_all(".FileOps_canWrite_good_File");
}

TEST(File, canWrite_will_return_true_on_a_path_that_is_writable_but_the_file_does_not_exist)
{
    //given we have a non-existing writable path
    File file = ".FileOps_canWrite_good_File01";

    //when we get write permissions
    bool actual = file.canWrite();

    //then we get back that we can write
    EXPECT_TRUE(actual);
}

TEST(File, canWrite_will_return_false_on_a_file_with_bad_permissions)
{
    //given we have a file with bad permissions
    ofstream badFile(".FileOps_canWrite_bad_File");
    badFile.close();
    filesystem::permissions(".FileOps_canWrite_bad_File", filesystem::perms::none, filesystem::perm_options::replace);
    
    File file = ".FileOps_canWrite_bad_File";

    //when we get write permissions
    bool actual = file.canWrite();

    //then we get back that we cannot write
    EXPECT_FALSE(actual);
    filesystem::permissions(".FileOps_canWrite_bad_File", filesystem::perms::all, filesystem::perm_options::replace);
    filesystem::remove_all(".FileOps_canWrite_bad_File");
}

TEST(File, canWrite_will_return_false_for_a_non_existing_path_that_is_not_writable)
{
    //given we have an un-writable path
    filesystem::create_directories(".FileOpes_canWrite_bad_directory");
    chmod(".FileOpes_canWrite_bad_directory", 0x000);
    File file = ".FileOpes_canWrite_bad_directory/file.txt";

    //when we get write permissions
    bool actual = file.canWrite();

    //then we get back that we cannot write
    ASSERT_FALSE(actual);
    chmod(".FileOpes_canWrite_bad_directory", 0x777);
    filesystem::remove_all(".FileOpes_canWrite_bad_directory");
}

TEST(File, canWrite_will_not_create_a_file)
{
    //given we have a non-existing file
    File file = ".FileOps_canWrite_non_existing_file";

    //when we get write permissions
    file.canWrite();

    //then the file is not created
    EXPECT_FALSE(filesystem::exists(".FileOps_canWrite_non_existing_file"));
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////File canRead tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef WIN32
TEST(File, canRead_will_return_true_if_we_can_read_the_File)
{
    //given we have a file that we have read permissions to
    ofstream goodFile(".FileOps_canRead_good_File");
    goodFile.close();
    File file = ".FileOps_canRead_good_File";

    //when we get read permissions
    bool actual = file.canRead();

    //then we get back that we can read
    EXPECT_TRUE(actual);
    filesystem::remove_all(".FileOps_canRead_good_File");
}

TEST(File, canRead_will_return_false_on_a_path_that_does_not_exist)
{
    //given we have a non-existing path
    File file = ".FileOps_canRead_not_existing";

    //when we get read permissions
    bool actual = file.canRead();

    //then we get back that we cannot read
    EXPECT_FALSE(actual);
}

TEST(File, canRead_will_return_false_on_a_file_with_bad_permissions)
{
    //given we have a file with bad permissions
    ofstream badFile(".FileOps_canRead_bad_File");
    badFile.close();
    chmod(".FileOps_canRead_bad_File", 0x000);
    File file = ".FileOps_canRead_bad_File";

    //when we get read permissions
    bool actual = file.canRead();

    //then we get back that we cannot read
    EXPECT_FALSE(actual);
    chmod(".FileOps_canRead_bad_File", 0x777);
    filesystem::remove_all(".FileOps_canRead_bad_File");
}

TEST(File, canRead_will_not_create_a_file)
{
    //given we have a non-existing file
    File file = ".FileOps_canRead_non_existing_file";

    //when we get read permissions
    file.canRead();

    //then the file is not created
    EXPECT_FALSE(filesystem::exists(".FileOps_canRead_non_existing_file"));
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////File canExecute tests///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef WIN32
TEST(File, canExecute_will_return_true_if_we_can_execute_the_File)
{
    //given we have a file that we have execute permissions to
    ofstream goodFile(".FileOps_canExecute_good_File");
    goodFile.close();
    chmod(".FileOps_canExecute_good_File", 0x777);
    File file = ".FileOps_canExecute_good_File";

    //when we get execute permissions
    bool actual = file.canExecute();

    //then we get back that we can execute
    EXPECT_TRUE(actual);
    filesystem::remove_all(".FileOps_canExecute_good_File");
}

TEST(File, canExecute_will_return_false_on_a_path_that_does_not_exist)
{
    //given we have a non-existing path
    File file = ".FileOps_canExecute_not_existing";

    //when we get execute permissions
    bool actual = file.canExecute();

    //then we get back that we cannot execute
    EXPECT_FALSE(actual);
}

TEST(File, canExecute_will_return_false_on_a_file_with_bad_permissions)
{
    //given we have a file with bad permissions
    ofstream badFile(".FileOps_canExecute_bad_File");
    badFile.close();
    chmod(".FileOps_canExecute_bad_File", 0x000);
    File file = ".FileOps_canExecute_bad_File";

    //when we get execute permissions
    bool actual = file.canExecute();

    //then we get back that we cannot execute
    EXPECT_FALSE(actual);
    chmod(".FileOps_canExecute_bad_File", 0x777);
    filesystem::remove_all(".FileOps_canExecute_bad_File");
}

TEST(File, canExecute_will_not_create_a_file)
{
    //given we have a non-existing file
    File file = ".FileOps_canExecute_non_existing_file";

    //when we get read permissions
    file.canExecute();

    //then the file is not created
    EXPECT_FALSE(filesystem::exists(".FileOps_canExecute_non_existing_file"));
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File exists tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (File, exists_returns_true_when_the_referenced_file_exists)
{
    //given we have a file
    ofstream aFile(".FileOps_Exists_01");
    aFile.close();
    File file = ".FileOps_Exists_01";

    //when we check if the file exists
    bool actual = file.exists();

    //then we get back true
    EXPECT_TRUE(actual);
    filesystem::remove_all(".FileOps_Exists_01");
}

TEST(File, exists_returns_false_when_the_referenced_file_does_not_exist)
{
    //given we have a file that does not exist
    File file = ".FileOps_exists_non_existing";

    //when we check if the file exists
    bool actual = file.exists();

    //then we get back that the file does not exist
    EXPECT_FALSE(actual);
}

#ifndef WIN32
TEST(File, exists_returns_false_if_we_do_not_have_read_permissions_to_a_file)
{
    //given we have a file that we cannot read
    ofstream badFile(".FileOps_exists_badFile");
    badFile.close();
    chmod(".FileOps_exists_badFile", 0x000);
    File file = ".FileOps_exists_badFile";

    //when we check if the file exists
    bool actual = file.exists();

    //then we get back that the file does not exist
    ASSERT_FALSE(actual);
    chmod(".FileOps_exists_badFile", 0x777);
    filesystem::remove_all(".FileOps_exists_badFile");
}
#endif

TEST(File, exists_will_not_create_a_file)
{
    //given we have a file that does not exist
    File file = ".FileOps_exists_non_existing_file01";

    //when we check if the file exists
    file.exists();

    //then the file is not created
    EXPECT_FALSE(filesystem::exists(".FileOps_exists_non_existing_file01"));
}

TEST(File, exists_will_return_true_For_a_directory)
{
    //given we have a directory
    filesystem::create_directories(".FileOps_exists_directory");
    File file = ".FileOps_exists_directory";

    //when we check if the file exists
    bool actual = file.exists();

    //then we get back true
    EXPECT_TRUE(actual);
    filesystem::remove_all(".FileOps_exists_directory");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File touch tests//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (File, touch_will_create_blank_file)
{
    //given we have a file that does not exist
    File file = ".FileOps_touch_01";

    //when we touch the file
    bool actual = file.touch();

    //then we get an empty file
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_touch_01"));
    EXPECT_TRUE(filesystem::is_regular_file(".FileOps_touch_01"));
    EXPECT_EQ(filesystem::file_size(".FileOps_touch_01"), 0);
    filesystem::remove_all(".FileOps_touch_01");
}

#ifndef WIN32
TEST(File, touch_will_return_false_if_writing_is_not_possible)
{
    //given we have a folder without read permissions
    filesystem::create_directories(".FileOps_touch_bad_permissions");
    File badTouch = ".FileOps_touch_bad_permissions/badTouch";
    chmod(".FileOps_touch_bad_permissions", 0x000);

    //when we touch the file
    bool actual = badTouch.touch();

    //then we do not create the file and return false
    chmod(".FileOps_touch_bad_permissions", 0x777);
    EXPECT_FALSE(actual);
    EXPECT_FALSE(filesystem::exists(".FileOps_touch_bad_permissions/badTouch"));
    filesystem::remove_all(".FileOps_touch_bad_permissions");
}
#endif

TEST(File, touch_will_return_true_and_not_modify_the_contents_of_an_existing_file)
{
    //given we have an existing file with some contents
    ofstream existingFile(".FileOps_touch_existing");
    existingFile << "here's some data";
    existingFile.close();
    File file = ".FileOps_touch_existing";

    //when we touch the file
    bool actual = file.touch();

    //then we return true and do not edit the file
    EXPECT_TRUE(actual);
    EXPECT_EQ(file.read(), "here's some data");
    filesystem::remove_all(".FileOps_touch_existing");
}

TEST(File, touch_will_create_required_directories)
{
    //given we have a file that needs several directories
    File file = ".FileOps_touch_dir1/ab/bf/test.txt";

    //when we touch the file
    bool actual = file.touch();

    //then we return true and create the file
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_touch_dir1/ab/bf/test.txt"));
    filesystem::remove_all(".FileOps_touch_dir1");
}

TEST(File, touch_will_crate_a_file_in_an_existng_directory)
{
    //given we have an existing directory
    filesystem::create_directories(".FileOps_touch_dir2/temp");
    File file = ".FileOps_touch_dir2/temp/test.txt";

    //when we touch the file
    bool actual = file.touch();

    //then we create the file and return true
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_touch_dir2/temp/test.txt"));
    filesystem::remove_all(".FileOps_touch_dir2");
}

TEST(File, touch_will_return_false_if_touched_file_is_a_directory)
{
    //given we have a directory
    filesystem::create_directories(".FileOps_touch_dir3");
    File file = ".FileOps_touch_dir3";

    //when we touch the file
    bool actual = file.touch();

    //then we get back false
    EXPECT_FALSE(actual);
    filesystem::remove_all(".FileOps_touch_dir3");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File mkdir tests//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, mkdir_will_create_a_directory)
{
    //given we have a path for a non-existing directory
    File file = ".FileOps_mkdir_new_dir";

    //when we make the directory
    bool actual = file.mkdir();

    //then we get back true and the directory is created
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_mkdir_new_dir"));
    EXPECT_TRUE(filesystem::is_directory(".FileOps_mkdir_new_dir"));
    filesystem::remove_all(".FileOps_mkdir_new_dir");
}

#ifndef WIN32
TEST(File, mkdir_will_return_false_if_requested_path_is_unwriteable)
{
    //given we have a path for a directory with no permissions
    filesystem::create_directories(".FileOps_mkdir_bad_perms");
    chmod(".FileOps_mkdir_bad_perms", 0x000);
    File file = ".FileOps_mkdir_bad_perms/test";

    //when we make the directory
    bool actual = file.mkdir();

    //then we get back false and the directory does not exist
    chmod(".FileOps_mkdir_bad_perms", 0x777);
    EXPECT_FALSE(actual);
    EXPECT_FALSE(filesystem::exists(".FileOps_mkdir_bad_perms/test"));
    filesystem::remove_all(".FileOps_mkdir_bad_perms");
}
#endif

TEST(File, mkdir_will_return_false_if_the_file_is_a_regular_file_and_not_edit_it)
{
    //given we have a path to a regular file
    ofstream regFile(".FileOps_mkdir_regular_file");
    regFile << "values";
    regFile.close();
    File file = ".FileOps_mkdir_regular_file";

    //when we try to make a directory
    bool actual = file.mkdir();

    //then we do not alter the file and return false
    EXPECT_FALSE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_mkdir_regular_file"));
    EXPECT_EQ(file.read(), "values");
    filesystem::remove_all(".FileOps_mkdir_regular_file");
}

TEST(File, mkdir_will_return_true_if_the_directory_already_exists)
{
    //given we have a directory that already exists
    filesystem::create_directories(".FileOps_mkdir_already_existing");
    File file = ".FileOps_mkdir_already_existing";

    //when we try to create the directory
    bool actual = file.mkdir();

    //then we get back true
    EXPECT_TRUE(actual);
    filesystem::remove_all(".FileOps_mkdir_already_existing");
}

TEST(File, mkdir_will_create_all_needed_directories)
{
    //given we want to create multiple directories
    File file = ".FileOps_mkdir_multi/directories/path";

    //when we try to make the path directory
    bool actual = file.mkdir();

    //then we get back true and the directories are made
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_mkdir_multi/directories/path"));
    filesystem::remove_all(".FileOps_mkdir_multi");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File remove tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, remove_will_delete_the_file_from_the_system)
{
    //given we have an existing file
    ofstream existingFile(".FileOps_remove_deletable_file");
    existingFile.close();
    File file = ".FileOps_remove_deletable_file";

    //when we try to remove the file
    bool actual = file.remove();

    //then we get back true and the file is removed
    EXPECT_TRUE(actual);
    EXPECT_FALSE(filesystem::exists(".FileOps_remove_deletable_file"));
}

#ifndef WIN32
TEST(File, remove_will_return_false_and_not_remove_the_file_if_permissions_are_not_granted)
{
    //given we have an existing file with bad permissions
    ofstream badFile(".FileOps_remove_bad_permissions");
    badFile.close();
    File file = ".FileOps_remove_bad_permissions";
    chmod(".FileOps_remove_bad_permissions", 0x111);

    //when we try to remove the file
    bool actual = file.remove();

    //then we get back false and do not remove the file
    chmod(".FileOps_remove_bad_permissions", 0x777);
    ASSERT_FALSE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_remove_bad_permissions"));
    filesystem::remove_all(".FileOps_remove_bad_permissions");
}
#endif

TEST(File, remove_will_delete_a_folder_with_things_in_it)
{
    //given we have a folder with stuff inside of it
    filesystem::create_directories(".FileOps_remove_multi/directories/and/stuff");
    File file = ".FileOps_remove_multi";

    //when we try to remove the file
    bool actual = file.remove();

    //then we get back true and everything is removed
    EXPECT_TRUE(actual);
    EXPECT_FALSE(filesystem::exists(".FileOps_remove_multi"));
}

TEST(File, remove_will_return_true_if_the_file_does_not_exist)
{
    //given we have a file that does not exist
    File file = ".FileOps_remove_does_not_exist";

    //when we try to remove the file
    bool actual = file.remove();

    //then we get back that the file is removed
    EXPECT_TRUE(actual);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////File isDirectory tests//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, isDirectory_will_return_true_if_the_file_is_a_directory)
{
    //given we have a directory
    filesystem::create_directories(".FileOps_isDirectory_directory");
    File file = ".FileOps_isDirectory_directory";

    //when we check if the file is a directory
    bool actual = file.isDirectory();

    //then we get back that the file is a directory
    EXPECT_TRUE(actual);
    filesystem::remove_all(".FileOps_isDirectory_directory");
}

TEST(File, isDirectory_will_return_false_if_the_file_is_not_a_directory)
{
    //given we have a regular file
    ofstream regularFile(".FileOps_isDirectory_regular_file");
    regularFile.close();
    File file = ".FileOps_isDirectory_regular_file";

    //when we check if the file is a directory
    bool actual = file.isDirectory();

    //then we get back that the file is not a directory
    EXPECT_FALSE(actual);
    filesystem::remove_all(".FileOps_isDirectory_regular_file");
}

#ifndef WIN32
TEST(File, isDirectory_will_return_false_if_we_dont_have_read_permissions)
{
    //given we have a folder with bad permissions
    filesystem::create_directories(".FileOps_isDirectory_bad_permissions");
    chmod(".FileOps_isDirectory_bad_permissions", 0x000);
    File file = ".FileOps_isDirectory_bad_permissions";

    //when we check if the file is a directory
    bool actual = file.isDirectory();

    //then we get back false
    chmod(".FileOps_isDirectory_bad_permissions", 0x777);
    EXPECT_FALSE(actual);
    filesystem::remove_all(".FileOps_isDirectory_bad_permissions");
}
#endif

TEST(File, isDirectory_will_return_false_if_the_file_does_not_exist)
{
    //given we have a file that does not exist
    File file = ".FileOps_isDirectory_does_not_exist";

    //when we check if the file is a directory
    bool actual = file.isDirectory();

    //we get back that the file is not a directory, and we do not create it
    EXPECT_FALSE(actual);
    EXPECT_FALSE(filesystem::exists(".FileOps_isDirectory_does_not_exist"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File getSize tests////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, getSize_will_return_negative_one_when_file_does_not_exist)
{
    //given we have a file that does not exist
    File file = ".FileOps_getSize_does_not_exist";

    //when we get the file size
    int size = file.getSize();

    //then we get back an error size
    EXPECT_EQ(size, -1);
}

TEST(File, getFileSize_will_not_create_a_File)
{
    //given we have a file that does not exist
    File file = ".FileOps_getSize_does_not_exist01";

    //when we get the file size
    file.getSize();
    
    //then we do not create the file
    EXPECT_FALSE(filesystem::exists(".FileOps_getSize_does_not_exist01"));
}

#ifndef WIN32
TEST(File, getSize_will_return_negative_if_we_do_not_have_permissions)
{
    // given we have a file with bad permissions
    ofstream badFile(".FileOps_getSize_bad_permissions");
    badFile.close();
    chmod(".FileOps_getSize_bad_permissions", 0x000);
    File file = ".FileOps_getSize_bad_permissions";

    //when we get the file size
    int actual = file.getSize();

    //then we get back an error size
    chmod(".FileOps_getSize_bad_permissions", 0x777);
    EXPECT_EQ(actual, -1);
    filesystem::remove_all(".FileOps_getSize_bad_permissions");
}
#endif

TEST(File, getSize_will_return_the_size_of_a_file)
{
    //given we have some files
    ofstream file0(".FileOps_getSize_size_00");
    file0 << "this is dr. jack bright.";
    file0.close();
    ofstream file1(".FileOps_getSize_size_01");
    file1.close();
    ofstream file2(".FileOps_getSize_size_02");
    file2 << "scp-000";
    file2.close();
    File f0 = ".FileOps_getSize_size_00";
    File f1 = ".FileOps_getSize_size_01";
    File f2 = ".FileOps_getSize_size_02";

    //when we get their file sizes
    int actual0 = f0.getSize();
    int actual1 = f1.getSize();
    int actual2 = f2.getSize();

    //then we get back the correct file sizes
    EXPECT_EQ(actual0, 24);
    EXPECT_EQ(actual1, 0);
    EXPECT_EQ(actual2, 7);
    filesystem::remove_all(".FileOps_getSize_size_00");
    filesystem::remove_all(".FileOps_getSize_size_01");
    filesystem::remove_all(".FileOps_getSize_size_02");
}

TEST(File, getSize_will_return_the_size_of_the_contents_of_a_directory_recursivly)
{
    //given we have a directory with contents
    filesystem::create_directories(".FileOps_getSize_folder/sub");
    filesystem::create_directories(".FileOps_getSize_folder/sub1/quail");
    ofstream stream1(".FileOps_getSize_folder/sub/txt1");
    stream1 << "here's some data";
    stream1.close();
    ofstream stream2(".FileOps_getSize_folder/quail.code");
    stream2 << "test";
    stream2.close();
    ofstream stream3(".FileOps_getSize_folder/sub1/quail.brb");
    stream3 << "123456789";
    stream3.close();
    ofstream stream4(".FileOps_getSize_folder/sub1/pickle.jpg");
    stream4 << "here is a pickle";
    stream4.close();
    ofstream stream5(".FileOps_getSize_folder/sub1/quail/something.jpg");
    stream5 << "this is a file";
    stream5.close();
    File file = ".FileOps_getSize_folder";

    //when we get the file size
    int actual = file.getSize();

    //then we get back the size of all the folder's contents
    EXPECT_EQ(actual, 59);
    filesystem::remove_all(".FileOps_getSize_folder");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////File copy tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, copy_will_create_a_file_if_destination_does_not_exist)
{
    //given we have a file to copy
    ofstream toCopy(".FileOps_copy_source00");
    toCopy << "I was stuck staring into the unknown. the inky black.";
    toCopy.close();
    File file = ".FileOps_copy_source00";

    //when we try to copy the file to a non-existing location
    bool actual = file.copy(".FileOps_copy_dest00");

    //then we get back true and the file is copied
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_source00"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_dest00"));
    EXPECT_EQ(file.read(),"I was stuck staring into the unknown. the inky black.");
    EXPECT_EQ(((File)".FileOps_copy_dest00").read(), "I was stuck staring into the unknown. the inky black.");
    filesystem::remove_all(".FileOps_copy_source00");
    filesystem::remove_all(".FileOps_copy_dest00");

}

TEST(File, copy_will_replace_the_contents_of_an_existing_file)
{
    //given we have an existing dest file with contents
    ofstream toCopy(".FileOps_copy_source01");
    toCopy << "Secure, contain, protect";
    toCopy.close();
    ofstream destination(".FileOps_copy_dest01");
    destination << "It has been recorded that there was an XK-class end of the world scenario";
    destination.close();
    File file = ".FileOps_copy_source01";

    //when we try to copy the file
    bool actual = file.copy(".FileOps_copy_dest01");

    //then we get back true and the contents is copied over the old
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_source01"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_dest01"));
    EXPECT_EQ(file.read(),"Secure, contain, protect");
    EXPECT_EQ(((File)".FileOps_copy_dest01").read(), "Secure, contain, protect");
    filesystem::remove_all(".FileOps_copy_source01");
    filesystem::remove_all(".FileOps_copy_dest01");
}

#ifndef WIN32
TEST(File, copy_file_will_return_false_and_do_nothing_if_source_file_cannot_be_read)
{
    //given we have a source file without read permissions
    ofstream toCopy(".FileOps_copy_source_bad");
    toCopy << "Secure, contain, protect";
    toCopy.close();
    chmod(".FileOps_copy_source_bad", 0x666);
    File file = ".FileOps_copy_source_bad";

    //when we try to copy the file
    bool actual = file.copy(".FileOps_copy_dest_bad");

    //then the file is not copied and we return false
    chmod(".FileOps_copy_source_bad", 0x777);
    EXPECT_FALSE(actual);
    EXPECT_FALSE(filesystem::exists(".FileOps_copy_dest_bad"));
    filesystem::remove_all(".FileOps_copy_source_bad");
}

TEST(File, copy_file_will_return_false_and_do_nothing_if_the_destination_cannot_be_written_to)
{
    //given we have a destination that cannot be written to
    ofstream toCopy(".FileOps_copy_source02");
    toCopy << "You do not have clearance to enter the chamber.";
    toCopy.close();
    ofstream bad(".FileOps_copy_dest_bad01");
    bad << "requires 05 clearance";
    bad.close();
    chmod(".FileOps_copy_dest_bad01", 0x555);
    File file = ".FileOps_copy_source02";

    //when we try to copy the file
    bool actual = file.copy(".FileOps_copy_dest_bad01");

    //then we get back false and nothing is changed
    chmod(".FileOps_copy_source02", 0x777);
    EXPECT_FALSE(actual);
    EXPECT_EQ(((File)".FileOps_copy_dest_bad01").read(), "requires 05 clearance");
    filesystem::remove_all(".FileOps_copy_dest_bad01");
    filesystem::remove_all(".FileOps_copy_source02");
}
#endif

TEST(File, copy_will_return_false_and_do_nothing_if_source_does_not_exist)
{
    //given we have a destination that does not exist
    File file = ".FileOps_copy_source_not_existing";

    //when we try to copy the file
    bool actual = file.copy(".FileOps_copy_dest_bad02");

    //then we get back false nd the file is not created
    EXPECT_FALSE(actual);
    EXPECT_FALSE(filesystem::exists(".FileOps_copy_dest_bad02"));
}

TEST(File, copy_will_recursively_copy_a_folder)
{
    //given we have a directory to copy with files in it
    filesystem::create_directories(".FileOps_copy_folder/sub");
    filesystem::create_directories(".FileOps_copy_folder/sub1/quail");
    ofstream stream1(".FileOps_copy_folder/sub/txt1");
    stream1 << "here's some data";
    stream1.close();
    ofstream stream2(".FileOps_copy_folder/quail.code");
    stream2 << "test";
    stream2.close();
    ofstream stream3(".FileOps_copy_folder/sub1/quail.brb");
    stream3 << "123456789";
    stream3.close();
    ofstream stream4(".FileOps_copy_folder/sub1/pickle.jpg");
    stream4 << "here is a pickle";
    stream4.close();
    ofstream stream5(".FileOps_copy_folder/sub1/quail/something.jpg");
    stream5 << "this is a file";
    stream5.close();
    File file = ".FileOps_copy_folder";

    //when we copy the folder to a new location
    bool actual = file.copy(".FileOps_copy_folder_dest");

    //then the whole folder and all files are copied
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_folder_dest"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/quail.code"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub/txt1"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1/quail.brb"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1/pickle.jpg"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1/quail"));
    EXPECT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1/quail/something.jpg"));
    filesystem::remove_all(".FileOps_copy_folder_dest");
    filesystem::remove_all(".FileOps_copy_folder");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////File write tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, write_will_return_false_if_the_file_is_a_directory)
{
    //Given we have a directory
    filesystem::create_directories(".FileOps_write_directory");
    File file = ".FileOps_write_directory";

    //When we try to write to the file
    bool actual = file.write("i dunno something");

    //Then we get back false
    EXPECT_FALSE(actual);
    filesystem::remove_all(".FileOps_write_directory");
}

TEST(File, write_will_create_the_file_if_it_does_not_exist)
{
    //Given we have a non-existing file
    File file = ".FileOps_write_non_existing";

    //When we try to write to the file
    bool actual = file.write("Here is a recording of incident SCP-682-5930.");

    //Then we get back true and the file is written with the desired contents
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_write_non_existing"));
    EXPECT_EQ(((File)".FileOps_write_non_existing").read(), "Here is a recording of incident SCP-682-5930.");
    filesystem::remove_all(".FileOps_write_non_existing");
}

TEST(File, write_will_overwrite_an_existing_file)
{
    //Given we have an existing file with contents
    ofstream existing(".FileOps_write_existing");
    existing << "this is a recount of the true SCP-001";
    existing.close();
    File file = ".FileOps_write_existing";

    //When we try to write to the file
    bool actual = file.write("[redacted]");

    //Then we get back true and the contents of the file is altered
    EXPECT_TRUE(actual);
    EXPECT_EQ(file.read(), "[redacted]");
    filesystem::remove_all(".FileOps_write_existing");
}

#ifndef WIN32
TEST(File, write_will_return_false_and_do_nothing_if_we_dont_have_write_permissions)
{
    //Given we have an existing file with bad permissions
    ofstream badFile(".FileOps_write_bad_perms");
    badFile << "this is a recount of the true SCP-001";
    badFile.close();
    chmod(".FileOps_write_bad_perms", 0x555);
    File file = ".FileOps_write_bad_perms";

    //When we try to write to the file
    bool actual = file.write("[redacted]");

    //Then we get back false and nothing is changed
    chmod(".FileOps_write_bad_perms", 0x777);
    EXPECT_FALSE(actual);
    EXPECT_EQ(file.read(), "this is a recount of the true SCP-001");
    filesystem::remove_all(".FileOps_write_bad_perms");
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////File append tests////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, append_will_return_false_if_the_file_is_a_directory)
{
    //Given we have a directory
    filesystem::create_directories(".FileOps_append_directory");
    File file = ".FileOps_append_directory";

    //When we try to append to the file
    bool actual = file.append("data");

    //Then we get back false
    EXPECT_FALSE(actual);
    filesystem::remove_all(".FileOps_append_directory");
}

TEST(File, append_will_create_a_file_if_it_does_not_exist)
{
    //Given we have a non-existing file
    File file = ".FileOps_append_non_existing";

    //when we try to append to the file
    bool actual = file.append("[redacted]");

    //then we create the file and return true
    EXPECT_TRUE(actual);
    EXPECT_TRUE(filesystem::exists(".FileOps_append_non_existing"));
    EXPECT_EQ(file.read(), "[redacted]");
    filesystem::remove_all(".FileOps_append_non_existing");
}

TEST(File, append_will_append_to_an_existing_file)
{
    //given we have an existing file with some contents
    ofstream existing(".FileOps_append_existing");
    existing << "We will brief you shortly on ";
    existing.close();
    File file = ".FileOps_append_existing";

    //when we append to the file
    bool actual = file.append("SCP-682");

    //then we get back true and append the data
    EXPECT_TRUE(actual);
    EXPECT_EQ(file.read(), "We will brief you shortly on SCP-682");
    filesystem::remove_all(".FileOps_append_existing");
}

#ifndef WIN32
TEST(File, append_will_return_false_and_do_nothing_if_we_do_not_have_write_permission)
{
    //given we have an existing folder with bad permissions
    ofstream badFile(".FileOps_append_bad_perms");
    badFile << "some text";
    badFile.close();
    chmod(".FileOps_append_bad_perms", 0x555);
    File file = ".FileOps_append_bad_perms";

    //when we append to the file
    bool actual = file.append("[redacted]");

    //then we get back false and nothing is changed
    chmod(".FileOps_append_bad_perms", 0x777);
    EXPECT_FALSE(actual);
    EXPECT_EQ(file.read(), "some text");
    filesystem::remove_all(".FileOps_append_bad_perms");
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////File read tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, read_will_return_empty_if_there_is_no_File)
{
    //given we have a file that does not exist
    File nonExistingFile = "/path/that/does/not/exist";

    //when we try to read the file
    string output = nonExistingFile.read();

    //then we get back a null pointer
    EXPECT_EQ(output, "");
}

TEST(File, read_will_not_create_file_if_it_does_not_exist)
{
    //given we provide a non-existing path
    File non_existingFile = "test.txt";

    //when we try to read the file
    non_existingFile.read();

    //then the file does not exist
    EXPECT_FALSE(filesystem::exists("test.txt"));
}

TEST(File, read_will_return_the_data)
{
    //given we provide an existing file with some data in it
    filesystem::create_directory(".FileOps_Read_test_temp");
    ofstream fileToRead(".FileOps_Read_test_temp/SCP-049.txt");
    fileToRead << "class: euclid";
    fileToRead.close();
    File notAFile = ".FileOps_Read_test_temp/SCP-049.txt";

    //when we try to read the file
    string output =  notAFile.read();

    //then we get back the contents of the file
    EXPECT_EQ(output, "class: euclid");
    filesystem::remove_all(".FileOps_Read_test_temp");
}

#ifndef WIN32
TEST(File, read_will_return_empty_if_the_file_has_bad_permissions)
{
    //given we provide a file with bad read permissions
    filesystem::create_directory(".FileOps_Read_test_temp_01");
    ofstream fileToRead(".FileOps_Read_test_temp_01/SCP-682.txt");
    fileToRead << "class: keter";
    fileToRead.close();
    chmod(".FileOps_Read_test_temp_01/SCP-682.txt", 0x00);
    File badPermissionFile = ".FileOps_Read_test_temp_01/SCP-682.txt";

    //when we try to read the file
    string output =  badPermissionFile.read();

    //then we get back the contents of the file
    EXPECT_EQ(output, "");

    chmod(".FileOps_Read_test_temp_01/SCP-682.txt", 0x777);
    filesystem::remove_all(".FileOps_Read_test_temp_01");
}
#endif

TEST(File, read_will_return_empty_if_the_file_is_a_folder)
{
    //given we have a directory
    filesystem::create_directory(".FileOps_read_directory");
    File file = ".FileOps_read_directory";

    //when we try to read the file
    string output = file.read();

    //then we get back empty
    EXPECT_EQ(output, "");
    filesystem::remove_all(".FileOps_read_directory");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////File readFirstNCharacters tests/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, readFirstNCharacters_will_only_read_the_first_specified_characters)
{
    //given we have a really, really long file
    ofstream longFile(".FileOps_ReadNChars_LongFile");
    longFile << "this is a very long file\n with some file breaks here and there\n";
    longFile.close();
    File file = ".FileOps_ReadNChars_LongFile";

    //when we read the first n bytes
    string actual = file.readFirstNCharacters(6);

    //then we get back the first 6 characters
    EXPECT_EQ(actual, "this i");
    filesystem::remove_all(".FileOps_ReadNChars_LongFile");
}

TEST(File, readFirstNCharacters_will_only_return_what_is_in_the_file_if_the_file_is_too_small)
{
    //given we have a short file
    ofstream shortFile(".FileOps_ReadNChars_ShortFile");
    shortFile << "apples";
    shortFile.close();
    File file = ".FileOps_ReadNChars_ShortFile";

    //when we read too many chars
    string actual = file.readFirstNCharacters(88);

    //then we get back what's in the file
    EXPECT_EQ(actual, "apples");
    filesystem::remove_all(".FileOps_ReadNChars_ShortFile");
}

TEST(File, readFirstNCharacters_will_return_whole_file_if_negative_size_is_passed_in)
{
    //given we have a file
    ofstream someFile(".FileOps_ReadNCharacters_full_file");
    someFile << "under no circumstances should SCP-009 breach containment";
    someFile.close();
    File file = ".FileOps_ReadNCharacters_full_file";

    //when we try to read a negative number of characters
    string actual = file.readFirstNCharacters(-1);

    //then we get back what's in the file
    EXPECT_EQ(actual, "under no circumstances should SCP-009 breach containment");
    filesystem::remove_all(".FileOps_ReadNCharacters_full_file");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////File readLastNCharacters tests/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
TEST(File, readLastNCharacters_will_only_read_the_last_specified_characters)
{
    //given we have a really, really long file
    ofstream longFile(".FileOps_ReadLastNChars_LongFile");
    longFile << "this is a very long file\n with some file breaks here and there\n";
    longFile.close();
    File file = ".FileOps_ReadLastNChars_LongFile";

    //when we read the last n bytes
    string actual = file.readLastNCharacters(6);

    //then we get back the last 6 characters
    EXPECT_EQ(actual, "here\r\n");
    filesystem::remove_all(".FileOps_ReadLastNChars_LongFile");
}
#else
TEST(File, readLastNCharacters_will_only_read_the_last_specified_characters)
{
    //given we have a really, really long file
    ofstream longFile(".FileOps_ReadLastNChars_LongFile");
    longFile << "this is a very long file\n with some file breaks here and there\n";
    longFile.close();
    File file = ".FileOps_ReadLastNChars_LongFile";

    //when we read the last n bytes
    string actual = file.readLastNCharacters(6);

    //then we get back the last 6 characters
    EXPECT_EQ(actual, "there\n");
    filesystem::remove_all(".FileOps_ReadLastNChars_LongFile");
}
#endif

TEST(File, readLastNCharacters_will_only_return_what_is_in_the_file_if_the_file_is_too_small)
{
    //given we have a short file
    ofstream shortFile(".FileOps_ReadLastNChars_ShortFile");
    shortFile << "apples";
    shortFile.close();
    File file = ".FileOps_ReadLastNChars_ShortFile";

    //when we read too many chars
    string actual = file.readLastNCharacters(88);

    //then we get back what's in the file
    EXPECT_EQ(actual, "apples");
    filesystem::remove_all(".FileOps_ReadLastNChars_ShortFile");
}

TEST(File, readLastNCharacters_will_return_whole_file_if_negative_size_is_passed_in)
{
    //given we have a file
    ofstream someFile(".FileOps_ReadLastNCharacters_full_file");
    someFile << "under no circumstances should SCP-009 breach containment";
    someFile.close();
    File file = ".FileOps_ReadLastNCharacters_full_file";

    //when we try to read a negative number of characters
    string actual = file.readLastNCharacters(-1);

    //then we get back what's in the file
    EXPECT_EQ(actual, "under no circumstances should SCP-009 breach containment");
    filesystem::remove_all(".FileOps_ReadLastNCharacters_full_file");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////File getPath tests///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, getPath_returns_the_whole_path_pointed_to_by_the_file)
{
    //given we have a file that points to a path
    File file = "some/path";

    //when we get the path
    string filePath = file.getPath();

    //then we get back the path
    EXPECT_EQ(filePath, "some/path");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////File getExtension tests////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, getExtension_will_return_the_extension_of_the_provided_file)
{
    //given we have a file with an extension
    File file = "some/textFile.txt";

    //when we get the extension
    string extension = file.getExtension();

    //then we get back the extension
    EXPECT_EQ(extension, ".txt");
}

TEST(File, getExtension_will_not_get_confused_by_multiple_periods_in_file_name)
{
    //given we have a file with multiple periods in the name
    File file = "some/complicated.shit.i.got.online.bob";

    //when we get the extension
    string extension = file.getExtension();

    //then we get back the extension
    EXPECT_EQ(extension, ".bob");
}

TEST(File, getExtension_will_return_empty_string_if_there_is_no_extension)
{
    //given we have a file without an extension
    File file = "some/linux/shit";

    //when we get the extension
    string extension = file.getExtension();

    //then we get back an empty string
    EXPECT_EQ(extension, "");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////File getNameWithoutExtension tests//////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, getNameWithoutExtension_will_get_the_name_of_the_file_without_a_path_or_extension)
{
    //given we have a file with an extension
    File file = "site-19/records/SCP-096.scp";

    //when we get the name
    string name = file.getNameWithoutExtension();

    //then we get back the name of the file
    EXPECT_EQ(name, "SCP-096");
}

TEST(File, getNameWithoutExtension_will_not_get_confused_by_multiple_periods_in_file_name)
{
    //given we have a file with multiple periods in the name
    File file = "site-19/records/SCP-000.1.345.delete_this.scp";

    //when we get the name
    string name = file.getNameWithoutExtension();

    //then we get back the name of the file
    EXPECT_EQ(name, "SCP-000.1.345.delete_this");
}

TEST(File, getNameWithoutExtension_will_get_the_name_of_a_file_that_does_not_have_an_extension)
{
    //given we have a file with no extensions
    File file = "site-19/records";

    //when we get the name
    string name = file.getNameWithoutExtension();

    //then we get back the name of the file
    EXPECT_EQ(name, "records");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////File list tests///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, list_will_list_all_files_in_a_directory)
{
    //given we have a directory with many files in it
    filesystem::create_directories(".FileOps_list_folder/sub");
    filesystem::create_directories(".FileOps_list_folder/sub1/quail");
    ofstream(".FileOps_list_folder/sub/txt1").close();
    ofstream(".FileOps_list_folder/quail.code").close();
    ofstream(".FileOps_list_folder/sub1/quail.brb").close();
    ofstream(".FileOps_list_folder/sub1/pickle.jpg").close();
    ofstream(".FileOps_list_folder/sub1/quail/something.jpg").close();
    File file = ".FileOps_list_folder";

    //when we try to list the files in the directory
    unordered_set<string> actual = file.list();

    //then we get back a list of files
    EXPECT_EQ(actual, (unordered_set<string>{".FileOps_list_folder" fileSeparator "sub", ".FileOps_list_folder" fileSeparator "sub1" fileSeparator "quail",
                                             ".FileOps_list_folder" fileSeparator "sub" fileSeparator "txt1", ".FileOps_list_folder" fileSeparator "quail.code",
                                             ".FileOps_list_folder" fileSeparator "sub1" fileSeparator "quail.brb", ".FileOps_list_folder" fileSeparator "sub1" fileSeparator "pickle.jpg",
                                             ".FileOps_list_folder" fileSeparator "sub1" fileSeparator "quail" fileSeparator "something.jpg",
                                             ".FileOps_list_folder" fileSeparator "sub1"}));
    filesystem::remove_all(".FileOps_list_folder");
}

TEST(File, list_will_run_a_function_on_each_path_if_provided)
{
    //given we have a directory with many files in it
    unordered_set<string> fileNames;
    filesystem::create_directories(".FileOps_list_folder_01/sub");
    filesystem::create_directories(".FileOps_list_folder_01/sub1/quail");
    ofstream(".FileOps_list_folder_01/sub/txt1").close();
    ofstream(".FileOps_list_folder_01/quail.code").close();
    ofstream(".FileOps_list_folder_01/sub1/quail.brb").close();
    ofstream(".FileOps_list_folder_01/sub1/pickle.jpg").close();
    ofstream(".FileOps_list_folder_01/sub1/quail/something.jpg").close();
    File file = ".FileOps_list_folder_01";

    //when we try to list the files and pass in a function
    file.list([&fileNames](const string& path){fileNames.insert(path.substr(path.find_last_of(fileSeparator)));});

    //then we execute the function on each file
    EXPECT_EQ(fileNames, (unordered_set<string>{fileSeparator "sub", fileSeparator "quail", fileSeparator "txt1", fileSeparator "quail.code", fileSeparator "quail.brb",
                                                fileSeparator "pickle.jpg", fileSeparator "something.jpg", fileSeparator "sub1"}));
    filesystem::remove_all(".FileOps_list_folder_01");
}

TEST(File , list_will_return_an_empty_list_if_the_file_does_not_exist)
{
    //given we have a file that does not exist
    File file = ".non_existing";

    //when we try to list the files
    unordered_set<string> actual = file.list();

    //then we get back an empty list
    EXPECT_EQ(actual, (unordered_set<string>{}));
}

TEST(File, list_will_return_an_empty_set_if_the_file_is_not_a_direcctory)
{
    //given we have a file that is not a directory
    ofstream(".52806336-61e0-48c3-8611-7ec9f7f614f5").close();
    const File file = ".52806336-61e0-48c3-8611-7ec9f7f614f5";

    //when we try to list the sub directories and files
    auto actual = file.list();

    //then we get back a list of just the file name
    EXPECT_EQ(actual, (unordered_set<string>{}));
    filesystem::remove_all(".52806336-61e0-48c3-8611-7ec9f7f614f5");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////