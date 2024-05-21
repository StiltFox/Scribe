add_library(ConfigFile ConfigFile.c++)
target_link_libraries(ConfigFile File)
set_target_properties(ConfigFile PROPERTIES PUBLIC_HEADER "modules/config_file/ConfigFile.h++")
target_include_directories(ConfigFile PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")