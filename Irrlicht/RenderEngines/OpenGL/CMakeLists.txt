set(_IRR_DYNAMIC_ false)

if(_IRR_DYNAMIC_)
  set(LIBTYPE SHARED)
else(_IRR_DYNAMIC_)
 set(LIBTYPE STATIC)
endif(_IRR_DYNAMIC_)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIRS}
    #${ZLIB_INCLUDE_DIR}
    #${CMAKE_SOURCE_DIR}
    #${CMAKE_SOURCE_DIR}/dep/include
    #${CMAKE_SOURCE_DIR}/contrib/IrrLicht
    #${CMAKE_SOURCE_DIR}/contrib/IrrLicht/include
)

file(GLOB_RECURSE OpenGL_Source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.c *.h *.hpp *.vert *.frag)
file(GLOB_RECURSE RESOURCE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.vert *.frag)

if (BUILD_HAS_RESOURCE_SYSTEM)
    resource_prebuild(
        TARGET "IrrOpenGL"
        GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/.Resource"
        SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}"
        RESOURCE_FILES ${RESOURCE_SRCS}
        OUT_MODULE_SOURCE RESOURCE_MODULE_SOURCE
        OUT_GENERATED_FILES RESOURCE_GENERATED_FILES
        OUT_SRC RESOURCE_GENERATED_SOURCES
    )
    
    LIST(APPEND OpenGL_Source ${RESOURCE_GENERATED_FILES})
endif (BUILD_HAS_RESOURCE_SYSTEM)

CreateLibrary(IrrOpenGL "${OpenGL_Source}" "${LIBTYPE}" "" "")
add_dependencies(IrrOpenGL ZLIB)
target_link_libraries (IrrOpenGL
    OpenGL::GL
    ZLIB
    Glslang)

if (BUILD_HAS_RESOURCE_SYSTEM)
    target_link_libraries (IrrOpenGL
        CFramework)

    resource_build(
        TARGET "IrrOpenGL"
        GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/.Resource"
        SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}"
        SOURCE_FILE "${CMAKE_CURRENT_BINARY_DIR}/.Resource/Resource_OpenGL.dsc"
        MODULE_SOURCE_FILE ${RESOURCE_MODULE_SOURCE}
        RESOURCE_FILES ${RESOURCE_SRCS}
        GENERATED_FILES ${RESOURCE_GENERATED_FILES}
        RESOURCE_EXECUTABLE ${ResourceCompilerExecutable}
    )
endif (BUILD_HAS_RESOURCE_SYSTEM)

if(_IRR_DYNAMIC_)
    target_link_libraries (IrrOpenGL
        irrlicht)
    IF (WIN32)
        target_link_libraries (IrrOpenGL winmm)
    ENDIF(WIN32)
    install(TARGETS IrrOpenGL DESTINATION ${CMAKE_INSTALL_PREFIX})
else()
    add_definitions(-D_LIB_SOURCE_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")
    add_definitions(-D_IRR_COMPILE_WITH_OPENGL_)
    add_definitions(-DIRRLICHT_EXPORTS)
    
    target_link_libraries (IrrOpenGL LINK_INTERFACE_LIBRARIES
        irrlicht
    )
endif(_IRR_DYNAMIC_)

set_target_properties(IrrOpenGL
    PROPERTIES
      FOLDER
        "RenderEngine/IrrLicht")
