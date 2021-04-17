#include "Camera.h"
#include <iostream>
namespace Graficos1 {
	
	Camera::Camera(Renderer* r) : Entity(r){}
	Camera::~Camera() {	}
	void Camera::InitCamera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) {
		SetPos(pos.x, pos.y, pos.z);
		_worldUp = up;
		_yaw = yaw;
		_pitch = pitch;
		_front = glm::vec3(0.0f, 0.0f, -1.0f);
		UpdateCamera();
	}
	glm::mat4 Camera::CalculateViewMatrix() {
		return glm::lookAt(positionVec, positionVec + _front, _up);
	}
	void Camera::UpdateCamera() {
		_front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_front.y = sin(glm::radians(_pitch));
		_front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_front = glm::normalize(_front);

		_right = glm::normalize(glm::cross(_front, _worldUp));
		_up = glm::normalize(glm::cross(_right, _front));
	}
	void Camera::UpdateEyePosition() {
		_renderer->SetEyePosition(positionVec);
	}
	void Camera::SetPitch(float p) {
		_pitch = p;
		UpdateCamera();
	}
	void Camera::SetYaw(float y) {
		_yaw = y;
		UpdateCamera();
	}
	float Camera::GetPitch() {
		return _pitch;
	}
	float Camera::GetYaw() {
		return _yaw;
	}
}
