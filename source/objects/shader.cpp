#include "shader.h"

Shader::Shader(const char* vertexSource, const char* fragmentSource, const char* shaderName) {

	unsigned int vertexShaderSource = 0;
	int vertexShaderSuccess;
	char vertexInfoLog[512];

	std::ifstream vertexFile = std::ifstream(vertexSource, std::ios_base::in | std::ios::ate);
	if (vertexFile.is_open()) {
		
		auto vertexFileSize = vertexFile.tellg();
		msgLog("Info: ", shaderName, " vertex shader file size: ", vertexFileSize);
		vertexFile.seekg(std::ios::beg);
		std::string vertexContent(vertexFileSize, 0);
		vertexFile.read(&vertexContent[0], vertexFileSize);

		const char * vertexReference = vertexContent.c_str();
		vertexShaderSource = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderSource, 1, &vertexReference, NULL);
		glCompileShader(vertexShaderSource);

		glGetShaderiv(vertexShaderSource, GL_COMPILE_STATUS, &vertexShaderSuccess);
		
		if (!vertexShaderSuccess) {
			glGetShaderInfoLog(vertexShaderSource, 512, NULL, vertexInfoLog);
			errorLog("Error: ", shaderName, " vertex shader compilation failed!, ", vertexInfoLog);
		}
		else {
			msgLog("Success: ", shaderName, " vertex shader compilation succeeded!");
		}

		vertexFile.close();
	}
	else {
		errorLog("Error: Cannot read ", shaderName, " vertex shader file!");
	}

	unsigned int fragmentShaderSource = 0;
	int fragmentShaderSuccess;
	char fragmentInfoLog[512];

	std::ifstream fragmentFile = std::ifstream(fragmentSource, std::ios_base::in | std::ios::ate);
	if (fragmentFile.is_open()) {

		auto fragmentFileSize = fragmentFile.tellg();
		msgLog("Info: ", shaderName, " fragment shader file size: ", fragmentFileSize);
		fragmentFile.seekg(std::ios::beg);
		std::string fragmentContent(fragmentFileSize, 0);
		fragmentFile.read(&fragmentContent[0], fragmentFileSize);

		const char* fragmentReference = fragmentContent.c_str();
		fragmentShaderSource = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderSource, 1, &fragmentReference, NULL);
		glCompileShader(fragmentShaderSource);

		glGetShaderiv(fragmentShaderSource, GL_COMPILE_STATUS, &fragmentShaderSuccess);

		if (!fragmentShaderSuccess) {
			glGetShaderInfoLog(fragmentShaderSource, 512, NULL, fragmentInfoLog);
			errorLog("Error: ", shaderName, " fragment shader compilation failed! ", fragmentInfoLog);
		}
		else {
			msgLog("Success: ", shaderName, " fragment shader compilation succeeded!");
		}

		fragmentFile.close();
	}
	else {
		errorLog("Error: Cannot read ", shaderName, " fragment shader file!");
	}

	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShaderSource);
	glAttachShader(shaderProgramID, fragmentShaderSource);
	glLinkProgram(shaderProgramID);

	int linkingSuccess;
	char linkingInfoLog[512];

	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linkingSuccess);
	if (!linkingSuccess) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, linkingInfoLog);
		errorLog("Error: ", shaderName, " linking failed! ", linkingInfoLog);
	}
	else {
		msgLog("Success: ", shaderName, " linking succeeded!");
	}

	glDeleteShader(vertexShaderSource);
	glDeleteShader(fragmentShaderSource);
}

void Shader::useShader() {
	glUseProgram(shaderProgramID);
}

unsigned int Shader::getID() {
	return shaderProgramID;
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}
void Shader::setBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value);
}
void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}
void Shader::setMat4(const std::string& name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setVec3(const std::string& name, glm::vec3 value) {
	glUniform3fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, glm::vec2 value) {
	glUniform2fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &value[0]);
}
void Shader::setUniform1i(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
}
void Shader::setVec4(const std::string& name, glm::vec4 value) {
	glUniform4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &value[0]);
}