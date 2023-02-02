#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "common.h"
#include "error.h"
#include "shader.h"

enum CameraPos {
	Camera_Forward,
	Camera_Backward,
	Camera_Right,
	Camera_Left
};

class Camera {
public:

	Camera(glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f), 
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f));

	void updatePosition(CameraPos pos, float delta);
	void updateDirection(float xoffset, float yoffset);
	void updateSpeed(float speed);
	void update(Shader& shader);
	glm::vec3 getPosition();
	glm::vec3 getDirection();

private:

	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	float cameraYaw = 0.0f;
	float cameraPitch = 0.0f;
	float cameraSpeed = 0.2f;


};

#endif