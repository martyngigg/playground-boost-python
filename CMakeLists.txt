cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(playground-boost-python)

# Use dynamic linking
set(BUILD_SHARED_LIBS ON)

# Remove optimizations
foreach(_flag
    -O2
    -ftree-vectorize
    -fstack-protector-strong
    -fvisibility-inlines-hidden
    -fno-plt
)
  string(REPLACE ${_flag} "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endforeach()

# Add other debug flags
if(CMAKE_SYSTEM_NAME MATCHES Darwin)
  set(_cxx_flags_debug_platform "-glldb -fstandalone-debug")
elseif(CMAKE_SYSTEM_NAME MATCHES Linux)
  set(_cxx_flags_debug_platform "-g3 -ggdb -fno-eliminate-unused-debug-symbols -fno-inline-small-functions")
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-fno-inline-functions  ${_cxx_flags_debug_platform} ${CMAKE_CXX_FLAGS_DEBUG}")

# We don't want auto_ptr...
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_NO_AUTO_PTR")

# External dependencies (binary)
find_package(Boost 1.84.0
  EXACT
  REQUIRED
)

# Boost Python expects public targets for every boost library but the binary
# distribution only exports interface targets for compiled libraries
# We alias our own to Boost::boost
foreach(_lib
    align
    bind
    config
    conversion
    core
    detail
    foreach
    function
    iterator
    lexical_cast
    mpl
    numeric_conversion
    preprocessor
    smart_ptr
    static_assert
    tuple
    type_traits
    utility
    graph
    integer
    property_map)
  if(NOT TARGET Boost::${_lib})
    add_library(Boost::${_lib} ALIAS Boost::boost)
  endif()
endforeach()

# External dependencies (source)
include(FetchContent)
FetchContent_Declare(boostpy_src
  GIT_REPOSITORY https://github.com/boostorg/python.git
  GIT_TAG boost-1.84.0
)
FetchContent_MakeAvailable(boostpy_src)
FetchContent_GetProperties(boostpy_src SOURCE_DIR BOOSTPY_SOURCE_DIR)

add_subdirectory(test)
