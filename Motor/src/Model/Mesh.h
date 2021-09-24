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
	public:
		Mesh(Renderer* rend);
		~Mesh();

		void CreateMesh(float* vertices, uint* indices, uint numOfVertices, uint numOfIndices);
		void RenderMesh();
		void ClearMesh();
		void AddMeshSon(Mesh* mesh);
		void SetNode(aiNode* node);
		void SetName(std::string value);
		void SetIsParent(bool value);
		void SetParent(Mesh* parent);
		bool GetIsParent();
		aiNode* GetNode();
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
	};

}

#endif