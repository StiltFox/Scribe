add_library(BufferedFile BufferedFile.c++)
target_link_libraries(BufferedFile File)
set_target_properties(BufferedFile PROPERTIES PUBLIC_HEADER "modules/buffered_file/BufferedFile.h++")
target_include_directories(File PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")