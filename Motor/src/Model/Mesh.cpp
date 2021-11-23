#include "Mesh.h"
#include "glew.h"

#include "ASSIMP_N/include/assimp/scene.h"
#include <iostream>

namespace Coco {

	Mesh::Mesh(Renderer* rend) : Entity(rend) {
		VAO = 0;
		VBO = 0;
		IBO = 0;
		indexCount = 0;

		_node = NULL;

		_uniformModel = glGetUniformLocation(_renderer->GetShader(), "model");
		_uniformProjection = glGetUniformLocation(_renderer->GetShader(), "projection");
		_uniformView = glGetUniformLocation(_renderer->GetShader(), "view");

		_positionLocation = glGetAttribLocation(_renderer->GetShader(), "pos");
		_texLocation = glGetAttribLocation(_renderer->GetShader(), "tex");
		_normalLocation = glGetAttribLocation(_renderer->GetShader(), "norm");

		_canDrawMesh = true;


		_minCollConst = glm::vec3(999, 999, 999);
		_minColl = glm::vec3(999, 999, 999);
		_maxCollConst = glm::vec3(-999, -999, -999);
		_maxColl = glm::vec3(-999, -999, -999);

		_minCollTotalConst	= glm::vec3(999, 999, 999);
		_minCollTotal		= glm::vec3(999, 999, 999);
		_maxCollTotalConst	= glm::vec3(-999, -999, -999);
		_maxCollTotal		= glm::vec3(-999, -999, -999);
	}


	Mesh::~Mesh() {
		ClearMesh();
	}

	void Mesh::CreateMesh(float* vertices, uint* indices, uint numOfVertices, uint numOfIndices) {
		indexCount = numOfIndices;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numOfIndices, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numOfVertices, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(_positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glEnableVertexAttribArray(_positionLocation);

		glVertexAttribPointer(_texLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(_texLocation);

		glVertexAttribPointer(_normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));
		glEnableVertexAttribArray(_normalLocation);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
	void Mesh::SetCanDrawMesh(bool value) {
		_canDrawMesh = value;
	}
	bool Mesh::GetCanDrawMesh() {
		return _canDrawMesh;
	}
	void Mesh::RenderMesh() {
		if (_canDrawMesh) {
			_renderer->UpdateMVP(matrix.model, _uniformModel, _uniformView, _uniformProjection);
			_renderer->DrawMesh(indexCount, VAO, VBO, IBO, _affectedByLight);
		}
	}

	void Mesh::ClearMesh() {
		if (IBO != 0) {
			glDeleteBuffers(1, &IBO);
			IBO = 0;
		}

		if (VBO != 0) {
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}

		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}

		indexCount = 0;
	}

	void Mesh::SetPos(float x, float y, float z) {
		transform.localPosition = { x, y, z };

		if (_meshParent)
			transform.position = _meshParent->transform.position + transform.localPosition;
		else
			transform.position = transform.localPosition;

		matrix.translate = glm::translate(glm::mat4(1.0f), transform.position);

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsPos();

		UpdateMatrixData();
	}
	void Mesh::SetPos(glm::vec3 pos) {
		SetPos(pos.x, pos.y, pos.z);
	}
	void Mesh::SetRotX(float x) {
		transform.localRotation.x = x;

		if (_meshParent)
			transform.rotation.x = _meshParent->transform.rotation.x + transform.rotation.x;
		else
			transform.rotation.x = transform.localRotation.x;


		matrix.rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsRotX();

		UpdateMatrixData();
		UpdateTransformsData();
	}
	void Mesh::SetRotY(float y) {
		transform.localRotation.y = y;

		if (_meshParent)
			transform.rotation.y = _meshParent->transform.rotation.y + transform.rotation.y;
		else
			transform.rotation.y = transform.localRotation.y;

		matrix.rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsRotY();

		UpdateMatrixData();
		UpdateTransformsData();
	}
	void Mesh::SetRotZ(float z) {
		transform.localRotation.z = z;

		if (_meshParent)
			transform.rotation.z = _meshParent->transform.rotation.z + transform.rotation.z;
		else
			transform.rotation.z = transform.localRotation.z;

		matrix.rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsRotZ();

		UpdateMatrixData();
		UpdateTransformsData();
	}
	void Mesh::SetRotations(float x, float y, float z) {
		transform.localRotation = glm::vec3(x, y, z);
		if (_meshParent)
			transform.rotation = _meshParent->transform.rotation + transform.localRotation;
		else
			transform.rotation = transform.localRotation;

		matrix.rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix.rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix.rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsRotations();

		UpdateMatrixData();
		UpdateTransformsData();
	}
	void Mesh::SetRotations(glm::vec3 rotation) {
		SetRotations(rotation.x, rotation.y, rotation.z);
	}
	void Mesh::SetScale(float x, float y, float z) {
		transform.localScale = { x, y, z };

		if (_meshParent)
			transform.scale = _meshParent->transform.scale * transform.localScale;
		else
			transform.scale = transform.localScale;

		matrix.scale = glm::scale(glm::mat4(1.0f), transform.scale);

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsScale();

		UpdateMatrixData();
	}

	void Mesh::UpdateSonsPos() {

		transform.position = _meshParent->transform.position + transform.localPosition;

		matrix.translate = glm::translate(glm::mat4(1.0f), transform.position);

		_minColl = (_minCollConst * transform.scale) + transform.position;
		_maxColl = (_maxCollConst * transform.scale) + transform.position + (-_minCollConst * transform.scale);

		_minCollTotal = (_minCollTotalConst * transform.scale) + transform.position;
		_maxCollTotal = (_maxCollTotalConst * transform.scale) + transform.position;

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsPos();

		UpdateMatrixData();
	}

	void Mesh::UpdateSonsRotX() {

		transform.rotation.x = _meshParent->transform.rotation.x + transform.localRotation.x;
		matrix.rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.x), glm::vec3(0.0f, 0.0f, 1.0f));

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsRotX();

		UpdateMatrixData();
		UpdateTransformsData();

	}

	void Mesh::UpdateSonsRotY() {
		transform.rotation.y = _meshParent->transform.rotation.y + transform.localRotation.y;
		matrix.rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y), glm::vec3(0.0f, 0.0f, 1.0f));

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsRotY();

		UpdateMatrixData();
		UpdateTransformsData();
	}

	void Mesh::UpdateSonsRotZ() {
		transform.rotation.z = _meshParent->transform.rotation.z + transform.localRotation.z;
		matrix.rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsRotZ();

		UpdateMatrixData();
		UpdateTransformsData();
	}

	void Mesh::UpdateSonsRotations() {
		transform.rotation = _meshParent->transform.rotation + transform.localRotation;

		matrix.rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix.rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix.rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsRotations();

		UpdateMatrixData();
		UpdateTransformsData();
	}

	void Mesh::UpdateSonsScale() {
		transform.scale = _meshParent->transform.scale * transform.localScale;
		matrix.scale = glm::scale(glm::mat4(1.0f), transform.scale);

		_minColl = (_minCollConst * transform.scale) + transform.position;
		_maxColl = (_maxCollConst * transform.scale) + transform.position + (-_minCollConst * transform.scale);

		_minCollTotal = (_minCollTotalConst * transform.scale)+ transform.position;
		_maxCollTotal = (_maxCollTotalConst * transform.scale)+ transform.position;

		for (int i = 0; i < _meshSons.size(); i++)
			_meshSons[i]->UpdateSonsScale();

		UpdateMatrixData();
	}

	void Mesh::SetName(std::string value) {
		_name = value;
	}

	void Mesh::AddMeshSon(Mesh* mesh) {
		_meshSons.push_back(mesh);
	}

	void Mesh::SetNode(aiNode* node) {
		_node = node;
	}

	void Mesh::SetIsParent(bool value) {
		_isParent = value;
	}

	void Mesh::SetParent(Mesh* parent) {
		_meshParent = parent;
	}

	bool Mesh::GetIsParent() {
		return _isParent;
	}
	aiNode* Mesh::GetNode() {
		return _node;
	}
	Mesh* Mesh::GetParent() {
		return _meshParent;
	}
	std::string Mesh::GetName() {
		return _name;
	}
	std::vector<Mesh*> Mesh::GetMeshesSons() {
		return _meshSons;
	}

	void Mesh::SetMinColl(glm::vec3 value) {
		_minCollConst = value;
		_minColl = (_minCollConst * transform.scale) + transform.position;
	}

	void Mesh::SetMaxColl(glm::vec3 value) {
		_maxCollConst = value;
		_maxColl = (_maxCollConst * transform.scale) + transform.position + (-_minCollConst * transform.scale);
	}

	glm::vec3 Mesh::GetMinCollTotal() {
		return _minCollConst;
	}
	glm::vec3 Mesh::GetMaxCollTotal() {
		return _maxCollConst;
	}

	glm::vec3 Mesh::GetMinColl() {
		return _minColl;
	}

	glm::vec3 Mesh::GetMaxColl() {
		return _maxColl;
	}

	void Mesh::SetMinCollGeneral(glm::vec3 value) {
		_minCollTotalConst = value;
		_minCollTotal = (_minCollTotalConst * transform.scale) + transform.position;
	}
	void Mesh::SetMaxCollGeneral(glm::vec3 value) {
		_maxCollTotalConst = value;
		_maxCollTotal = (_maxCollTotalConst * transform.scale) + transform.position;
	}
	glm::vec3 Mesh::GetMinCollGeneral() {
		return _minCollTotal;
	}
	glm::vec3 Mesh::GetMaxCollGeneral() {
		return _maxCollTotal;
	}

	void Mesh::StopDrawMeshAndSons(Mesh* mesh) {
		mesh->SetCanDrawMesh(false);
		if(mesh->GetIsParent())
			for (int i = 0; i < mesh->GetMeshesSons().size();i++) 
				StopDrawMeshAndSons(mesh->GetMeshesSons()[i]);
	}

	void Mesh::SetGeneralColls(Mesh* mesh) {
		float minX = mesh->GetMinCollTotal().x, minY = mesh->GetMinCollTotal().y, minZ = mesh->GetMinCollTotal().z, maxX = mesh->GetMaxCollTotal().x, maxY = mesh->GetMaxCollTotal().y, maxZ = mesh->GetMaxCollTotal().z;
		mesh->SetMinCollGeneral(glm::vec3(minX, minY, minZ));
		mesh->SetMaxCollGeneral(glm::vec3(maxX, maxY, maxZ));

		for (int i = 0; i < mesh->GetMeshesSons().size(); i++)
			SetGeneralColls(mesh->GetMeshesSons()[i]);


		if (mesh->GetParent() != NULL) 
			mesh->TryChangeParentGeneralColls(mesh->GetParent());
		
	}

	void Mesh::TryChangeParentGeneralColls(Mesh* mesh) {
		float minX = mesh->GetMinCollTotal().x, minY = mesh->GetMinCollTotal().y, minZ = mesh->GetMinCollTotal().z, maxX = mesh->GetMaxCollTotal().x, maxY = mesh->GetMaxCollTotal().y, maxZ = mesh->GetMaxCollTotal().z;
	//	int a = 999;
	//	int b = 999;

		for (int i = 0; i < mesh->GetMeshesSons().size(); i++) {
			
			if (mesh->GetMeshesSons()[i]->GetMinCollTotal().x <= minX)
				minX = mesh->GetMeshesSons()[i]->GetMinCollTotal().x;

			if (mesh->GetMeshesSons()[i]->GetMinCollTotal().y <= minY)
				minY = mesh->GetMeshesSons()[i]->GetMinCollTotal().y;

			if (mesh->GetMeshesSons()[i]->GetMinCollTotal().z <= minZ)
				minZ = mesh->GetMeshesSons()[i]->GetMinCollTotal().z;

			if (mesh->GetMeshesSons()[i]->GetMaxCollTotal().x >= maxX)
				maxX = mesh->GetMeshesSons()[i]->GetMaxCollTotal().x;

			if (mesh->GetMeshesSons()[i]->GetMaxCollTotal().y >= maxY)
				maxY = mesh->GetMeshesSons()[i]->GetMaxCollTotal().y;

			if (mesh->GetMeshesSons()[i]->GetMaxCollTotal().z >= maxZ)
				maxZ = mesh->GetMeshesSons()[i]->GetMaxCollTotal().z;
		
		}

		mesh->SetMinCollGeneral(glm::vec3(minX, minY, minZ));
		mesh->SetMaxCollGeneral(glm::vec3(maxX, maxY, minZ));

	//	std::cout << std::endl;
	//	std::cout << "name: " << mesh->GetName() << std::endl;
	//	std::cout << "min x: " << minX << " y: " << minY << " z: " << minZ << std::endl;
	//	std::cout << "max x: " << maxX << " y: " << maxY << " z: " << maxZ << std::endl;
	//	std::cout << std::endl;
	}

}