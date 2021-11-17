#ifndef BSPLANE_H
#define BSPLANE_H

#include "../Exports/Exports.h"
#include "../Model/Model.h"
#include "../Camera/Camera.h"
#include <vector>
namespace Coco {


	class GraficosEngine_API BSPlane {
		struct Plane {
			Model* model;
			glm::vec3 angleLookA;
			glm::vec3 angleLookB;
		};
		std::vector<Plane> _planes;
		std::vector<Model*> _objects;
	public:
		BSPlane();
		~BSPlane();

		void BSPMagic();
		void CheckObjectBSP(Mesh* mesh);
		void CheckPlaneCamera(Camera* camera);
		void AddPlane(Model* model, glm::vec3 angleLookA, glm::vec3 angleLookB);
		void AddModelToCheck(Model* object);
		void DrawPlanes();
	};

}

#endif