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
		if (_plane != NULL) {
			delete _plane;
			_plane = NULL;
		}
	}

	void Game::Start() {
		StartEngine(1366,768, "Coco");
		srand(time(NULL));

		_camera = new Camera(GetRenderer());

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

		//_model1 = new Model(GetRenderer());
		//_model1->LoadModel("res/models/body.fbx", "res/textures/", "img1.jpg");
		//_model1->SetPos(0, 0, 2);
		//_model1->SetScale(0.1, 0.1, 0.1);

		_model2 = new Model(GetRenderer());
		_model2->LoadModel("res/models/cube.fbx", "res/textures/", "img1.jpg");
		_model2->SetScale(0.1, 0.1, 0.1);
		_model2->SetPos(0, 0, 2);

		_plane = new BSPlane(GetRenderer());
		_plane->GetModel()->LoadModel("res/models/plane.fbx", "res/textures/", "theolean.jpg");
		_plane->GetModel()->SetScale(0.1, 0.1, 0.1);
		_plane->GetModel()->SetPos(0, 0, 1.5);
		_plane->GetModel()->SetRotations(0,90,0);
		std::cout << "plane forward: x: " << _plane->GetModel()->transform.forward.x << " y: " << _plane->GetModel()->transform.forward.y << " z: " << _plane->GetModel()->transform.forward.z << std::endl;

		//for (int i = 0; i < _plane->GetModel()->GetMeshes().size(); i++) {
		//	std::cout << "name: " << _plane->GetModel()->GetMeshes()[i]->GetName() << std::endl;
		//}

		//_camera->SetEntity(_model1);
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
	float posXFootModel = 0.0f;

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

		if (Input::GetKeyDown(Keycode::ALPHA0)) {
			_camera->SetPos(0.0f, 0.0f, 0.0f);
			_camera->SetRotations(0, 0, 0);
		}

		if (Input::GetKey(Keycode::J))
			posXModel += deltaTime;
		else if (Input::GetKey(Keycode::L))
			posXModel -= deltaTime;



		_camera->LookAt(_camera->transform.position + _camera->transform.forward);

		_camera->UseCamera();
		GetRenderer()->SetView(_camera->GetViewMatrix());
		GetLightManager()->UseLights();

		//_model1->DrawModel();

		_model2->DrawModel();
		_plane->GetModel()->DrawModel();

		GetWindow()->SwapBuffers();
	}
	void Game::End() {
		EndEngine();
	}
}