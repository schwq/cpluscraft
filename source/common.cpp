#include "common.h"
#include "error.h"

#if defined(_WIN32) || defined(__CYGWIN__)  
const char* operatingSystemType = "WIN32";
#elif defined(__linux__) || defined(__APPLE__)
const char* operatingSystemType = "UNIX";
#endif

std::string projectPath = std::filesystem::current_path().string();

std::string currentOSPath(const char* windowsRelativePath, const char* UnixRelativePath) {

	if(projectPath.find("build") != std::string::npos) {
		std::replace(projectPath.begin(), projectPath.end(), 'build', 'source');
	}
		if (operatingSystemType == "WIN32") {
			return std::string(projectPath + windowsRelativePath);
		}
		else if (operatingSystemType == "UNIX") {
			return std::string(projectPath + UnixRelativePath);
		}
		else {
			logError("Error: Cannot find Operating System to get current project path! (common.cpp)");
			return std::string("ErrorPath!");
		}
}

std::string searchShader(std::string shaderName) {
	std::string unixCopy = shaderName;
	std::replace(shaderName.begin(), shaderName.end(), '/', '\\');
	return currentOSPath(("\\source\\resources\\shaders\\" + shaderName).c_str(), ("/resources/shaders/" + unixCopy).c_str());
}
std::string searchTexture(std::string textureName) {
	std::string unixCopy = textureName;
	std::replace(textureName.begin(), textureName.end(), '/', '\\');
	return currentOSPath(("\\source\\resources\\textures\\" + textureName).c_str(), ("/resources/textures/" + unixCopy).c_str());
}
std::string searchModel(std::string modelName) {
	std::string unixCopy = modelName;
	std::replace(modelName.begin(), modelName.end(), '/', '\\');
	return currentOSPath(("\\source\\resources\\models\\" + modelName).c_str(), ("/resources/models/" + unixCopy).c_str());
}

std::string searchMusic(std::string musicName) {
	std::string unixCopy = musicName;
	std::replace(musicName.begin(), musicName.end(), '/', '\\');
	return currentOSPath(("\\source\\resources\\music\\" + musicName).c_str(), ("/resources/music/" + unixCopy).c_str());
}