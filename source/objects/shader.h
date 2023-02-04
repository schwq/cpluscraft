#ifndef _SHADER_H_
#define _SHADER_H_

#include "../common.h"
#include "../error.h"

class Shader {
public:
	Shader(const char* vertexSource, const char* fragmentSource, const char* shaderName);
	Shader();
	
	Shader& operator=(const Shader &shader) {
		Shader returnShader;
		returnShader.shaderProgramID = shader.shaderProgramID;
	}
	
	void useShader();
	unsigned int getID();
	void setInt(const std::string& name, int value);
	void setBool(const std::string& name, bool value);
	void setFloat(const std::string& name, float value);
	void setMat4(const std::string& name, glm::mat4 value);
	void setVec3(const std::string& name, glm::vec3 value);
	void setVec2(const std::string& name, glm::vec2 value);
	void setVec4(const std::string& name, glm::vec4 value);
	void setUniform1i(const std::string& name, int value);	

private:
	unsigned int shaderProgramID;
};


#endif
