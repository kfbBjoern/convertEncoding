set (PROJECT_NAME convertEncoding)

cmake_minimum_required(VERSION 3.10)
set (PROJECT_NAME convertEncoding)


# set the project name and version
project(convertEncoding VERSION 0.1.0.0)

# Settings

# C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
else()
    set(CMAKE_CXX_COMPILER "/usr/bin/g++-8")
endif()                           


# Include
set(PROJECT_INCLUDE "../include/")


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
target_link_libraries(${PROJECT_NAME} stdc++fs )                           
