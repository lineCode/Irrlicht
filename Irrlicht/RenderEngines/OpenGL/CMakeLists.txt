set(_IRR_DYNAMIC_ false)

if(_IRR_DYNAMIC_)
  set(LIBTYPE SHARED)
else(_IRR_DYNAMIC_)
 set(LIBTYPE STATIC)
endif(_IRR_DYNAMIC_)

include_directories(
${CMAKE_CURRENT_SOURCE_DIR}
${OPENGL_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/dep/include
${CMAKE_SOURCE_DIR}/contrib/IrrLicht
${CMAKE_SOURCE_DIR}/contrib/IrrLicht/include
${CMAKE_SOURCE_DIR}
)

file(GLOB_RECURSE OpenGL_Source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.c *.h *.hpp *.vert *.frag)

file(GLOB_RECURSE RESOURCE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.vert *.frag)

#resource_prebuild(
#    TARGET "OpenGL"
#    GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/.Resource"
#    SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}"
#    RESOURCE_FILES ${RESOURCE_SRCS}
#    OUT_MODULE_SOURCE RESOURCE_MODULE_SOURCE
#    OUT_GENERATED_FILES RESOURCE_GENERATED_FILES
#    OUT_SRC RESOURCE_GENERATED_SOURCES
#)
#
#LIST(APPEND OpenGL_Source ${RESOURCE_GENERATED_FILES})

CreateLibrary("OpenGL" "${OpenGL_Source}" "${LIBTYPE}" "" "")

add_dependencies(OpenGL ZLIB)

#resource_build(
#    TARGET "OpenGL"
#    GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/.Resource"
#    SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}"
#    SOURCE_FILE "${CMAKE_CURRENT_BINARY_DIR}/.Resource/Resource_OpenGL.dsc"
#    MODULE_SOURCE_FILE ${RESOURCE_MODULE_SOURCE}
#    RESOURCE_FILES ${RESOURCE_SRCS}
#    GENERATED_FILES ${RESOURCE_GENERATED_FILES}
#    RESOURCE_EXECUTABLE ${ResourceCompilerExecutable}
#)

if(_IRR_DYNAMIC_)
    target_link_libraries (OpenGL ${OPENGL0_LIBRARY} ${OPENGL1_LIBRARY} Winmm ZLIB)
    install(TARGETS OpenGL DESTINATION ${CMAKE_INSTALL_PREFIX})
else()
    add_definitions(-D_LIB_SOURCE_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")
    add_definitions(-D_IRR_COMPILE_WITH_OPENGL_)
    add_definitions(-DIRRLICHT_EXPORTS)
endif(_IRR_DYNAMIC_)

set_target_properties(OpenGL
    PROPERTIES
      FOLDER
        "RenderEngine/IrrLicht")