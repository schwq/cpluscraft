#include "camera.h"

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 cameraUp) {
	this->cameraPosition = cameraPosition;
	this->cameraFront = cameraFront;
	this->cameraUp = cameraUp;
	this->cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cameraPitch = 0.0f;
	this->cameraYaw = 0.0f;

}

void Camera::updateSpeed(float speed) {
	cameraSpeed = speed;
}

void Camera::update(Shader& shader) {
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

	shader.setMat4("view", view);
}

void Camera::updatePosition(CameraPos pos, float delta) {
	updateSpeed(2.5 * delta);
	switch (pos) {
	case Camera_Forward:
		cameraPosition += cameraSpeed * cameraFront;
		break;
	case Camera_Backward:
		cameraPosition -= cameraSpeed * cameraFront;
		break;
	case Camera_Right:
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		break;
	case Camera_Left:
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		break;
	}
}

void Camera::updateDirection(float xoffset, float yoffset) {
	
	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	
	cameraYaw += xoffset;
	cameraPitch += yoffset;
	
	if (cameraPitch > 89.0f) {
		cameraPitch = 89.0f;
	}

	if (cameraPitch < -89.0f) {
		cameraPitch = -89.0f;
	}

	cameraDirection.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	cameraDirection.y = sin(glm::radians(cameraPitch));
	cameraDirection.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	cameraFront = glm::normalize(cameraDirection);
}

glm::vec3 Camera::getPosition() {
	return this->cameraPosition;
}

glm::vec3 Camera::getDirection() {
	return this->cameraFront;
}

void Camera::mouseCallback(bool& firstMouse, float& lastX, float& lastY, double xpos, double ypos) {
	if (firstMouse) {
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		firstMouse = false;
	}

	float yoffset = lastY - static_cast<float>(ypos);
	float xoffset = static_cast<float>(xpos) - lastX;
	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	updateDirection(xoffset, yoffset);
}