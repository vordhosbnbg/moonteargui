cmake_minimum_required (VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project (moonteargui)

find_package (Threads)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(PugiXML REQUIRED)

file(GLOB_RECURSE Project_SOURCES "src/*.cpp")
file(GLOB_RECURSE Project_HEADERS "src/*.h")
set (Smoketest_SOURCES "test/smoketest.cpp")
set (Project_INCLUDE_DIRS "")

foreach (_headerFile ${Project_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Project_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES Project_INCLUDE_DIRS)

include_directories(${Project_INCLUDE_DIRS}
                    ${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${pugixml_DIR})

add_library (moonteargui SHARED ${Project_SOURCES})
add_executable(smoketest ${Smoketest_SOURCES})

set_property(TARGET moonteargui PROPERTY CXX_STANDARD 14)
set_property(TARGET smoketest PROPERTY CXX_STANDARD 14)
target_link_libraries (smoketest
                       moonteargui
                       ${SDL2_LIBRARIES}
                       ${SDL2_IMAGE_LIBRARY}
                       ${SDL2_TTF_LIBRARY}
                       ${PUGIXML_LIBRARIES}
                       ${CMAKE_THREAD_LIBS_INIT})

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-march=native" HAS_FLAG_MARCH_NATIVE)
if (HAS_FLAG_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
endif()

CHECK_CXX_COMPILER_FLAG("-mtune=native" HAS_FLAG_MTUNE_NATIVE)
if (HAS_FLAG_MTUNE_NATIVE)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mtune=native")
endif()

CHECK_CXX_COMPILER_FLAG("-pthread" HAS_FLAG_PTHREAD)
if (HAS_FLAG_PTHREAD)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -pthread")
endif()
