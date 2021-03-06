# Use c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Use -std=c++14 instead of -std=gnu++14
set(CXX_EXTENSIONS OFF)

message( STATUS "Selected Generator: ${CMAKE_GENERATOR}")

if ( WIN32 )
    message( STATUS "64bit compile is present: ${CMAKE_CL_64}")
endif ()

if(DEBUG)
  message(STATUS "Build in debug-mode   : Yes")
  set(USE_STD_MALLOC 1)
  set(CMAKE_BUILD_TYPE ${BDT_NAME})
else()
  set(CMAKE_BUILD_TYPE ${BRT_NAME})
  message(STATUS "Build in debug-mode   : No  (default)")
endif()
if(MEMCHECK)
  message(STATUS "Build in memory-checker   : Yes")
  add_definitions(-DMEMCHECK=1)
  set(USE_STD_MALLOC 1)
else()
  message(STATUS "Build in memory-checker   : No  (default)")
endif()
message("")

message("Setup Platform Environment:")

# check what platform we're on (64-bit or 32-bit), and create a simpler test than CMAKE_SIZEOF_VOID_P
if(CMAKE_SIZEOF_VOID_P MATCHES 8 OR FORCE_X64)
    set(PLATFORM 64)
    set(PLATFORM_NAME ${PLATFORM_NAME_X86_64})
    MESSAGE(STATUS "Detected 64-bit platform")
else()
    set(PLATFORM 32)
    set(PLATFORM_NAME ${PLATFORM_NAME_X86})
    MESSAGE(STATUS "Detected 32-bit platform")
endif()

include("${CMAKE_SOURCE_DIR}/cmake/platform/settings.cmake")

if(WIN32)
  include("${CMAKE_SOURCE_DIR}/cmake/platform/win/settings.cmake")
elseif(APPLE)
  include("${CMAKE_SOURCE_DIR}/cmake/platform/osx/settings.cmake")
elseif(UNIX)
  include("${CMAKE_SOURCE_DIR}/cmake/platform/unix/settings.cmake")
endif()
message("Finish")
message("")
