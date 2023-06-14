set(ZLIB_${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}_ROOT
    ${CMAKE_BINARY_DIR}/zlib/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}
)
set(ZLIB_ROOT ${ZLIB_${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}_ROOT})
set(ZLIB_TARGET_NAME ZLIB_${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})
set(ZLIB_BINARY_DIR ${ZLIB_${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}_ROOT})
set(ZLIB_TOOLCHAIN_ARG "--toolchain ${CMAKE_TOOLCHAIN_FILE}")
set(ZLIB_USE_STATIC_LIBS TRUE)

set(ZLIB_INSTALL_DIR ${ZLIB_BINARY_DIR})
ExternalProject_Add(
    ${ZLIB_TARGET_NAME}
    SOURCE_DIR          ${CMAKE_SOURCE_DIR}/lib/zlib
    BINARY_DIR          ${ZLIB_BINARY_DIR}
    INSTALL_DIR         ${ZLIB_INSTALL_DIR}
    UPDATE_DISCONNECTED TRUE
    CMAKE_ARGS          --install-prefix ${ZLIB_INSTALL_DIR}
                        ${ZLIB_TOOLCHAIN_ARG}
                        -DCMAKE_BUILD_TYPE:STRING=Release
                        -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
)
# *Replicate* variables generated by `FindZLIB`
set(ZLIB_FOUND TRUE)
set(ZLIB_INCLUDE_DIRS ${ZLIB_ROOT}/include)
set(ZLIB_LIBRARIES z)
if(TARGET_WIN32 OR CMAKE_HOST_WIN32 AND TARGET_WIN32)
    if(ZLIB_USE_STATIC_LIBS)
        set(ZLIB_LIBRARIES zlibstatic)
    else()
        set(ZLIB_LIBRARIES zlib)
    endif()
endif()
set(ZLIB_VERSION 1.2.13)
# Legacy vars, for the sake of completeness
set(ZLIB_VERSION_STRING ${ZLIB_VERSION})
string(REGEX REPLACE "^([0-9]+).*" "\\1" ZLIB_VERSION_MAJOR ${ZLIB_VERSION})
set(ZLIB_MAJOR_VERSION ${ZLIB_VERSION_MAJOR})
string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1" ZLIB_VERSION_MINOR ${ZLIB_VERSION})
set(ZLIB_MINOR_VERSION ${ZLIB_VERSION_MINOR})
string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" ZLIB_VERSION_PATCH ${ZLIB_VERSION})
set(ZLIB_PATCH_VERSION ${ZLIB_VERSION_PATCH})
set(ZLIB_VERSION_PATCH_TWEAK 0)

# *Replicate* targets generated by `FindZLIB`
file(MAKE_DIRECTORY ${ZLIB_INCLUDE_DIRS})
if(ZLIB_USE_STATIC_LIBS)
    add_library(ZLIB::ZLIB STATIC IMPORTED)
    set_property(
        TARGET ZLIB::ZLIB
        PROPERTY IMPORTED_LOCATION
        ${ZLIB_ROOT}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${ZLIB_LIBRARIES}${CMAKE_STATIC_LIBRARY_SUFFIX}
    )
else()
    add_library(ZLIB::ZLIB SHARED IMPORTED)
    set_target_properties(
        ZLIB::ZLIB PROPERTIES
        IMPORTED_LOCATION
        ${ZLIB_ROOT}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}${ZLIB_LIBRARIES}${CMAKE_SHARED_LIBRARY_SUFFIX}
        IMPORTED_IMPLIB
        ${ZLIB_ROOT}/lib/${CMAKE_IMPORT_LIBRARY_PREFIX}${ZLIB_LIBRARIES}${CMAKE_IMPORT_LIBRARY_SUFFIX}
    )
    target_include_directories(ZLIB::ZLIB INTERFACE ${ZLIB_INCLUDE_DIR})
    target_link_directories(ZLIB::ZLIB INTERFACE ${ZLIB_INCLUDE_DIR}/../lib)
endif()
add_dependencies(ZLIB::ZLIB ${ZLIB_TARGET_NAME})
