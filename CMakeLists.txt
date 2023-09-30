cmake_minimum_required(VERSION 3.27)
project(GMath VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
include(CTest)
enable_testing()


# muparser
include(FetchContent)

FetchContent_Declare(
    muparser
    GIT_REPOSITORY https://github.com/beltoforion/muparser.git
    GIT_TAG v2.3.4
    SOURCE_SUBDIR no
)
FetchContent_MakeAvailable(muparser)

file(GLOB muparser_src ${muparser_SOURCE_DIR}/src/*.cpp)

add_library(GMath SHARED
    src/GMath.cpp
    ${muparser_src}
)

target_include_directories(GMath PRIVATE 
    include/
    ${muparser_SOURCE_DIR}/include/
)
add_definitions(-DMUPARSER_STATIC)

if(WIN32)
    add_definitions(-DOS_Windows)
ENDIF()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(Output_Bin_Dir "${CMAKE_SOURCE_DIR}/out/")

add_custom_command(TARGET GMath POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${Output_Bin_Dir}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${Output_Bin_Dir}/"
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/GMath ${Output_Bin_Dir}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:GMath> ${Output_Bin_Dir}/extensions/GMath
)