add_executable(Tests FileTest.c++
        TempFileTest.c++
        BufferedFileTest.c++
        ConfigFileTest.c++
)

target_link_libraries(Tests GTest::gtest_main
        File
        TempFile
        BufferedFile
        ConfigFile
)

if (CMAKE_SYSTEM_NAME STREQUAL Windows)
 target_link_options(Tests PUBLIC -static -static-libgcc -static-libstdc++)
endif ()

gtest_discover_tests(Tests)