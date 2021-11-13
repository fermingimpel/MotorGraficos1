#ifndef BSPLANE_H
#define BSPLANE_H

#include "../Exports/Exports.h"
#include "../Model/Model.h"

namespace Coco {

	class GraficosEngine_API BSPlane {
		Model* _model;
	public:
		BSPlane(Renderer* rend);
		~BSPlane();

		bool IsFacingObjet(Entity* object);
		Model* GetModel();
	};

}

#endif