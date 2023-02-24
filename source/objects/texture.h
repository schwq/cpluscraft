#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../common.h"
#include "../error.h"

class Texture {
public:
	Texture(const char* texturePath, std::string name  = "texture", unsigned int format = GL_RGB);
	Texture(std::vector<std::string> paths, std::string name = "texture", unsigned int format = GL_RGB);
	Texture();
	
	Texture& operator=(Texture& tex) {
		if(this == &tex) {
			return *this;
		} else {
			this->textureID = tex.textureID;
			return *this;
		}
	}

	GLuint getID();
private:
	GLuint textureID;
	static unsigned int textureCount;
	std::string name;
	
};

#endif