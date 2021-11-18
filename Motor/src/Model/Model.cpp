#include "Model.h"
#include <iostream>
#include "glew.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "ModelImporter.h"


namespace Coco {

	Model::Model(Renderer* rend) : Entity(rend) {
		_material = NULL;
		_material = new Material(rend);
		_material->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		_material->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
		_material->SetSpecular(glm::vec3(0, 0, 0));
		_material->SetShininess(1);
		_usingOriginalMaterial = true;
	}
	Model::~Model() {
		if (_usingOriginalMaterial && _material != NULL) {
			delete _material;
			_material = NULL;
		}
		ClearModel();
	}

	void Model::SetAffectedByLight(bool abl) {
		_affectedByLight = abl;
		for (int i = 0; i < _meshList.size(); i++)
			_meshList[i]->SetAffectedByLight(abl);
	}

	void Model::LoadModel(std::string fileName, std::string texturesLocation) {
		ModelImporter* modelImporter = new ModelImporter(_renderer);
		modelImporter->LoadModel(fileName, texturesLocation);
		_meshList = modelImporter->GetMeshList();
		_meshesToTex = modelImporter->GetMeshToTex();
		_texturesList = modelImporter->GetTexturesList();
		delete modelImporter;
		SetColls(_meshList[0]);
	}

	void Model::LoadModel(std::string fileName, std::string texturesLocation, std::string nameTexture) {
		ModelImporter* modelImporter = new ModelImporter(_renderer);
		modelImporter->LoadModel(fileName, texturesLocation, nameTexture);
		_meshList = modelImporter->GetMeshList();
		_meshesToTex = modelImporter->GetMeshToTex();
		_texturesList = modelImporter->GetTexturesList();
		delete modelImporter;
		SetColls(_meshList[0]);
	}

	void Model::DrawModel() {
		if (!_canDraw) {
			_canDraw = true;
			return;
		}

		for (int i = 0; i < _meshList.size(); i++) 
			if (_meshList[i]->GetCanDrawMesh()) {
				//std::cout << _meshList[i]->GetName() << " can draw: " << _meshList[i]->GetCanDrawMesh() << std::endl << std::endl;
				uint materialIndex = _meshesToTex[i];
				if (materialIndex < _texturesList.size() && _texturesList[materialIndex])
					_texturesList[materialIndex]->UseTexture();

				if (_material != NULL)
					_renderer->UseMaterial(_material->GetAmbient(), _material->GetSpecular(), _material->GetDiffuse(), _material->GetShininess(),
						_material->GetUniformAmbient(), _material->GetUniformSpecular(), _material->GetUniformDiffuse(), _material->GetUniformShininess());

				_meshList[i]->RenderMesh();


				if (materialIndex < _texturesList.size() && _texturesList[materialIndex])
					_texturesList[materialIndex]->StopTexture();
			}

	}
	void Model::SetMaterial(Material* mat) {
		if (_material != NULL) {
			delete _material;
			_material = NULL;
			_usingOriginalMaterial = false;
		}
		_material = mat;
	}
	void Model::ClearModel() {

		for (int i = 0; i < _meshList.size(); i++)
			if (_meshList[i]) {
				delete _meshList[i];
				_meshList[i] = NULL;
			}

		for (int i = 0; i < _texturesList.size(); i++)
			if (_texturesList[i]) {
				delete _texturesList[i];
				_texturesList[i] = NULL;
			}

	}

	void Model::SetScale(float x, float y, float z) {
		SetMeshScale(x, y, z, 0);
	}
	void Model::SetRotX(float x) {
		SetMeshRotX(x, 0);
	}
	void Model::SetRotY(float y) {
		SetMeshRotY(y, 0);
	}
	void Model::SetRotZ(float z) {
		SetMeshRotZ(z, 0);
	}
	void Model::SetRotations(float x, float y, float z) {
		SetMeshRotations(x, y, z, 0);
	}

	void Model::SetRotations(glm::vec3 rotation) {
		SetMeshRotations(rotation.x, rotation.y, rotation.z, 0);
	}

	void Model::SetPos(float x, float y, float z) {
		SetMeshPos(x, y, z, 0);
	}

	void Model::SetPos(glm::vec3 pos) {
		SetMeshPos(pos.x, pos.y, pos.z, 0);
	}

	void Model::SetMeshPos(float x, float y, float z, int indexMesh) {
		transform.position = { x, y, z };
		matrix.translate = glm::translate(glm::mat4(1.0f), transform.position);
		_meshList[indexMesh]->SetPos(x, y, z);

		UpdateMatrixData();
	}

	void Model::SetMeshPos(glm::vec3 pos, int indexMesh) {
		SetMeshPos(pos.x, pos.y, pos.z, indexMesh);
	}

	void Model::SetMeshRotX(float x, int indexMesh) {
		transform.rotation.x = x;
		matrix.rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		_meshList[indexMesh]->SetRotX(x);

		UpdateMatrixData();
		UpdateTransformsData();
	}

	void Model::SetMeshRotY(float y, int indexMesh) {
		transform.rotation.y = y;
		matrix.rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		_meshList[indexMesh]->SetRotY(y);

		UpdateMatrixData();
		UpdateTransformsData();
	}

	void Model::SetMeshRotZ(float z, int indexMesh) {
		transform.rotation.z = z;
		matrix.rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		_meshList[indexMesh]->SetRotZ(z);

		UpdateMatrixData();
		UpdateTransformsData();
	}

	void Model::SetMeshRotations(float x, float y, float z, int indexMesh) {
		transform.rotation = glm::vec3(x, y, z);
		matrix.rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix.rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix.rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));

		_meshList[indexMesh]->SetRotations(x, y, z);

		UpdateMatrixData();
		UpdateTransformsData();
	}

	void Model::SetMeshRotations(glm::vec3 rotation, int indexMesh) {
		SetMeshRotations(rotation.x, rotation.y, rotation.z, indexMesh);
	}

	void Model::SetMeshScale(float x, float y, float z, int indexMesh) {
		transform.scale = { x, y, z };
		matrix.scale = glm::scale(glm::mat4(1.0f), transform.scale);
		_meshList[indexMesh]->SetScale(x, y, z);

		UpdateMatrixData();
		UpdateTransformsData();
	}

	std::vector<Mesh*> Model::GetMeshes() {
		return _meshList;
	}
	void Model::SetColls(Mesh* mesh) {
		//float minX = mesh->GetMinColl().x, minY = mesh->GetMinColl().y, minZ = mesh->GetMinColl().z, maxX = mesh->GetMaxColl().x, maxY = mesh->GetMaxColl().y, maxZ = mesh->GetMaxColl().z;
		//for (int i = 0; i < mesh->GetMeshesSons().size(); i++) 
		//	if(mesh->GetIsParent())
		//		SetColls(mesh->GetMeshesSons()[i]);
		//
		//
		//for (int i = 0; i < mesh->GetMeshesSons().size(); i++) {
		//	if (mesh->GetMeshesSons()[i]->GetMinColl().x < minX)
		//		minX = mesh->GetMeshesSons()[i]->GetMinColl().x;
		//	if (mesh->GetMeshesSons()[i]->GetMinColl().y < minY)
		//		minY = mesh->GetMeshesSons()[i]->GetMinColl().y;
		//	if (mesh->GetMeshesSons()[i]->GetMinColl().z < minZ)
		//		minZ = mesh->GetMeshesSons()[i]->GetMinColl().z;
		//	if (mesh->GetMeshesSons()[i]->GetMaxColl().x > maxX)
		//		maxX = mesh->GetMeshesSons()[i]->GetMaxColl().x;
		//	if (mesh->GetMeshesSons()[i]->GetMaxColl().y > maxY)
		//		maxY = mesh->GetMeshesSons()[i]->GetMaxColl().y;
		//	if (mesh->GetMeshesSons()[i]->GetMaxColl().z > maxZ)
		//		maxZ = mesh->GetMeshesSons()[i]->GetMaxColl().z;
		//}
		//
		//mesh->SetMaxCollGeneral(glm::vec3(maxX, maxY, maxZ));
		//mesh->SetMinCollGeneral(glm::vec3(minX, minY, minZ));

		//std::cout << "mesh name: " << mesh->GetName() << std::endl;
		//std::cout << "min x: " << minX << " y: " << minY << " z: " << minZ << std::endl;
		//std::cout << "max x: " << maxX << " y: " << maxY << " z: " << maxZ << std::endl;
		//std::cout << std::endl;
	}
}