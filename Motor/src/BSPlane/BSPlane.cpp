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
		for (int i = 0; i < _objects.size(); i++)
			CheckObjectBSP(_objects[i]->GetMeshes()[0], true);
	}

	void BSPlane::CheckObjectBSP(Mesh* mesh, bool isRoot) {
		if (!isRoot) {
			bool checkPassed = true;

			for (int i = 0; i < _planes.size(); i++) {
				glm::vec3 dirA = glm::normalize(mesh->GetMinCollGeneral() - _planes[i].model->transform.position);
				float dotProdA = glm::dot(dirA, _planes[i].model->transform.forward);

				glm::vec3 dirB = glm::normalize(mesh->GetMaxCollGeneral() - _planes[i].model->transform.position);
				float dotProdB = glm::dot(dirB, _planes[i].model->transform.forward);

				if (dotProdA < 0.0f && dotProdB < 0.0f) {
					checkPassed = false;
					break;
				}
			}

			if (!checkPassed) {
				mesh->SetCanDrawMesh(false);
				mesh->StopDrawMeshAndSons(mesh);
				return;
			}


			for (int i = 0; i < _planes.size(); i++) {
				glm::vec3 dirA = glm::normalize(mesh->GetMinColl() - _planes[i].model->transform.position);
				float dotProdA = glm::dot(dirA, _planes[i].model->transform.forward);

				glm::vec3 dirB = glm::normalize(mesh->GetMaxColl() - _planes[i].model->transform.position);
				float dotProdB = glm::dot(dirB, _planes[i].model->transform.forward);
				if (dotProdA < 0.0f && dotProdB < 0.0f) {
					checkPassed = false;
					break;
				}
			}

			if (!checkPassed)
				mesh->SetCanDrawMesh(false);
			else
				mesh->SetCanDrawMesh(true);
		}

		for (int i = 0; i < mesh->GetMeshesSons().size(); i++) {
			std::cout << "mesh parent: " << mesh->GetName() << " - mesh son to check: " << mesh->GetMeshesSons()[i]->GetName() << std::endl;
			CheckObjectBSP(mesh->GetMeshesSons()[i],false);
		}
	}

	void BSPlane::CheckPlaneCamera(Camera* camera) {
		for (int i = 0; i < _planes.size(); i++) {
			glm::vec3 dirFromAtoB = glm::normalize(camera->transform.position - _planes[i].model->transform.position);
			float dotProd = glm::dot(dirFromAtoB, _planes[i].model->transform.forward);
		
			if (dotProd < 0) {
				glm::vec3 rot;
				if (_planes[i].model->transform.rotation == _planes[i].angleLookA)
					rot = _planes[i].angleLookB;
				else
					rot = _planes[i].angleLookA;

				_planes[i].model->SetRotations(rot);
			}
		}	
	}

	void BSPlane::AddModelToCheck(Model* object) {
		_objects.push_back(object);
	}

	void BSPlane::AddPlane(Model* model, glm::vec3 angleLookA, glm::vec3 angleLookB) {
		Plane plane;
		plane.model = model;
		plane.angleLookA = angleLookA;
		plane.angleLookB = angleLookB;
		_planes.push_back(plane);
	}

	void BSPlane::DrawPlanes() {
		for (int i = 0; i < _planes.size(); i++)
			if (_planes[i].model != NULL)
				_planes[i].model->DrawModel();
	}
}