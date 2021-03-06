cmake_minimum_required (VERSION 3.4)
set(CMAKE_GENERATOR_PLATFORM x64)

project (D3D12MA)

add_compile_options(/MP)

set (Headers
    "src/Common.h"
    "src/D3D12MemAlloc.h"
)

set (Source
    "src/D3D12MemAlloc.cpp"
    "src/Common.cpp"
)

# set ouput directory
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Bin)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/Bin/${OUTPUTCONFIG} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/Bin/${OUTPUTCONFIG} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/Bin/${OUTPUTCONFIG} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

add_library(${PROJECT_NAME} STATIC ${Headers} ${Source} )