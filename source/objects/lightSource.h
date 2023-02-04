#ifndef _LIGHTSOURCE_H_
#define _LIGHTSOURCE_H_

#include "error.h"
#include "common.h"
#include "shader.h"
#include "texture.h"

#define PRTLIGHTS_NUM_MAX 4

class LightSource {
public:

	void createDirLight();
	void createPtrLight();
	void createCbLight();
	void createSptLight();

	void update();
	void updateDirLight();
	void updatePtrLight();
	void updateCbLight();
	void createSptLight();

private:

	struct DirLight {
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct PtrLight {
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;
	};

	struct SptLight {
		glm::vec3 position;
		glm::vec3 direction;
		float cutOff;
		float outerCutOff;
		
		float constant;
		float linear;
		float quadratic;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct CubeLight {
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;
	};
	
};

#endif _LIGHTSOURCE_H_
