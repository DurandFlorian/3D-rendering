cmake_minimum_required(VERSION 3.19)

project(syntheseImage)

if(MSVC)
    add_compile_options(/std:c++17 /W4 /WX)
else()
    add_compile_options(-std=c++17 -Wall -W -Werror)
endif()

list(APPEND CMAKE_PREFIX_PATH C:/Users/flori/freeglut)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})

set(executables
    RayProjection
)

set(INCLUDE_DIR include)

set(SOURCE_DIR src)

foreach(executable ${executables})
    add_executable(
        ${executable} 
        ${SOURCE_DIR}/${executable}.cpp 
        ${INCLUDE_DIR}/Vector2D.hpp
        ${INCLUDE_DIR}/Vector2D.cpp
        ${INCLUDE_DIR}/Point2D.hpp
        ${INCLUDE_DIR}/Point2D.cpp
        ${INCLUDE_DIR}/ControllablePoints.hpp
        ${INCLUDE_DIR}/ControllablePoints.cpp
        ${INCLUDE_DIR}/Circle2D.hpp
        ${INCLUDE_DIR}/Circle2D.cpp
        ${INCLUDE_DIR}/Ray2D.hpp
        ${INCLUDE_DIR}/Ray2D.cpp
        ${INCLUDE_DIR}/Square2D.hpp
        ${INCLUDE_DIR}/Square2D.cpp
        ${INCLUDE_DIR}/GlutLibrary2D.hpp
        ${INCLUDE_DIR}/GlutLibrary2D.cpp
        )
    target_link_libraries(${executable} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endforeach()