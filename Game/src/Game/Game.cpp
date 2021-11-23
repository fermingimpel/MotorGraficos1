﻿#include "Game.h"
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
		
#pragma region Model2
		_model2 = new Model(GetRenderer());
		_model2->LoadModel("res/models/bodyna.fbx", "res/textures/", "img1.jpg");
		_model2->SetScale(0.1,0.1,0.1);
		//_model2->SetRotations(180, 0, 0);
		// 1 head, 2 body, 3 hip, 4 right leg, 5 right foot, 6 left leg, 7 left foot, 8 right arm, 9 right arm, 10 left arm, 11 left hand
		_model2->SetMeshPos(0, 0.5, 0, 1); 
		
		_model2->SetMeshPos(0, -0.2, 0, 2); 
		_model2->SetMeshScale(0.5, 1.33, 0.5, 2);

		_model2->SetMeshPos(0, -0.225, 0, 3);
		_model2->SetMeshScale(1.5, 0.75, 1.5, 3);

		_model2->SetMeshPos(-0.05, -0.2, 0, 4);
		_model2->SetMeshScale(0.33, 1, 0.33, 4);

		_model2->SetMeshPos(0, -0.15, -0.05, 5);
		_model2->SetMeshScale(0.9, 0.6, 3, 5);

		_model2->SetMeshPos(0.05, -0.2, 0, 6);
		_model2->SetMeshScale(0.33, 1, 0.33, 6);

		_model2->SetMeshPos(0, -0.15, -0.05, 7);
		_model2->SetMeshScale(0.9, 0.6, 3, 7);

		_model2->SetMeshPos(0.15, 0, 0, 8); 
		_model2->SetMeshScale(3, 0.33, 0.5, 8);

		_model2->SetMeshPos(0.2, 0.0, 0, 9);
		_model2->SetMeshScale(0.33, 2, 2, 9);

		_model2->SetMeshPos(-0.15, 0, 0, 10);
		_model2->SetMeshScale(3, 0.33, 0.5, 10);

		_model2->SetMeshPos(-0.2, 0, 0, 11);
		_model2->SetMeshScale(0.33, 2, 2, 11);

		_model2->SetPos(0, 0, 2);
	
		_model2->GetMeshes()[0]->SetGeneralColls(_model2->GetMeshes()[0]);

		//for (int i = 0; i < _model2->GetMeshes().size(); i++) 			{
		//	std::cout << std::endl;
		//	std::cout << "name: " << _model2->GetMeshes()[i]->GetName()<< " coll min pos: x: " << _model2->GetMeshes()[i]->GetMinColl().x << " y: " << _model2->GetMeshes()[i]->GetMinColl().y << " z: " << _model2->GetMeshes()[i]->GetMinColl().z << std::endl;
		//	std::cout << "name: " << _model2->GetMeshes()[i]->GetName()<< " coll max pos: x: " << _model2->GetMeshes()[i]->GetMaxColl().x << " y: " << _model2->GetMeshes()[i]->GetMaxColl().y << " z: " << _model2->GetMeshes()[i]->GetMaxColl().z << std::endl;
		//	std::cout << std::endl;
		//	
		//	std::cout << std::endl;
		//	std::cout << "name: " << _model2->GetMeshes()[i]->GetName() << " coll gen min pos: x: " << _model2->GetMeshes()[i]->GetMinCollGeneral().x << " y: " << _model2->GetMeshes()[i]->GetMinCollGeneral().y << " z: " << _model2->GetMeshes()[i]->GetMinCollGeneral().z << std::endl;
		//	std::cout << "name: " << _model2->GetMeshes()[i]->GetName() << " coll gen max pos: x: " << _model2->GetMeshes()[i]->GetMaxCollGeneral().x << " y: " << _model2->GetMeshes()[i]->GetMaxCollGeneral().y << " z: " << _model2->GetMeshes()[i]->GetMaxCollGeneral().z << std::endl;
		//	std::cout << std::endl;
		//}
		
		//std::cout << std::endl;
		//std::cout << "manito coll min pos: x: " << _model2->GetMeshes()[9]->GetMinColl().x << " y: " << _model2->GetMeshes()[9]->GetMinColl().y << " z: " << _model2->GetMeshes()[9]->GetMinColl().z << std::endl;
		//std::cout << "manito coll max pos: x: " << _model2->GetMeshes()[9]->GetMaxColl().x << " y: " << _model2->GetMeshes()[9]->GetMaxColl().y << " z: " << _model2->GetMeshes()[9]->GetMaxColl().z << std::endl;
		//std::cout << std::endl;
		//
		//std::cout << std::endl;
		//std::cout << "manito coll gen min pos: x: " << _model2->GetMeshes()[9]->GetMinCollGeneral().x << " y: " << _model2->GetMeshes()[9]->GetMinCollGeneral().y << " z: " << _model2->GetMeshes()[9]->GetMinCollGeneral().z << std::endl;
		//std::cout << "manito coll gen max pos: x: " << _model2->GetMeshes()[9]->GetMaxCollGeneral().x << " y: " << _model2->GetMeshes()[9]->GetMaxCollGeneral().y << " z: " << _model2->GetMeshes()[9]->GetMaxCollGeneral().z << std::endl;
		//std::cout << std::endl;


#pragma endregion

		BSP = new BSPlane();

		_planeLeft = new Model(GetRenderer());
		_planeLeft->LoadModel("res/models/plane.fbx", "res/textures/", "theolean.jpg");
		_planeLeft->SetScale(0.1, 0.1, 0.05);
		_planeLeft->SetPos(1, 0, 2);
		_planeLeft->SetRotations(0, -90, 0);
		BSP->AddPlane(_planeLeft, glm::vec3(0,-90,0), glm::vec3(0,90,0));

		_planeDown = new Model(GetRenderer());
		_planeDown->LoadModel("res/models/plane.fbx", "res/textures/", "theolean.jpg");
		_planeDown->SetScale(0.1, 0.1, 0.05);
		_planeDown->SetPos(0, -1, 2);
		_planeDown->SetRotations(-90, 0, 0);
		BSP->AddPlane(_planeDown, glm::vec3(-90,0,0), glm::vec3(90,0,0));

		_planeBack = new Model(GetRenderer());
		_planeBack->LoadModel("res/models/plane.fbx", "res/textures/", "theolean.jpg");
		_planeBack->SetScale(0.1, 0.1, 0.05);
		_planeBack->SetPos(0, 0, 3);
		_planeBack->SetRotations(0, 180, 0);
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

	float posXCube = 0.0f;

	void Game::Update(float deltaTime) {
		GetWindow()->ClearWindow(0.15f, 0.15f, 0.15f, 1.0f);

		rotY += deltaTime * 50.0f;

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

		if (Input::GetKey(Keycode::Z))
			posXCube += deltaTime * speedPosModel;
		else if (Input::GetKey(Keycode::X))
			posXCube -= deltaTime * speedPosModel;



		_model1->SetPos(posXCube, 0, 2);

		//timerToPrint += deltaTime;
		//if (timerToPrint >= 0.1) {
		//	//system("cls");
		//
		//	//for (int i = 0; i < _model2->GetMeshes().size(); i++) {
		//	//	std::cout << std::endl;
		//	//	std::cout << "name: " << _model2->GetMeshes()[i]->GetName()<<" coll min pos: x: " << _model2->GetMeshes()[i]->GetMinColl().x << " y: " << _model2->GetMeshes()[i]->GetMinColl().y << " z: " << _model2->GetMeshes()[i]->GetMinColl().z << std::endl;
		//	//	std::cout << "name: " << _model2->GetMeshes()[i]->GetName()<<" coll max pos: x: " << _model2->GetMeshes()[i]->GetMaxColl().x << " y: " << _model2->GetMeshes()[i]->GetMaxColl().y << " z: " << _model2->GetMeshes()[i]->GetMaxColl().z << std::endl;
		//	//	std::cout << std::endl;
		//	//}
		//
		//	//_model2->GetMeshes()[0]->SetGeneralColls(_model2->GetMeshes()[0]);
		//	timerToPrint = 0;
		//	BSP->CheckPlaneCamera(_camera);
		//	BSP->BSPMagic();
		//}

		//std::cout << std::endl;
		//std::cout << "manito coll min pos: x: " << _model2->GetMeshes()[9]->GetMinColl().x << " y: " << _model2->GetMeshes()[9]->GetMinColl().y << " z: " << _model2->GetMeshes()[9]->GetMinColl().z << std::endl;
		//std::cout << "manito coll max pos: x: " << _model2->GetMeshes()[9]->GetMaxColl().x << " y: " << _model2->GetMeshes()[9]->GetMaxColl().y << " z: " << _model2->GetMeshes()[9]->GetMaxColl().z << std::endl;
		//std::cout << std::endl;
		//
		//std::cout << std::endl;
		//std::cout << "manito coll gen min pos: x: " << _model2->GetMeshes()[9]->GetMinCollGeneral().x << " y: " << _model2->GetMeshes()[9]->GetMinCollGeneral().y << " z: " << _model2->GetMeshes()[9]->GetMinCollGeneral().z << std::endl;
		//std::cout << "manito coll gen max pos: x: " << _model2->GetMeshes()[9]->GetMaxCollGeneral().x << " y: " << _model2->GetMeshes()[9]->GetMaxCollGeneral().y << " z: " << _model2->GetMeshes()[9]->GetMaxCollGeneral().z << std::endl;
		//std::cout << std::endl;
		timerToPrint += deltaTime;
		if (timerToPrint >= 0.2f) {
			timerToPrint = 0;
			system("cls");
			_model2->GetMeshes()[0]->SetGeneralColls(_model2->GetMeshes()[0]);
			BSP->CheckPlaneCamera(_camera);
			BSP->BSPMagic();
		}

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