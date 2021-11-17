#include "Game.h"
#include <time.h>
#include <iostream>
#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Coco {

	Game::Game() :GameBase() {}
	Game::~Game() {
		if (_shape != NULL) {
			delete _shape;
			_shape = NULL;
		}
		if (_shape2 != NULL) {
			delete _shape2;
			_shape2 = NULL;
		}
		if (_shape3 != NULL) {
			delete _shape3;
			_shape3 = NULL;
		}
		if (_camera != NULL) {
			delete _camera;
			_camera = NULL;
		}
		if (_goldMaterial != NULL) {
			delete _goldMaterial;
			_goldMaterial = NULL;
		}
		if (_obsidianMaterial != NULL) {
			delete _obsidianMaterial;
			_obsidianMaterial = NULL;
		}
		if (_model1 != NULL) {
			delete _model1;
			_model1 = NULL;
		}
		if (_model2 != NULL) {
			delete _model2;
			_model2 = NULL;
		}
		if (BSP != NULL) {
			delete BSP;
			BSP = NULL;
		}
		if (_planeLeft != NULL) {
			delete _planeLeft;
			_planeLeft = NULL;
		}
		if (_planeBack != NULL) {
			delete _planeBack;
			_planeBack = NULL;
		}
		if (_planeDown != NULL) {
			delete _planeDown;
			_planeDown = NULL;
		}
	}

	void Game::Start() {
		StartEngine(1366, 768, "Coco");
		srand(time(NULL));

		_camera = new Camera(GetRenderer());
		_camera->SetPos(0.99f, 0, 0);

		_goldMaterial = new Material(GetRenderer());
		_goldMaterial->SetAmbient(glm::vec3(0.24725f, 0.1995f, 0.0745f));
		_goldMaterial->SetDiffuse(glm::vec3(0.75164f, 0.60648f, 0.22648f));
		_goldMaterial->SetSpecular(glm::vec3(0.628281f, 0.555802f, 0.366065f));
		_goldMaterial->SetShininess(0.4f);

		_obsidianMaterial = new Material(GetRenderer());
		_obsidianMaterial->SetAmbient(glm::vec3(0.05375f, 0.05f, 0.06625f));
		_obsidianMaterial->SetDiffuse(glm::vec3(0.18275f, 0.17f, 0.22525f));
		_obsidianMaterial->SetSpecular(glm::vec3(0.332741f, 0.328634f, 0.346435f));
		_obsidianMaterial->SetShininess(0.3f);

		_model1 = new Model(GetRenderer());
		_model1->LoadModel("res/models/cube.fbx", "res/textures/", "pato.jpg");
		_model1->SetPos(0, 0, 2);
		_model1->SetScale(0.1, 0.1, 0.1);
		//for (int i = 0; i < _model1->GetMeshes().size(); i++) {
		//	std::cout << "name:" << _model1->GetMeshes()[i]->GetName() << std::endl;
		//	std::cout << "min coll: x: " << _model1->GetMeshes()[i]->GetMinColl().x << " y: " << _model1->GetMeshes()[i]->GetMinColl().y << " z: " << _model1->GetMeshes()[i]->GetMinColl().z << std::endl;
		//	std::cout << "max coll: x: " << _model1->GetMeshes()[i]->GetMaxColl().x << " y: " << _model1->GetMeshes()[i]->GetMaxColl().y << " z: " << _model1->GetMeshes()[i]->GetMaxColl().z << std::endl;
		//	std::cout << std::endl;
		//}
		
#pragma region Model2
		_model2 = new Model(GetRenderer());
		_model2->LoadModel("res/models/body.fbx", "res/textures/", "img1.jpg");
		_model2->SetScale(0.1, 0.1, 0.1);
		_model2->SetRotations(-90, 0, 0);

		_model2->SetMeshPos(0, 0.33, 0, 1);
		_model2->SetMeshPos(0, -0.2, 0, 2);
		_model2->SetMeshPos(0.15, 0, 0, 3);
		_model2->SetMeshPos(0.15, 0, 0, 4);
		_model2->SetMeshPos(-0.15, 0, 0, 5);
		_model2->SetMeshPos(-0.15, 0, 0, 6);
		_model2->SetMeshPos(0, -0.175, 0, 7);
		_model2->SetMeshPos(-0.05, -0.175, 0, 8);
		_model2->SetMeshPos(0, -0.1, -0.05, 9);
		_model2->SetMeshPos(0.05, -0.175, 0, 10);
		_model2->SetMeshPos(0, -0.1, -0.05, 11);

		for (int i = 0; i < _model2->GetMeshes().size(); i++) {
			std::cout << "name: " << _model2->GetMeshes()[i]->GetName() << std::endl;
			std::cout << "min coll: x: " << _model2->GetMeshes()[i]->GetMinColl().x << " y: " << _model2->GetMeshes()[i]->GetMinColl().y << " z: " << _model2->GetMeshes()[i]->GetMinColl().z << std::endl;
			std::cout << "max coll: x: " << _model2->GetMeshes()[i]->GetMaxColl().x << " y: " << _model2->GetMeshes()[i]->GetMaxColl().y << " z: " << _model2->GetMeshes()[i]->GetMaxColl().z << std::endl;
			std::cout << std::endl;
		}

		_model2->SetPos(0, 0, 2);
#pragma endregion

		BSP = new BSPlane();

		_planeLeft = new Model(GetRenderer());
		_planeLeft->LoadModel("res/models/plane.fbx", "res/textures/", "theolean.jpg");
		_planeLeft->SetScale(0.1, 0.1, 0.1);
		_planeLeft->SetPos(1, 0, 2);
		_planeLeft->SetRotations(0, -90, 0);
		BSP->AddPlane(_planeLeft, glm::vec3(0,-90,0), glm::vec3(0,90,0));

		_planeDown = new Model(GetRenderer());
		_planeDown->LoadModel("res/models/plane.fbx", "res/textures/", "theolean.jpg");
		_planeDown->SetScale(0.1, 0.1, 0.1);
		_planeDown->SetPos(0, -1, 2);
		_planeDown->SetRotations(-90, 0, 0);
		BSP->AddPlane(_planeDown, glm::vec3(-90,0,0), glm::vec3(90,0,0));

		_planeBack = new Model(GetRenderer());
		_planeBack->LoadModel("res/models/plane.fbx", "res/textures/", "theolean.jpg");
		_planeBack->SetScale(0.1, 0.1, 0.1);
		_planeBack->SetPos(0, 0, 3);
		_planeBack->SetRotations(0, 0, 0);
		BSP->AddPlane(_planeBack, glm::vec3(0,0,0), glm::vec3(0,180,0));

		BSP->AddModelToCheck(_model1);
		BSP->AddModelToCheck(_model2);
	}
	void Game::Play() {
		UpdateEngine();
	}

	float speed = 5.0f;
	float speedRotationCamera = 100.0f;
	bool usingLight = true;

	float timerLight = 0.0f;
	const float maxTimerLight = 1.5f;

	float rotY = 0;

	bool inFirstPersonMode = false;

	float posXModel = 0.0f;
	float posYModel = 0.0f;
	float posZModel = 2.0f;

	float timerToPrint = 0.0f;

	void Game::Update(float deltaTime) {
		GetWindow()->ClearWindow(0.15f, 0.15f, 0.15f, 1.0f);

		rotY += deltaTime * 50.0f;
		//_model1->SetRotations(0, rotY, 0);

		if (Input::GetKey(Keycode::W))
			_camera->SetPos(_camera->transform.position + (glm::vec3(0, 1, 0) * speed * deltaTime));
		else if (Input::GetKey(Keycode::S))
			_camera->SetPos(_camera->transform.position + (glm::vec3(0, -1, 0) * speed * deltaTime));

		if (Input::GetKey(Keycode::A))
			_camera->SetPos(_camera->transform.position + (glm::vec3(1, 0, 0) * speed * deltaTime));
		else if (Input::GetKey(Keycode::D))
			_camera->SetPos(_camera->transform.position + (glm::vec3(-1, 0, 0) * speed * deltaTime));

		if (Input::GetMouseButtonDown(MouseButtons::LEFT_MOUSE_BUTTON))
			_camera->SetPos(_camera->transform.position + (glm::vec3(0, 0, 1) * speed * deltaTime));
		else if (Input::GetMouseButtonDown(MouseButtons::RIGHT_MOUSE_BUTTON))
			_camera->SetPos(_camera->transform.position + (glm::vec3(0, 0, -1) * speed * deltaTime));

		if (Input::GetKey(Keycode::Q))
			_camera->SetRotY(_camera->transform.rotation.y + (speedRotationCamera * deltaTime));
		else if (Input::GetKey(Keycode::E))
			_camera->SetRotY(_camera->transform.rotation.y - (speedRotationCamera * deltaTime));

		if (Input::GetKeyDown(Keycode::ALPHA1)) {
			_camera->SetPos(0.99f, 0.0f, 1.5f);
			_camera->SetRotations(0, 0, 0);
		}
		if (Input::GetKeyDown(Keycode::ALPHA2)) {
			_camera->SetPos(1.01f, 0.0f, 1.5f);
			_camera->SetRotations(0, 0, 0);
		}

		if (Input::GetKeyDown(Keycode::ALPHA0)) {
			_camera->SetPos(0.0f, 0.0f, 0.0f);
			_camera->SetRotations(0, 0, 0);
		}

		float speedPosModel = 0.5f;

		if (Input::GetKey(Keycode::J))
			posXModel += deltaTime * speedPosModel;
		else if (Input::GetKey(Keycode::L))
			posXModel -= deltaTime * speedPosModel;
		if (Input::GetKey(Keycode::I))
			posYModel += deltaTime * speedPosModel;
		else if (Input::GetKey(Keycode::K))
			posYModel -= deltaTime * speedPosModel;
		if (Input::GetKey(Keycode::U))
			posZModel += deltaTime * speedPosModel;
		else if (Input::GetKey(Keycode::O))
			posZModel -= deltaTime * speedPosModel;

		_model2->SetPos(posXModel, posYModel, posZModel);

		//for (int i = 0; i < _model2->GetMeshes().size(); i++) {
		//	std::cout << "name: " << _model2->GetMeshes()[i]->GetName() << std::endl;
		//	std::cout << "min coll: x: " << _model2->GetMeshes()[i]->GetMinColl().x << " y: " << _model2->GetMeshes()[i]->GetMinColl().y << " z: " << _model2->GetMeshes()[i]->GetMinColl().z << std::endl;
		//	std::cout << "max coll: x: " << _model2->GetMeshes()[i]->GetMaxColl().x << " y: " << _model2->GetMeshes()[i]->GetMaxColl().y << " z: " << _model2->GetMeshes()[i]->GetMaxColl().z << std::endl;
		//	std::cout << std::endl;
		//}

		//std::cout << std::endl;
		//std::cout << std::endl;
		//std::cout << std::endl;

		//timerToPrint += deltaTime;
		//if (timerToPrint >= 1.0f) {
		//	timerToPrint = 0;
		//	system("cls");
		//	for (int i = 0; i < _model2->GetMeshes().size(); i++) {
		//		std::cout << "name: " << _model2->GetMeshes()[i]->GetName() << std::endl;
		//		std::cout << "min coll: x: " << _model2->GetMeshes()[i]->GetMinColl().x << " y: " << _model2->GetMeshes()[i]->GetMinColl().y << " z: " << _model2->GetMeshes()[i]->GetMinColl().z << std::endl;
		//		std::cout << "max coll: x: " << _model2->GetMeshes()[i]->GetMaxColl().x << " y: " << _model2->GetMeshes()[i]->GetMaxColl().y << " z: " << _model2->GetMeshes()[i]->GetMaxColl().z << std::endl;
		//		std::cout << std::endl;
		//	}
		//}

		//timerToPrint += deltaTime;
		//
		//if (timerToPrint >= 1.0f) {
		//	timerToPrint = 0.0f;
		//	system("cls");
		//	for (int i = 0; i < _model2->GetMeshes().size(); i++) {
		//		std::cout << "name: " << _model2->GetMeshes()[i]->GetName() << std::endl;
		//		std::cout << "can draw: " << _model2->GetMeshes()[i]->GetCanDrawMesh() << std::endl;
		//		std::cout << std::endl;
		//	}
		//}

		BSP->BSPMagic();
		BSP->CheckPlaneCamera(_camera);

		_camera->LookAt(_camera->transform.position + _camera->transform.forward);

		_camera->UseCamera();
		GetRenderer()->SetView(_camera->GetViewMatrix());
		GetLightManager()->UseLights();

		_model1->DrawModel();
		_model2->DrawModel();
		BSP->DrawPlanes();

		GetWindow()->SwapBuffers();
	}
	void Game::End() {
		EndEngine();
	}
}