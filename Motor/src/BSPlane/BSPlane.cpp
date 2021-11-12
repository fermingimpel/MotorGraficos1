#include "BSPlane.h"
namespace Coco {

	BSPlane::BSPlane(Renderer* rend, glm::vec3 inNormal, glm::vec3 inPoint) : Entity(rend) {
		glm::vec3 aux = glm::normalize(inNormal);
		_vecNormal = aux;
		float auxD = glm::dot(_vecNormal, inPoint);
		_distance = -auxD;
	}

	BSPlane::BSPlane(Renderer* rend, glm::vec3 a, glm::vec3 b, glm::vec3 c) : Entity(rend) {
		glm::vec3 aux = glm::cross(b - a, c - a);
		aux = glm::normalize(aux);
		_vecNormal = aux;
		float auxD = glm::dot(_vecNormal, b);
		_distance = -auxD;
	}

	BSPlane::~BSPlane() {

	}

	float BSPlane::GetDistanceToPoint(glm::vec3 point) {
		return glm::dot(_vecNormal, point) + _distance;
	}

	bool BSPlane::GetSide(glm::vec3 point) {
		return GetDistanceToPoint(point) > 0;
	}

	bool BSPlane::SameSide(glm::vec3 inPt0, glm::vec3 inPt1) {

		float aux1 = GetDistanceToPoint(inPt0);
		float aux2 = GetDistanceToPoint(inPt1);
		if (aux1 > 0 && aux2 > 0)
			return true;
		else if (aux1 <= 0 && aux2 <= 0)
			return true;

		return false;
	}

	void BSPlane::Set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
		glm::vec3 aux = glm::cross(b - a, c - a);
		aux = glm::normalize(aux);
		_vecNormal = aux;
		float auxD = glm::dot(_vecNormal, b);
		_distance = -auxD;
	}

	void BSPlane::SetNormalAndPosition(glm::vec3 inNormal, glm::vec3 inPoint) {
		_vecNormal = glm::normalize(inNormal);
		float auxD = glm::dot(inNormal, inPoint);
		_distance = -auxD;
	}

	void BSPlane::Flip() {
		_vecNormal *= -1;
		_distance *= -1;
	}
}