#ifndef _SHADER_H_
#define _SHADER_H_

#include "../common.h"
#include "../error.h"
#include "../player/camera.h"

class Camera;

class Shader {
public:
	Shader(const char* vertexSource, const char* fragmentSource, const char* shaderName);
	Shader();
	~Shader();
	
	Shader& operator=(const Shader &shader) {
		Shader returnShader;
		returnShader.shaderProgramID = shader.shaderProgramID;
	}
	
	void useShader();
	void manifestShaderProperties(Camera& camera);
	GLuint getID();
	void setInt(const std::string& name, int value);
	void setBool(const std::string& name, bool value);
	void setFloat(const std::string& name, float value);
	void setMat4(const std::string& name, glm::mat4 value);
	void setVec3(const std::string& name, glm::vec3 value);
	void setVec2(const std::string& name, glm::vec2 value);
	void setVec4(const std::string& name, glm::vec4 value);
	void setUniform1i(const std::string& name, int value);	

	void setPointLightMax(int max) {
		if(max > 0 && max <= 16) {
			pointLightsMax = max;
		} else {
			logError("Warning: pointLightMax on Shader have reached the maximum limit!");
		}
	}

	int getPointLightMax() {
		return pointLightsMax;
	}

private:
	GLuint shaderProgramID;
	int pointLightsMax = 10;
	glm::vec3 pointLightPositions[4] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
    };

};


#endif
