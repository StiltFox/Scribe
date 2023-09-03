add_executable(Tests FileTest.c++
        TempFileTest.c++)

target_link_libraries(Tests GTest::gtest_main
        File
        TempFile
)

gtest_discover_tests(Tests)