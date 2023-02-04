#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../common.h"
#include "../error.h"

class Texture {
public:
	Texture(const char* texturePath, unsigned int format = GL_RGB);
	Texture() = default;
	void defaultConfiguration();
	unsigned int getID();
private:
	unsigned int textureID;

};

#endif