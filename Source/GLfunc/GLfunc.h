#ifndef _GLFUNC_H_
#define _GLFUNC_H_

#include "../Common.h"
#include "../LogSystem.h"

template<typename Type> 
void genVertexAttrib(GLuint &VAO, GLuint &VBO, uint* sizeofBuffer, GLenum glTypeDraw, uint firstGroup, uint secondGroup, uint thirdGroup, Type dataType);

#endif