add_executable(Tests FileTest.c++
        TempFileTest.c++)

target_link_libraries(Tests GTest::gtest_main
        File
        TempFile
)

target_link_options(Tests PUBLIC -static -static-libgcc -static-libstdc++)

gtest_discover_tests(Tests)