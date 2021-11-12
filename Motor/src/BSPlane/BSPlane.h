#ifndef BSPLANE_H
#define BSPLANE_H

#include "../Entity/Entity.h"
#include "../Exports/Exports.h"

namespace Coco {

	class GraficosEngine_API BSPlane : public Entity {
		glm::vec3 _vecNormal;
		float _distance;
	public:
		BSPlane(Renderer* rend, glm::vec3 inNormal, glm::vec3 inPoint);
		BSPlane(Renderer* rend, glm::vec3 a, glm::vec3 b, glm::vec3 c);
		~BSPlane();

		glm::vec3 GetNormal() { return _vecNormal; };
		float GetDistance() { return _distance; };

		float GetDistanceToPoint(glm::vec3 point);
		bool GetSide(glm::vec3 point);
		bool SameSide(glm::vec3 inPt0, glm::vec3 inPt1);
		void Set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		void SetNormalAndPosition(glm::vec3 inNormal, glm::vec3 inPoint);
		void Flip();
	};

}

#endif