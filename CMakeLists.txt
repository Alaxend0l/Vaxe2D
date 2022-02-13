cmake_minimum_required(VERSION 3.6)
set(NAME Vaxe2D)
set(CMAKE_CXX_STANDARD 20)

project(${NAME} VERSION 0.0.1)



set(ENTT_PATH "${CMAKE_SOURCE_DIR}/third_party/entt")
set(IMGUI_PATH "${CMAKE_SOURCE_DIR}/third_party/imgui")
set(GLM_PATH "${CMAKE_SOURCE_DIR}/third_party/glm")
set(PUGIXML_PATH "${CMAKE_SOURCE_DIR}/third_party/pugixml/src")


file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(${NAME} ${SOURCES})
target_compile_features(${NAME} PUBLIC cxx_std_20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
link_libraries(${SDL2_LIBRARY_DIR})

# SDL2_Image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_libraries(${SDL2_IMAGE_LIBRARY_DIR})

# GLM
include_directories(${GLM_PATH})

# PUGIXML
include_directories(${PUGIXML_PATH})
#add_library(${PUGIXML_PATH}/pugixml.cpp)


# OPENGL

if (WIN32)
    find_package(OpenGL REQUIRED COMPONENTS OpenGL)
else()
    find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL)
endif()
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARY_DIR})

# GLEW

if (WIN32)
    set(GLEW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/glew-2.1.0/include")
    set(GLEW_LIBRARIES "${CMAKE_SOURCE_DIR}/third_party/glew-2.1.0/lib/Release/x64/glew32s")
else()
    find_package(GLEW)
endif()
include_directories(${GLEW_INCLUDE_DIR})
#link_libraries(${GLEW_LIBRARIES})

# ImGui

# Compile as static library 
file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp ${IMGUI_PATH}/backends/imgui_impl_sdl.cpp ${IMGUI_PATH}/backends/imgui_impl_sdlrenderer.cpp ${IMGUI_PATH}/misc/cpp/imgui_stdlib.cpp) 
add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH} ${IMGUI_PATH}/backends ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
target_link_libraries("ImGui" PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

target_link_libraries(${NAME} PUBLIC
    ImGui
    ) 

# Includes

target_include_directories(${NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/source
    ${ENTT_PATH}
    
   
    )






