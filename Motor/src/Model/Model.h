#ifndef MODEL_H
#define MODEL_H

#include "../Exports/Exports.h"

#include <vector>

#include "../Entity/Entity.h"
#include "Mesh.h"
#include "ModelTexture.h"
#include "../Material/Material.h"

namespace Coco {
	typedef unsigned int uint;

	class GraficosEngine_API Model : public Entity {
		uint textureID;
		int width, height, bitDepth;

		const char* fileLocation;

		std::vector<Mesh*> _meshList;
		std::vector<uint> _meshesToTex;
		std::vector<ModelTexture*> _texturesList;

		bool _usingOriginalMaterial;
		Material* _material;

		glm::vec3 _minCollGeneralModelConst;
		glm::vec3 _minCollGeneralModel;
		glm::vec3 _maxCollGeneralModelConst;
		glm::vec3 _maxCollGeneralModel;

	public:
		Model(Renderer* rend);
		~Model();


		void SetAffectedByLight(bool abl) override;

		void LoadModel(std::string fileName, std::string texturesLocation);
		void LoadModel(std::string fileName, std::string textureLocation, std::string nameTexture);
		void DrawModel();
		void ClearModel();

		void SetMaterial(Material* mat);

		void SetPos(float x, float y, float z)			override;
		void SetPos(glm::vec3 pos)						override;
		void SetRotX(float x)							override;
		void SetRotY(float y)							override;
		void SetRotZ(float z)							override;
		void SetRotations(float x, float y, float z)	override;
		void SetRotations(glm::vec3 rotation)			override;
		void SetScale(float x, float y, float z)		override;

		void SetMeshPos(float x, float y, float z		,int indexMesh);
		void SetMeshPos(glm::vec3 pos					,int indexMesh);
		void SetMeshRotX(float x						,int indexMesh);
		void SetMeshRotY(float y						,int indexMesh);
		void SetMeshRotZ(float z						,int indexMesh);
		void SetMeshRotations(float x, float y, float z	,int indexMesh);
		void SetMeshRotations(glm::vec3 rotation		,int indexMesh);
		void SetMeshScale(float x, float y, float z		,int indexMesh);

		std::vector<Mesh*> GetMeshes();
		void SetColls(Mesh* mesh);
	};

}

#endif