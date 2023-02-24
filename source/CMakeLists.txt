set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0)

set(project_name cpluscraft)
project(&{project_name})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(IMGUI_SRC
        libs/imgui/imgui_impl_opengl3.h
        libs/imgui/imgui_impl_opengl3.cpp
        libs/imgui/imgui_impl_opengl3_loader.h
        libs/imgui/imgui_impl_glfw.h
        libs/imgui/imgui_impl_glfw.cpp
        libs/imgui/imgui.h
        libs/imgui/imgui.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_tables.cpp
        libs/imgui/imgui_widgets.cpp
        libs/imgui/imgui_demo.cpp
        )

set(source_files  
main.cpp 
${IMGUI_SRC}
world/terrain.cpp 
audio/musicBuffer.cpp 
audio/soundDevices.cpp 
world/skybox.cpp  
editor/window.cpp 
player/playerUI.cpp 
player/camera.cpp 
game.cpp common.cpp 
objects/shapes.cpp 
objects/mesh.cpp 
objects/model.cpp 
objects/shader.cpp 
objects/texture.cpp 
libs/glad.c)

add_executable(${project_name} ${source_files})
target_link_libraries(${project_name} glfw dl GLU glut assimp sndfile alut openal)
add_definitions(-w)
