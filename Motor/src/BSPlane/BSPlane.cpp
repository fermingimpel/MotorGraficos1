#include "BSPlane.h"
#include <iostream>

namespace Coco {

	BSPlane::BSPlane(Renderer* rend) {
		_model = new Model(rend);
	}

	BSPlane::~BSPlane() {
		if (_model != NULL) {
			delete _model;
			_model = NULL;
		}
	}

	bool BSPlane::IsFacingObjet(Entity* object) {
		glm::vec3 dirFromAtoB = glm::normalize(object->transform.position - _model->transform.position);
		float dotProd = glm::dot(dirFromAtoB, _model->transform.forward);

		return (dotProd >= 0.0f);
	}

	Model* BSPlane::GetModel() {
		return _model;
	}

}