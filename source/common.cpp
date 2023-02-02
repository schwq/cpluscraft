#include "common.h"
#include "error.h"

#if defined(_WIN32) || defined(__CYGWIN__)  
const char* operatingSystemType = "WIN32";
#elif defined(__linux__) || defined(__APPLE__)
const char* operatingSystemType = "UNIX";
#endif

std::string projectPath = std::filesystem::current_path().string();

std::string currentOSPath(const char* windowsRelativePath, const char* UnixRelativePath) {
	if (operatingSystemType == "WIN32") {
		return std::string(projectPath + windowsRelativePath);
	}
	else if (operatingSystemType == "UNIX") {
		return std::string(projectPath + UnixRelativePath);
	}
	else {
		errorLog("Error: Cannot find Operating System to get current project path! (common.cpp)");
		return std::string("ErrorPath!");
	}
}