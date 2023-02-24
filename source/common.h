#ifndef _COMMON_H_
#define _COMMON_H_

// Common
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

// OpenGL and GLFW window, GLM mathematics
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
// Assimp model importing
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifdef defined(_WIN32) || defined(__CYGWIN__)  
#include <Windows.h>
#endif

// Globals
extern const char* operatingSystemType;
extern std::string projectPath;
extern std::string currentOSPath(const char* windowsRelativePath, const char* UnixRelativePath);
extern std::string searchShader(std::string shaderName);
extern std::string searchTexture(std::string textureName); 
extern std::string searchModel(std::string modelName); 
extern std::string searchMusic(std::string musicName);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#endif
