#include "BSPlane.h"
#include <iostream>
#include <algorithm>
#include <iterator>

namespace Coco {

	BSPlane::BSPlane() {}

	BSPlane::~BSPlane() {
		_objects.clear();
		_planes.clear();
	}

	void BSPlane::BSPMagic() {
		for (int x = 0; x < _objects.size(); x++) {
			if (_objects[x] != NULL) {
				std::vector<Mesh*> aux = _objects[x]->GetMeshes();
				for (int i = 0; i < _planes.size(); i++)
					for (int j = 0; j < aux.size(); j++) {
						glm::vec3 dirFromAtoB = glm::normalize(aux[j]->transform.position - _planes[i]->transform.position);
						float dotProd = glm::dot(dirFromAtoB, _planes[i]->transform.forward);
						if (dotProd >= 0.0f) {
							aux[j]->SetCanDrawMesh(true);
						}
						else {
							aux[j]->SetCanDrawMesh(false);
							aux.erase(aux.begin() + j);
							j--;

						}
					}
			}
		}
	}

	void BSPlane::CheckPlaneCamera(Camera* camera) {
		for (int i = 0; i < _planes.size(); i++) {
			glm::vec3 dirFromAtoB = glm::normalize(camera->transform.position - _planes[i]->transform.position);
			float dotProd = glm::dot(dirFromAtoB, _planes[i]->transform.forward);

			if (dotProd < 0.0f) {
				glm::vec3 rot = _planes[i]->transform.rotation;
				_planes[i]->SetRotations(rot.x * -1, rot.y * -1, rot.z * -1);
			}
		}	
	}

	void BSPlane::AddModelToCheck(Model* object) {
		_objects.push_back(object);
	}

	void BSPlane::AddPlane(Model* plane) {
		_planes.push_back(plane);
	}

	void BSPlane::DrawPlanes() {
		for (int i = 0; i < _planes.size(); i++)
			if (_planes[i] != NULL)
				_planes[i]->DrawModel();
	}
}