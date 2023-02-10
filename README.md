# Minecraft clone made in C++ and OpenGL 3.3

### Files and folders explained:

```main.cpp```: Main file

```common.h```: Includes and globals

```error.h```: Log error and Log msg functions

```callback.h```: Callbacks functions for opengl

#### Resources folder:
```Models/ models files``` (.obj and textures)

```Textures/ texture files``` for rendering world

```Shaders/ shaders files``` .glsl

#### Player folder:
```camera.h```: Camera file player and utils

#### Objects folder:
```lightSource.h```: Lights sources creation file, write to glsl shaders

```mesh.h```: manipulate meshes from models

```model.h```: loads models

```shader.h```: file for shader compilation and creation

```texture.h```: file for custom textures compilation and creation

```shapes.h```: basic shapes creation (cube, sphere, triangule)

#### World/ 
```render.h```: render multiple shapes together
```world.h```: main file for manipulating the entire world

#### Editor folder:
```window.h```: Imgui and glfw file

#### Libraries used:
```GLAD```
```OPENGL 3.3```
```GLFW3```
```ASSIMP model load```
```MAKE```

#### Future implemetations:
```Networking (multiplayer)```
```Serial save state```
```Saves```
```Custom configuration```
```Colision```
```Skyboxs```
```Multiple textures```
```Player GUI```
```Controls```
```Tools```
```Editor```
```Log window```
