#ifndef BSPLANE_H
#define BSPLANE_H

#include "../Exports/Exports.h"
#include "../Model/Model.h"
#include <vector>
namespace Coco {

	class GraficosEngine_API BSPlane {
		std::vector<Model*> _planes;
	public:
		BSPlane();
		~BSPlane();

		void BSPMagic(Model* object);
		void AddPlane(Model* plane);
		void DrawPlanes();
	};

}

#endif