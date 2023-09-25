# Stilt Fox&trade; Scribe
Stilt Fox&trade; scribe is a C++ library designed to make dealing with files and other related IO tasks easier. This convenience
library used to be a part of Stilt Fox&trade; universal library, however was split into its own repository for better maintainability.
This Library won't be updated often as well, reading a file doesn't change often. So unless a bug is discovered, or new functionality
is required, this library should stay rather static.

## Legal Stuff
Stilt Fox&trade; is not liable for any damages done to your hardware. For more information see LICENSE file.\
Stilt Fox&trade; is trademarked. You may not use the Stilt Fox™ name, however this code is free to reference and use.\
You may contribute to this library, however all contributions will share the same license as this library and you agree that Stilt Fox&trade; owns the copyright for any contributions.

## Prerequisites
- CMake
  - version 3.0.0 or greater
- C++ compiler
  - must support C++ version 20 or higher
  - We at Stilt Fox&trade; tend to use g++
- GTests
  - This is only required for unit testing, and can be skipped
    - To skip, use the `SFSkipTesting=true` option when compiling
  - You can obtain GTest by using `sudo apt install libgtest-dev`
    - if you are not running debian based linux, or are allergic to apt... it can be found [here](https://github.com/google/googletest)

## Installation
The following commands will install the libraries to your system. These will exist globally to all users. If you wish to
install for a single user, please adjust accordingly. Also, you will require sudo privileges to run the `cmake --install .`
command.
>mkdir build\
>cd build\
>cmake .. -DSFSkipTesting=true -DCMAKE_BUILD_TYPE=Release\
>cmake --build .\
>cmake --install .\
>cd .j

## Cross Compiling For Windows
Because this project was made primarily for Linux based systems, getting the libraries running on windows can be tricky. Several configurations need to be made that Linux simply does not need.

### Prerequisites
- CMake
  - version 3.0.0 or greater
- C++ compiler
  - must support C++ version 20 or higher
  - must be mingw using a posix threading system
    - example: `x86_64-w64-mingw32-g++-posix`

### Setup
#### Compiler and Toolchain
The first order of business should be getting your compiler and toolchain up and running. To make this happen you first need to install the mingw compiler onto your computer.\
`sudo apt install g++-mingw-w64 gcc-mingw-w64` \
#### Installing GTest for Windows
Because we are running on Linux, by default only the Linux binaries for the GTest library are available on the repo and we will have to compile the GTest library from scratch. \
1. clone GTest from the github repo [here](https://github.com/google/googletest)
2. copy the toolchain file from [toolchains/windows.toolchain](toolchains)

## Linking to Stilt Fox&trade; Scribe
Linking to Stilt Fox&trade; scribe is easy. In your CMakeLists.txt file include the following line:\
`find_package(Scribe)`\
then to link to your project use the following line:\
`target_link_libraries(MyProject StiltFox::Scribe::File StiltFox::Scribe::TempFile)`\
please notice that each module you want to link must be linked separately as shown above. There is no way to just include all
modules. This allows you to include only what you need in your build.

## Tutorials and Examples
If you want to see the classes of Stilt Fox&trade; Scribe, feel free to check out the [test folder](test). All public methods
are thoroughly unit tested, and also demonstrate intended usage of the classes.