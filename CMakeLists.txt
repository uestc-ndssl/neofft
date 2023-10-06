cmake_minimum_required(VERSION 3.16)

# --- Project settings ---

# ------ Project name ------
project(neofft)

# ------ Standard ------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------ Test ------
include(CTest)

enable_testing()

# ------ Build tool ------
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_GENERATOR "Unix Makefiles")

# ------ Build type ------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo") # default build type
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(__DEBUG__) # set __DEBUG__ for debug release
endif()
if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  add_compile_definitions(__DEBUG__) # set __DEBUG__ for debug release
endif()
if(CMAKE_BUILD_TYPE STREQUAL "RelWithSizeOp")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Oz -pipe -fno-math-errno -flto=auto")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oz -pipe -fno-math-errno -flto=auto")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -fno-math-errno -flto=auto")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -fno-math-errno -flto=auto")
endif()

# --- Dependencies ---
# ------ cmake module ------
include(cmake/CPM.cmake)
include(ExternalProject)
set(FETCHCONTENT_QUIET FALSE)
# ------ third party libs ------
# --------- zlib 1.3 ---------
# Compile zlib for
# cpmaddpackage(
#   NAME ZLIB
#   VERSION 1.3
#   URL "http://zlib.net/zlib-1.3.tar.gz"
# )
# --------- fftw 3.3.10 ---------
# fftw does not fully support CMake
ExternalProject_Add(
  fftw
  URL http://www.fftw.org/fftw-3.3.10.tar.gz
  PREFIX     ${CMAKE_BINARY_DIR}/_deps/fftw/prefix
  SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/fftw/src
  BINARY_DIR ${CMAKE_BINARY_DIR}/_deps/fftw/build
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  CONFIGURE_COMMAND 
    ${CMAKE_BINARY_DIR}/_deps/fftw/src/configure
    --enable-shared
    --prefix=${CMAKE_CURRENT_BINARY_DIR}/_deps/fftw
)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/_deps/fftw/src/api)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/fftw/lib)
# --------- boost 1.83 ---------
cpmaddpackage(
    NAME Boost
    VERSION 1.83.0
    URL "https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.gz"
    OPTIONS
    "CMAKE_BUILD_TYPE Release"
)
# --------- hdf5 1.12.2 ---------
cpmaddpackage(
  NAME HDF5
  VERSION 1.12.2
  URL "https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.12/hdf5-1.12.2/src/hdf5-1.12.2.tar.gz"
  OPTIONS
  "BUILD_TESTING OFF"
  "DEFAULT_API_VERSION v112"
  "HDF5_ENABLE_DEPRECATED_SYMBOLS OFF"
  "HDF5_BUILD_TOOLS OFF"
  "HDF5_BUILD_EXAMPLES OFF"
  "HDF5_BUILD_CPP_LIB ON"
  "HDF5_BUILD_HL_LIB OFF"
  "HDF5_BUILD_UTILS OFF"
)
# Unset some vars otherwise hdf5 taint project
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "" CACHE STRING "unset" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "" CACHE STRING "unset" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "" CACHE STRING "unset" FORCE)
set(CMAKE_Fortran_MODULE_DIRECTORY "" CACHE STRING "unset" FORCE)
# --- Sub directory ---
# ------ Include dir ------
include_directories(include)
# ------ source code ------
# add_subdirectory(src)
# ------ Application ------
# add_subdirectory(app)
# ------ unit   test ------
add_subdirectory(test)