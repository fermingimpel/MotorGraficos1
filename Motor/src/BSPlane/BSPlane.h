#ifndef BSPLANE_H
#define BSPLANE_H

#include "../Exports/Exports.h"
#include "../Model/Model.h"
#include "../Camera/Camera.h"
#include <vector>
namespace Coco {

	class GraficosEngine_API BSPlane {
		std::vector<Model*> _planes;
		std::vector<Model*> _objects;
	public:
		BSPlane();
		~BSPlane();

		void BSPMagic();
		void CheckPlaneCamera(Camera* camera);
		void AddPlane(Model* plane);
		void AddModelToCheck(Model* object);
		void DrawPlanes();
	};

}

#endif