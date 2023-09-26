cmake_minimum_required(VERSION 3.0.0)
project(Scribe VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if(NOT SFSkipTesting)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(test)
endif()

add_subdirectory(modules)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/ScribeConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Scribe
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/ScribeConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/ScribeConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Scribe
)

install(
        TARGETS File TempFile
        EXPORT Scribe
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/Stilt_Fox/Scribe
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/Stilt_Fox/Scribe
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/Stilt_Fox/Scribe
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Stilt_Fox/Scribe
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Stilt_Fox/Scribe
)

install(EXPORT Scribe
        FILE ScribeTargets.cmake
        NAMESPACE StiltFox::Scribe::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Scribe
)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/ScribeConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
)