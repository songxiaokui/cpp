cmake_minimum_required(VERSION 3.10)
project(dataSet3 VERSION 0.1.0)
set(VTK_DIR /opt/libs/vtk/lib/cmake/vtk-8.2/)


message(STATUS "VTK_DIR=${VTK_DIR}")

aux_source_directory(${PROJECT_SOURCE_DIR} DIR_SRCS)

file(GLOB SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/src/*.h*")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${DIR_SRCS})

target_link_libraries(${PROJECT_NAME}
        ${VTK_LIBRARIES})