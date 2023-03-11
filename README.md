# Minecraft clone made in C++ and OpenGL 3.3

### Files and folders explained:

```main.cpp```: Main file

```Common.h```: Includes and globals

```LogSystem.h```: Log error and Log msg functions

```callback.h```: Callbacks functions for opengl

#### Resources folder:
```Models/ models files``` (.obj and textures)

```Textures/ texture files``` for rendering world

```Shaders/ shaders files``` .glsl

#### Player folder:
```Camera.h```: Camera file player and utils

#### Objects folder:
```lightSource.h```: Lights sources creation file, write to glsl shaders

```Mesh.h```: manipulate meshes from models

```Model.h```: loads models

```Shader.h```: file for shader compilation and creation

```Texture.h```: file for custom textures compilation and creation

```Shapes.h```: basic shapes creation (cube, sphere, triangule)

#### World/ 
```render.h```: render multiple shapes together
```world.h```: main file for manipulating the entire world

#### Editor folder:
```Window.h```: Imgui and glfw file

#### Libraries used:
```GLAD```
```OPENGL 3.3```
```GLFW3```
```ASSIMP model load```
```MAKE```

