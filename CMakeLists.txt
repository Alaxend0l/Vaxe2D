cmake_minimum_required(VERSION 3.0.0)
set(NAME Vaxe2D)
set(CMAKE_CXX_STANDARD 20)

project(${NAME} VERSION 0.0.1)

if (WIN32)
    add_subdirectory("third_party/glfw")
else()
    find_package(glfw3 3.3 REQUIRED)
endif()

set(ENTT_PATH "${CMAKE_SOURCE_DIR}/third_party/entt")
set(GLM_PATH "${CMAKE_SOURCE_DIR}/third_party/glm")

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(${NAME} ${SOURCES})

target_compile_features(${NAME} PUBLIC cxx_std_20)

# Includes

target_include_directories(${NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/source
    ${ENTT_PATH}
    ${GLM_PATH}
    )