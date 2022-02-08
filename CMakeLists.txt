cmake_minimum_required(VERSION 3.0.0)
set(NAME Vaxe2D)
set(CMAKE_CXX_STANDARD 20)

project(${NAME} VERSION 0.0.1)

if (WIN32)
    add_subdirectory("third_party/glfw")
else()
    find_package(SDL2 REQUIRED)
endif()

set(ENTT_PATH "${CMAKE_SOURCE_DIR}/third_party/entt")

find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL)
find_package(GLEW)
find_package(glm)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(${NAME} ${SOURCES})

target_compile_features(${NAME} PUBLIC cxx_std_20)

# Includes

target_include_directories(${NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/source
    ${ENTT_PATH}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR}
    )

target_link_libraries(${NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES}) 