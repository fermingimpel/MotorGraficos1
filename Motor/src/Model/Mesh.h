#ifndef MESH_H
#define MESH_H

#include "../Exports/Exports.h"
#include "../Entity/Entity.h"
#include <vector>
#include <string>

struct aiNode;

namespace Coco {
	typedef unsigned int uint;
	class GraficosEngine_API Mesh : public Entity {
		uint VAO, VBO, IBO;
		int indexCount;
		std::vector<Mesh*> _meshSons;
		Mesh* _meshParent;
		std::string _name;
		aiNode* _node;
		bool _isParent;
		bool _canDrawMesh;

		glm::vec3 _minCollConst;
		glm::vec3 _minColl;
		glm::vec3 _maxCollConst;
		glm::vec3 _maxColl;

		glm::vec3 _minCollTotal;
		glm::vec3 _maxCollTotal;
	public:
		Mesh(Renderer* rend);
		~Mesh();

		void CreateMesh(float* vertices, uint* indices, uint numOfVertices, uint numOfIndices);
		void SetCanDrawMesh(bool value);
		bool GetCanDrawMesh();
		void RenderMesh();
		void ClearMesh();
		void AddMeshSon(Mesh* mesh);
		void SetNode(aiNode* node);
		void SetName(std::string value);
		void SetIsParent(bool value);
		void SetParent(Mesh* parent);
		bool GetIsParent();
		aiNode* GetNode();
		Mesh* GetParent();
		std::string GetName();
		std::vector<Mesh*> GetMeshesSons();

		void SetPos(float x, float y, float z)			override;
		void SetPos(glm::vec3 pos)						override;
		void SetRotX(float x)							override;
		void SetRotY(float y)							override;
		void SetRotZ(float z)							override;
		void SetRotations(float x, float y, float z)	override;
		void SetRotations(glm::vec3 rotation)			override;
		void SetScale(float x, float y, float z)		override;

		void UpdateSonsPos();
		void UpdateSonsRotX();
		void UpdateSonsRotY();
		void UpdateSonsRotZ();
		void UpdateSonsRotations();
		void UpdateSonsScale();

		void SetMinColl(glm::vec3 value);
		void SetMaxColl(glm::vec3 value);
		glm::vec3 GetMinCollTotal();
		glm::vec3 GetMaxCollTotal();
		glm::vec3 GetMinColl();
		glm::vec3 GetMaxColl();

		void SetMinCollGeneral(glm::vec3 value);
		void SetMaxCollGeneral(glm::vec3 value);
		glm::vec3 GetMinCollGeneral();
		glm::vec3 GetMaxCollGeneral();

		void StopDrawMeshAndSons(Mesh* mesh);
		void SetGeneralColls(Mesh* mesh);
		void TryChangeParentGeneralColls(Mesh* mesh);
	};

}

#endif