set (PROJECT_NAME convertEncoding)


cmake_minimum_required(VERSION 3.10)
set (PROJECT_NAME convertEncoding)


# set the project name and version
project(convertEncoding VERSION 0.2.0)
# Settings

# C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    set(DEFINE_SYMBOL WIN32)
else()
    set(CMAKE_CXX_COMPILER "/usr/bin/g++-8")
endif()                           


# Include
message(${PROJECT_SOURCE_DIR})
set(PROJECT_INCLUDE "../Include/")
message(${PROJECT_INCLUDE})
configure_file(${PROJECT_INCLUDE}/version.hpp.in ${PROJECT_BINARY_DIR}/version.hpp)
include_directories(${PROJECT_BINARY_DIR})
##include_directories(${PROJECT_INCLUDE})

# Pre Build steps

add_executable(${PROJECT_NAME}  main.cpp 
                                handleOptions.cpp
                                handleFiles.cpp
                                )

target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "../Include"
                           )
                        
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()                           

# Add Libraries for filesystem
if (MSVC)
else()
    target_link_libraries(${PROJECT_NAME} stdc++fs )
endif()
