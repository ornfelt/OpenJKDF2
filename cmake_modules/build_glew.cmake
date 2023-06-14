set(GLEW_ROOT ${CMAKE_BINARY_DIR}/glew)
ExternalProject_Add(
    GLEW
    SOURCE_DIR          ${CMAKE_SOURCE_DIR}/lib/glew
    BINARY_DIR          ${GLEW_ROOT}
    INSTALL_DIR         ${GLEW_ROOT}
    UPDATE_DISCONNECTED TRUE
    CMAKE_ARGS          --toolchain ${CMAKE_TOOLCHAIN_FILE}
                        --install-prefix ${GLEW_ROOT}
                        -DCMAKE_BUILD_TYPE:STRING=Release
                        -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
                        -Dglew-cmake_BUILD_SHARED:BOOL=FALSE
                        -DONLY_LIBS:BOOL=TRUE
)
# *Replicate* variables generated by `FindGLEW`
set(GLEW_FOUND TRUE)
set(GLEW_VERSION 2.2.0)
set(GLEW_INCLUDE_DIRS ${GLEW_ROOT}/include)
set(GLEW_STATIC_LIBRARIES glew)
set(GLEW_SHARED_LIBRARIES glew-shared)
if(GLEW_USE_STATIC_LIBS)
    set(GLEW_LIBRARIES ${GLEW_STATIC_LIBRARIES})
else()
    set(GLEW_LIBRARIES ${GLEW_SHARED_LIBRARIES})
endif()
# *Replicate* targets generated by `FindGLEW`
add_library(GLEW::glew SHARED IMPORTED)
add_dependencies(GLEW::glew GLEW)
file(MAKE_DIRECTORY ${GLEW_INCLUDE_DIRS})
set_target_properties(
    GLEW::glew PROPERTIES
    IMPORTED_LOCATION
    ${GLEW_ROOT}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}${GLEW_SHARED_LIBRARIES}${CMAKE_SHARED_LIBRARY_SUFFIX}
    IMPORTED_IMPLIB
    ${GLEW_ROOT}/lib/${CMAKE_IMPORT_LIBRARY_PREFIX}${GLEW_SHARED_LIBRARIES}${CMAKE_IMPORT_LIBRARY_SUFFIX}
)
target_include_directories(GLEW::glew INTERFACE ${GLEW_INCLUDE_DIRS})
target_link_directories(GLEW::glew INTERFACE ${GLEW_INCLUDE_DIRS}/../lib)
if(GLEW_USE_STATIC_LIBS)
    add_library(GLEW::glew_s STATIC IMPORTED)
    add_dependencies(GLEW::glew_s GLEW)
    set_property(
        TARGET GLEW::glew_s
        PROPERTY IMPORTED_LOCATION
        ${GLEW_ROOT}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${GLEW_STATIC_LIBRARIES}${CMAKE_STATIC_LIBRARY_SUFFIX}
    )
    target_compile_definitions(GLEW::glew_s INTERFACE GLEW_STATIC)
    target_include_directories(GLEW::glew_s INTERFACE ${GLEW_INCLUDE_DIRS})
    target_link_directories(GLEW::glew_s INTERFACE ${GLEW_INCLUDE_DIRS}/../lib)
    if(TARGET_WIN32)
        target_link_libraries(GLEW::glew_s INTERFACE opengl32)
    endif()
    add_library(GLEW::GLEW ALIAS GLEW::glew_s)
else()
    add_library(GLEW::GLEW ALIAS GLEW::glew)
endif()
