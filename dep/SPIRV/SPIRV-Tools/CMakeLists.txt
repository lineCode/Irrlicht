# Copyright (c) 2015-2016 The Khronos Group Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#cmake_minimum_required(VERSION 2.8.12)
#if (POLICY CMP0048)
#  cmake_policy(SET CMP0048 NEW)
#endif()
#if (POLICY CMP0054)
#  # Avoid dereferencing variables or interpret keywords that have been
#  # quoted or bracketed.
#  # https://cmake.org/cmake/help/v3.1/policy/CMP0054.html
#  cmake_policy(SET CMP0054 NEW)
#endif()

set(SPIRV_TOOLS "SPIRV-Tools")

include(GNUInstallDirs)
include(cmake/setup_build.cmake)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  add_definitions(-DSPIRV_LINUX)
  set(SPIRV_TIMER_ENABLED ON)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  add_definitions(-DSPIRV_WINDOWS)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "CYGWIN")
  add_definitions(-DSPIRV_WINDOWS)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
  add_definitions(-DSPIRV_MAC)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Android")
  add_definitions(-DSPIRV_ANDROID)
  set(SPIRV_TIMER_ENABLED ON)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
  add_definitions(-DSPIRV_FREEBSD)
else()
  message(FATAL_ERROR "Your platform '${CMAKE_SYSTEM_NAME}' is not supported!")
endif()

if (${SPIRV_TIMER_ENABLED})
  add_definitions(-DSPIRV_TIMER_ENABLED)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug")
endif()


option(SPIRV_BUILD_COMPRESSION "Build SPIR-V compressing codec" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

option(SPIRV_COLOR_TERMINAL "Enable color terminal output" ON)
if(${SPIRV_COLOR_TERMINAL})
  add_definitions(-DSPIRV_COLOR_TERMINAL)
endif()

option(SPIRV_LOG_DEBUG "Enable excessive debug output" OFF)
if(${SPIRV_LOG_DEBUG})
  add_definitions(-DSPIRV_LOG_DEBUG)
endif()

if (DEFINED SPIRV_TOOLS_EXTRA_DEFINITIONS)
  add_definitions(${SPIRV_TOOLS_EXTRA_DEFINITIONS})
endif()

function(spvtools_default_compile_options TARGET)
  target_compile_options(${TARGET} PRIVATE ${SPIRV_WARNINGS})

  if (${COMPILER_IS_LIKE_GNU})
    target_compile_options(${TARGET} PRIVATE
      -std=c++11 -fno-exceptions -fno-rtti)
    target_compile_options(${TARGET} PRIVATE
      -Wall -Wextra -Wno-long-long -Wshadow -Wundef -Wconversion
      -Wno-sign-conversion)
    # For good call stacks in profiles, keep the frame pointers.
    if(NOT "${SPIRV_PERF}" STREQUAL "")
      target_compile_options(${TARGET} PRIVATE -fno-omit-frame-pointer)
    endif()
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      set(SPIRV_USE_SANITIZER "" CACHE STRING
        "Use the clang sanitizer [address|memory|thread|...]")
      if(NOT "${SPIRV_USE_SANITIZER}" STREQUAL "")
        target_compile_options(${TARGET} PRIVATE
          -fsanitize=${SPIRV_USE_SANITIZER})
      endif()
    else()
      target_compile_options(${TARGET} PRIVATE
         -Wno-missing-field-initializers)
    endif()
  endif()

  if (MSVC)
    # Specify /EHs for exception handling. This makes using SPIRV-Tools as
    # dependencies in other projects easier.
    target_compile_options(${TARGET} PRIVATE /EHs)
  endif()

  # For MinGW cross compile, statically link to the C++ runtime.
  # But it still depends on MSVCRT.dll.
  if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
      set_target_properties(${TARGET} PROPERTIES
        LINK_FLAGS -static -static-libgcc -static-libstdc++)
    endif()
  endif()
endfunction()

#if(NOT COMMAND find_host_package)
#  macro(find_host_package)
#    find_package(${ARGN})
#  endmacro()
#endif()
#if(NOT COMMAND find_host_program)
#  macro(find_host_program)
#    find_program(${ARGN})
#  endmacro()
#endif()
#
#find_host_package(PythonInterp)

# Check for symbol exports on Linux.
# At the moment, this check will fail on the OSX build machines for the Android NDK.
# It appears they don't have objdump.
macro(spvtools_check_symbol_exports TARGET)
if (NOT "${SPIRV_SKIP_TESTS}")
    message("Skipping symbol exports test for ${TARGET}")
endif()
endmacro()

set(SPIRV_SKIP_TESTS ON)

add_subdirectory(external)

#if (TARGET effcee)
#  add_definitions(-DSPIRV_EFFCEE)
#endif()

add_subdirectory(source)
