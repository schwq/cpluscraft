#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../Common.h"
#include "../LogSystem.h"

class Texture {
public:
	Texture(const char* texturePath, std::string name  = "texture", uint format = GL_RGB);
	Texture(std::vector<std::string> paths, std::string name = "texture", uint format = GL_RGB);
	Texture();
	
	Texture& operator=(Texture& tex) {
		if(this == &tex) {
			return *this;
		} else {
			this->textureID = tex.textureID;
			return *this;
		}
	}

	GLuint  getID();
private:
	GLuint  textureID;
	static uint textureCount;
	std::string name;
	
};

#endif