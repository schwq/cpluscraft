#include "shader.h"

Shader::~Shader() {
	glDeleteProgram(shaderProgramID);
}

Shader::Shader(const char* vertexSource, const char* fragmentSource, const char* shaderName) {

	unsigned int vertexShaderSource = 0;
	int vertexShaderSuccess;
	char vertexInfoLog[512];

	std::ifstream vertexFile = std::ifstream(vertexSource, std::ios_base::in | std::ios::ate);
	if (vertexFile.is_open()) {
		
		auto vertexFileSize = vertexFile.tellg();
		logMessage("Info: ", shaderName, " vertex shader file size: ", vertexFileSize);
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
			logError("Error: ", shaderName, " vertex shader compilation failed!, ", vertexInfoLog);
		}
		else {
			logMessage("Success: ", shaderName, " vertex shader compilation succeeded!");
		}

		vertexFile.close();
	}
	else {
		logError("Error: Cannot read ", shaderName, " vertex shader file!");
	}

	unsigned int fragmentShaderSource = 0;
	int fragmentShaderSuccess;
	char fragmentInfoLog[512];

	std::ifstream fragmentFile = std::ifstream(fragmentSource, std::ios_base::in | std::ios::ate);
	if (fragmentFile.is_open()) {

		auto fragmentFileSize = fragmentFile.tellg();
		logMessage("Info: ", shaderName, " fragment shader file size: ", fragmentFileSize);
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
			logError("Error: ", shaderName, " fragment shader compilation failed! ", fragmentInfoLog);
		}
		else {
			logMessage("Success: ", shaderName, " fragment shader compilation succeeded!");
		}

		fragmentFile.close();
	}
	else {
		logError("Error: Cannot read ", shaderName, " fragment shader file!");
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
		logError("Error: ", shaderName, " linking failed! ", linkingInfoLog);
	}
	else {
		logMessage("Success: ", shaderName, " linking succeeded!");
	}

	glDeleteShader(vertexShaderSource);
	glDeleteShader(fragmentShaderSource);
}

void Shader::manifestShaderProperties(Camera& camera) {

	setVec3("source_dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	setVec3("source_dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	setVec3("source_dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	setVec3("source_dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	
	// point light 1
	setVec3("source_ptrLight[0].position", pointLightPositions[0]);
	setVec3("source_ptrLight[0].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	setVec3("source_ptrLight[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	setVec3("source_ptrLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	setFloat("source_ptrLight[0].constant", 1.0f);
	setFloat("source_ptrLight[0].linear", 0.09f);
	setFloat("source_ptrLight[0].quadratic", 0.032f);
	// point light 2
	setVec3("source_ptrLight[1].position", pointLightPositions[1]);
	setVec3("source_ptrLight[1].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	setVec3("source_ptrLight[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	setVec3("source_ptrLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	setFloat("source_ptrLight[1].constant", 1.0f);
	setFloat("source_ptrLight[1].linear", 0.09f);
	setFloat("source_ptrLight[1].quadratic", 0.032f);
	// point light 3
	setVec3("source_ptrLight[2].position", pointLightPositions[2]);
	setVec3("source_ptrLight[2].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	setVec3("source_ptrLight[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	setVec3("source_ptrLight[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	setFloat("source_ptrLight[2].constant", 1.0f);
	setFloat("source_ptrLight[2].linear", 0.09f);
	setFloat("source_ptrLight[2].quadratic", 0.032f);
	// point light 4
	setVec3("source_ptrLight[3].position", pointLightPositions[3]);
	setVec3("source_ptrLight[3].ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	setVec3("source_ptrLight[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	setVec3("source_ptrLight[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	setFloat("source_ptrLight[3].constant", 1.0f);
	setFloat("source_ptrLight[3].linear", 0.09f);
	setFloat("source_ptrLight[3].quadratic", 0.032f);
	
	// source_sptLight
	setVec3("source_sptLight.position", camera.getPosition());
	setVec3("source_sptLight.direction", camera.getDirection());
	setVec3("source_sptLight.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
	setVec3("source_sptLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	setVec3("source_sptLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	setFloat("source_sptLight.constant", 1.0f);
	setFloat("source_sptLight.linear", 0.09f);
	setFloat("source_sptLight.quadratic", 0.032f);
	setFloat("source_sptLight.cutOff", glm::cos(glm::radians(12.5f)));
	setFloat("source_sptLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	
	setVec3("source_cbLight.position", glm::vec3(1.0f)); 
	setVec3("source_cbLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	setVec3("source_cbLight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	setVec3("source_cbLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	setFloat("source_cbLight.constant", 1.0f);
	setFloat("source_cbLight.linear", 0.09f);
	setFloat("source_cbLight.quadratic", 0.032f);
}

void Shader::useShader() {
	glUseProgram(shaderProgramID);
}

GLuint Shader::getID() {
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