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
CameraIntersectObjects3D
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
        ${INCLUDE_DIR}/Ray2D.cpp
        ${INCLUDE_DIR}/Ray2D.hpp
        ${INCLUDE_DIR}/Shape2D.hpp
        ${INCLUDE_DIR}/Square2D.hpp
        ${INCLUDE_DIR}/Square2D.cpp
        ${INCLUDE_DIR}/GlutLibrary2D.hpp
        ${INCLUDE_DIR}/GlutLibrary2D.cpp
        ${INCLUDE_DIR}/Camera2D.hpp
        ${INCLUDE_DIR}/Camera2D.cpp
        ${INCLUDE_DIR}/Matrix2D.hpp
        ${INCLUDE_DIR}/Matrix2D.cpp
        ${INCLUDE_DIR}/Color.hpp
        ${INCLUDE_DIR}/Color.cpp
        ${INCLUDE_DIR}/ScrolBars.hpp
        ${INCLUDE_DIR}/ScrolBar.hpp
        ${INCLUDE_DIR}/Point3D.hpp
        ${INCLUDE_DIR}/Point3D.cpp
        ${INCLUDE_DIR}/Vector3D.hpp
        ${INCLUDE_DIR}/Vector3D.cpp
        ${INCLUDE_DIR}/Shape3D.hpp
        ${INCLUDE_DIR}/Matrix3D.hpp
        ${INCLUDE_DIR}/Matrix3D.cpp
        ${INCLUDE_DIR}/Ray3D.cpp
        ${INCLUDE_DIR}/Ray3D.hpp
        ${INCLUDE_DIR}/Circle3D.hpp
        ${INCLUDE_DIR}/Circle3D.cpp
        ${INCLUDE_DIR}/Camera3D.hpp
        ${INCLUDE_DIR}/Camera3D.cpp
        )
    target_link_libraries(${executable} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endforeach()