cmake_minimum_required (VERSION 2.8)
project (LFSRNoiseUgens)

include_directories(${SC_PATH}/include/plugin_interface)
include_directories(${SC_PATH}/include/common)
include_directories(${SC_PATH}/external_libraries/libsndfile/)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SHARED_MODULE_PREFIX "")
if(APPLE OR WIN32)
    set(CMAKE_SHARED_MODULE_SUFFIX ".scx")
endif()

set(SOURCE_FILES LFSRNoise.cpp LFSRNoise.hpp)

add_library(LFSRNoise MODULE ${SOURCE_FILES})
