set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0)

set(project_name cpluscraft)
project(&{project_name})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(IMGUI_SRC
        Libraries/imgui/imgui_impl_opengl3.h
        Libraries/imgui/imgui_impl_opengl3.cpp
        Libraries/imgui/imgui_impl_opengl3_loader.h
        Libraries/imgui/imgui_impl_glfw.h
        Libraries/imgui/imgui_impl_glfw.cpp
        Libraries/imgui/imgui.h
        Libraries/imgui/imgui.cpp
        Libraries/imgui/imgui_draw.cpp
        Libraries/imgui/imgui_tables.cpp
        Libraries/imgui/imgui_widgets.cpp
        Libraries/imgui/imgui_demo.cpp
        )

set(source_files  
main.cpp 
${IMGUI_SRC}
World/TerrainGenerator.cpp 
Audio/MusicBuffer.cpp 
Audio/SoundDevices.cpp 
World/Skybox.cpp  
Editor/Window.cpp 
Player/PlayerUI.cpp 
Player/Camera.cpp 
Game.cpp 
Common.cpp 
Globals.cpp
Objects/Shapes.cpp 
Objects/Mesh.cpp 
Objects/Model.cpp 
Objects/Shader.cpp 
Objects/Texture.cpp 
Objects/Blocks/Blocks.cpp
Physics/BlockCollision.cpp
Libraries/glad.c)

add_executable(${project_name} ${source_files})
target_link_libraries(${project_name} glfw dl GLU glut assimp sndfile openal)
add_definitions(-w)
