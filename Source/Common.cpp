#include "Common.h"
#include "LogSystem.h"

#if defined(_WIN32) || defined(__CYGWIN__)  
const char* operatingSystemType = "WIN32";
#elif defined(__linux__) || defined(__APPLE__)
const char* operatingSystemType = "UNIX";
#endif

std::string projectPath = std::filesystem::current_path().string();

std::string currentOSPath(const char* windowsRelativePath, const char* UnixRelativePath) {

	if(projectPath.find("build") != std::string::npos) {
		std::replace(projectPath.begin(), projectPath.end(), 'build', 'Source');
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
	return currentOSPath(("\\Source\\Resources\\Shaders\\" + shaderName).c_str(), ("/Resources/Shaders/" + unixCopy).c_str());
}
std::string searchTexture(std::string textureName) {
	std::string unixCopy = textureName;
	std::replace(textureName.begin(), textureName.end(), '/', '\\');
	return currentOSPath(("\\Source\\Resources\\Textures\\" + textureName).c_str(), ("/Resources/Textures/" + unixCopy).c_str());
}
std::string searchModel(std::string modelName) {
	std::string unixCopy = modelName;
	std::replace(modelName.begin(), modelName.end(), '/', '\\');
	return currentOSPath(("\\Source\\Resources\\Models\\" + modelName).c_str(), ("/Resources/Models/" + unixCopy).c_str());
}
std::string searchMusic(std::string musicName) {
	std::string unixCopy = musicName;
	std::replace(musicName.begin(), musicName.end(), '/', '\\');
	return currentOSPath(("\\Source\\Resources\\Music\\" + musicName).c_str(), ("/Resources/Music/" + unixCopy).c_str());
}

