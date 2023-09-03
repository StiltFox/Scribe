add_library(File File.c++)
set_target_properties(File PROPERTIES PUBLIC_HEADER "modules/file/File.h++")
target_include_directories(File PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")