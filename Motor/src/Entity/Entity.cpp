#include "Entity.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

namespace Coco {

	float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;

	Entity::Entity(Renderer* rend) {
		_renderer = rend;
		_affectedByLight = true;

		matrix.model = glm::mat4(1.0f);
		matrix.translate = glm::mat4(1.0f);
		matrix.rotationX = glm::mat4(1.0f);
		matrix.rotationY = glm::mat4(1.0f);
		matrix.rotationZ = glm::mat4(1.0f);
		matrix.scale = glm::mat4(1.0f);

		transform.position = { 0,0,0 };
		transform.scale = { 1,1,1 };
		transform.rotation = { 0,0,0 };

		transform.localPosition = transform.position;
		transform.localScale = transform.scale;
		transform.localRotation = transform.rotation;

		transform.rotationQuaternion = glm::quat(0, 0, 0, 1);
		
		UpdateMatrixData();
		UpdateTransformsData();
	}
	Entity::~Entity() {

	}
	void Entity::SetCanDraw(bool cd) {
		_canDraw = cd;
	}
	void Entity::SetAffectedByLight(bool abl) {
		_affectedByLight = abl;
	}
	void Entity::SetRenderer(Renderer* r) {
		_renderer = r;
	}
	Renderer* Entity::GetRenderer() {
		return _renderer;
	}
	void Entity::UpdateMatrixData() {
		matrix.model = matrix.translate * matrix.rotationX * matrix.rotationY * matrix.rotationZ * matrix.scale;
	}

	glm::quat EulerToQuat(glm::vec3 euler) {
		euler *= deg2rad;

		float cy = cos(euler.z * 0.5);
		float sy = sin(euler.z * 0.5);
		float cp = cos(euler.x * 0.5);
		float sp = sin(euler.x * 0.5);
		float cr = cos(euler.y * 0.5);
		float sr = sin(euler.y * 0.5);
		
		glm::quat q;
		q.w = cr * cp * cy + sr * sp * sy;
		q.x = cr * sp * cy + sr * cp * sy;
		q.y = sr * cp * cy - cr * sp * sy;
		q.z = cr * cp * sy - sr * sp * cy;
		return q;
	}

	glm::vec3 QuatXVec(glm::quat quat, glm::vec3 vec) {
		float x2 = quat.x * 2.0f;
		float y2 = quat.y * 2.0f;
		float z2 = quat.z * 2.0f;
		float xx2 = quat.x * x2;
		float yy2 = quat.y * y2;
		float zz2 = quat.z * z2;
		float xy2 = quat.x * y2;
		float xz2 = quat.x * z2;
		float yz2 = quat.y * z2;
		float wx2 = quat.w * x2;
		float wy2 = quat.w * y2;
		float wz2 = quat.w * z2;

		glm::vec3 res;
		res.x = (1.0f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
		res.y = (xy2 + wz2) * vec.x + (1.0f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
		res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.0f - (xx2 + yy2)) * vec.z;
		return res;
	}

	void Entity::UpdateTransformsData() {
		transform.rotationQuaternion = EulerToQuat(transform.rotation);
		transform.forward = QuatXVec(transform.rotationQuaternion, glm::vec3(0, 0, 1));
		transform.up = QuatXVec(transform.rotationQuaternion, glm::vec3(0, 1, 0));
		transform.right = QuatXVec(transform.rotationQuaternion, glm::vec3(1, 0, 0));
	}
	void Entity::SetPos(float x, float y, float z) {
		transform.position = { x, y, z };
		transform.localPosition = { x,y,z };
		matrix.translate = glm::translate(glm::mat4(1.0f), transform.position);
		UpdateMatrixData();
	}
	void Entity::SetPos(glm::vec3 pos) {
		SetPos(pos.x, pos.y, pos.z);
	}
	void Entity::SetRotX(float x) {
		transform.rotation.x = x;
		transform.localRotation.x = x;
		matrix.rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		UpdateMatrixData();
		UpdateTransformsData();
	}
	void Entity::SetRotY(float y) {
		transform.rotation.y = y;
		transform.localRotation.y = y;
		matrix.rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		UpdateMatrixData();
		UpdateTransformsData();
	}
	void Entity::SetRotZ(float z) {
		transform.rotation.z = z;
		transform.localRotation.z = z;
		matrix.rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrixData();
		UpdateTransformsData();
	}
	void Entity::SetRotations(float x, float y, float z) {
		transform.rotation = glm::vec3(x, y, z);
		transform.localRotation = glm::vec3(x, y, z);
		matrix.rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix.rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix.rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrixData();
		UpdateTransformsData();
	}
	void Entity::SetRotations(glm::vec3 rotation) {
		SetRotations(rotation.x, rotation.y, rotation.z);
	}
	void Entity::SetScale(float x, float y, float z) {
		transform.scale = { x, y, z };
		transform.localScale = { x,y,z };
		matrix.scale = glm::scale(glm::mat4(1.0f), transform.scale);
		UpdateMatrixData();
	}
}