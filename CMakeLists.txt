cmake_minimum_required(VERSION 3.1)

set(TARGET OpenGLViewer)
project(${TARGET})

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "~/ClionProjects/OpenGLViewer/build")
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/opencv/2.4.12_2")
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/open-mesh")
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt5/5.6.0")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenMesh REQUIRED)

file(GLOB_RECURSE ${TARGET}_HEADERS src/*.h)
file(GLOB_RECURSE ${TARGET}_SOURCES src/*.cpp)

add_executable(${TARGET}
        ${${TARGET}_SOURCES}
        ${${TARGET}_HEADERS} )

set(LIBS ${LIBS} ${OPENMESH_LIBRARIES})

include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${OPENMESH_INCLUDE_DIRS}
)

target_link_libraries(${TARGET}
        ${OPENGL_LIBRARY}
        ${OpenCV_LIBS}
        ${LIBS}
        Qt5::Widgets
        Qt5::OpenGL)


set(CMAKE_PREFIX_PATH "../test/mydll.dll")

# searching for library file
find_library(MYDLL_LIBRARY mydll)

if (MYDLL_LIBRARY)
    # you may need that if further action in your CMakeLists.txt depends
    # on detecting your library
    set(MYDLL_FOUND TRUE)

    # you may need that if you want to conditionally compile some parts
    # of your code depending on library availability
    #add_definitions(-DHAVE_LIBSIFTGPU=1)

    # those two, you really need
    #include_directories(${SIFTGPU_INCLUDE_DIR})
    set(YOUR_LIBRARIES ${YOUR_LIBRARIES} ${MYDLL_LIBRARY})
endif ()