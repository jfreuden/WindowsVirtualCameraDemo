cmake_minimum_required(VERSION 4.1)
project(VirtualCameraDemo)

set(CMAKE_CXX_STANDARD 20)

add_executable(VirtualCameraDemo main.cpp)

target_link_libraries(VirtualCameraDemo
        PRIVATE
        mfsensorgroup.lib
#        mfplat.lib
#        mf.lib
#        mfuuid.lib
#        shlwapi.lib
#        ole32.lib
)
