#ifndef ENTITY_H
#define ENTITY_H

#include "../src/Exports/Exports.h"
#include "../src/Renderer/Renderer.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Coco {

	class GraficosEngine_API Entity {
	private:
		struct Transform {
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
			glm::quat rotationQuaternion;

			glm::vec3 localPosition;
			glm::vec3 localRotation;
			glm::vec3 localScale;
			glm::quat localRotationQuaternion;

			glm::vec3 forward;
			glm::vec3 up;
			glm::vec3 right;
		};
		struct Matrix {
			glm::mat4 model;
			glm::mat4 translate;
			glm::mat4 rotationX;
			glm::mat4 rotationY;
			glm::mat4 rotationZ;
			glm::mat4 scale;
		};
	protected:
		glm::vec3 _worldUp;
		Renderer* _renderer;
		void UpdateMatrixData();
		void UpdateTransformsData();

		uint _uniformModel;
		uint _uniformView;
		uint _uniformProjection;
		uint _positionLocation;
		uint _texLocation;
		uint _normalLocation;

		bool _canDraw;
		bool _affectedByLight;
	public:
		Entity(Renderer* rend);
		~Entity();

		Transform transform;
		Matrix matrix;
		
		void SetCanDraw(bool cd);
		virtual void SetAffectedByLight(bool abl);
		void SetRenderer(Renderer* r);
		Renderer* GetRenderer();
		virtual void SetPos(float x, float y, float z);
		virtual void SetPos(glm::vec3 pos);
		virtual void SetRotX(float x);
		virtual void SetRotY(float y);
		virtual void SetRotZ(float z);
		virtual void SetRotations(float x, float y, float z);
		virtual void SetRotations(glm::vec3 rotation);
		virtual void SetScale(float x, float y, float z);
	};

}

#endif;