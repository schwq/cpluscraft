#ifndef _LIGHTSOURCE_H_
#define _LIGHTSOURCE_H_

#include "error.h"
#include "common.h"
#include "shader.h"
#include "texture.h"

class LightSource {
public:

	LightSource();

private:

	glm::vec3 lightColor;
	glm::vec3 lightPosition;


};

#endif _LIGHTSOURCE_H_
