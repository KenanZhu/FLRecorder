cmake_minimum_required(VERSION 3.10)
project(FLRecorder)

# SET STANDARD
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ADD EXECUTABLE FILE
add_executable(${PROJECT_NAME}
    MainLoop.cpp
    CmdForge/CmdForge.cpp
    Depends/Cmns.cpp
    FileHandle/FileHandle.cpp
    LogTypes/LogTypes.cpp
)

# INCLUDE HEADER DIR
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/CmdForge
    ${CMAKE_CURRENT_SOURCE_DIR}/Depends
    ${CMAKE_CURRENT_SOURCE_DIR}/FileHandle
    ${CMAKE_CURRENT_SOURCE_DIR}/LogTypes
)
