cmake_minimum_required(VERSION 2.9)

project(syntheseImage)

if(MSVC)
    add_compile_options(/std:c++17 /W4 /WX /DNDEBUG)
else()
    add_compile_options(-std=c++17 -Wall -W -Werror -DNDEBUG )
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})

set(executables
RayTracing
)

set(INCLUDE_DIR include)

set(SOURCE_DIR src)

foreach(executable ${executables})
    add_executable(
        ${executable} 
        ${SOURCE_DIR}/${executable}.cpp 
        ${INCLUDE_DIR}/Color.hpp
        ${INCLUDE_DIR}/Color.cpp
        ${INCLUDE_DIR}/ScrolBars.hpp
        ${INCLUDE_DIR}/ScrolBar.hpp
        ${INCLUDE_DIR}/Vector3D.hpp
        ${INCLUDE_DIR}/Vector3D.cpp
        ${INCLUDE_DIR}/Shape3D.hpp
        ${INCLUDE_DIR}/Matrix3D.hpp
        ${INCLUDE_DIR}/Matrix3D.cpp
        ${INCLUDE_DIR}/Ray3D.cpp
        ${INCLUDE_DIR}/Ray3D.hpp
        ${INCLUDE_DIR}/Sphere3D.hpp
        ${INCLUDE_DIR}/Sphere3D.cpp
        ${INCLUDE_DIR}/Cube3D.hpp
        ${INCLUDE_DIR}/Cube3D.cpp
        ${INCLUDE_DIR}/Camera3D.hpp
        ${INCLUDE_DIR}/Camera3D.cpp
        ${INCLUDE_DIR}/GlutLibrary3D.hpp
        ${INCLUDE_DIR}/GlutLibrary3D.cpp
        ${INCLUDE_DIR}/Light3D.hpp
        ${INCLUDE_DIR}/Point.hpp
        )
    target_link_libraries(${executable} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endforeach()