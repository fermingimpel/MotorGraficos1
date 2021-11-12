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
		if (_model3 != NULL) {
			delete _model3;
			_model3 = NULL;
		}
		if (_model4 != NULL) {
			delete _model4;
			_model4 = NULL;
		}
		if (_model5 != NULL) {
			delete _model5;
			_model5 = NULL;
		}
		if (_model6 != NULL) {
			delete _model6;
			_model6 = NULL;
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

		_model1 = new Model(GetRenderer());
		_model1->LoadModel("res/models/body.fbx", "null");
		_model1->SetPos(0, 0, 2);
		_model1->SetMeshPos(-0.66f, 0, 0, 8);
		_model1->SetMeshPos(0.2, 0, 0, 9);
		//_model1->SetPos(0, -0.5, 5);
		//_model1->SetRotY(180);
		
		_model1->SetRotY(30);


		//_model1->SetRotZ(-180);
		//
		//_model1->SetMeshPos(1, -0.5, 5, 5);
		//_model1->SetMeshPos(-1, -0.5, 5, 6);

		for (int i = 0; i < _model1->GetMeshes().size(); i++) {
			std::cout << "name: " << _model1->GetMeshes()[i]->GetName().c_str() <<	" world rot x: " << _model1->GetMeshes()[i]->transform.rotationQuaternion.x << " y: " << _model1->GetMeshes()[i]->transform.rotationQuaternion.y << " z: " << _model1->GetMeshes()[i]->transform.rotationQuaternion.z <<" w: " << _model1->GetMeshes()[i]->transform.rotationQuaternion.w << std::endl;
			//std::cout << "name: " <<_model1->GetMeshes()[i]->GetName().c_str() <<	" local rot x: " << _model1->GetMeshes()[i]->transform.localRotation.x << " y: " << _model1->GetMeshes()[i]->transform.localRotation.y << " z: " << _model1->GetMeshes()[i]->transform.localRotation.z <<	" w: " << _model1->GetMeshes()[i]->transform.rotation.w << std::endl;
			std::cout << std::endl;
		}

		_camera->SetEntity(_model1);


		//_model1 = new Model(GetRenderer());
		//_model1->LoadModel("res/models/Banfield Ghost/ghost.obj", "res/models/Banfield Ghost/", "Ghost_lambert1_BaseColor.png");
		//_model1->SetPos(-3, 0, 5);
		//_model1->SetScale(0.5f, 0.5f, 0.5f);
		//_model1->SetRotY(180);
		//_model1->SetMaterial(_goldMaterial);
		//
		//_model2 = new Model(GetRenderer());
		//_model2->LoadModel("res/models/BokitaGhost/ghost.obj", "res/models/BokitaGhost/", "Ghost_lambert1_BaseColor.png");
		//_model2->SetPos(-1, 0, 5);
		//_model2->SetScale(0.5f, 0.5f, 0.5f);
		//_model2->SetRotY(180);
		//_model2->SetMaterial(_obsidianMaterial);
		//
		//_model3 = new Model(GetRenderer());
		//_model3->LoadModel("res/models/ChacaritaGhost/ghost.obj", "res/models/ChacaritaGhost/", "Ghost_lambert1_BaseColor.png");
		//_model3->SetPos(1, 0, 5);
		//_model3->SetScale(0.5f, 0.5f, 0.5f);
		//_model3->SetRotY(180);
		//
		//_model4 = new Model(GetRenderer());
		//_model4->LoadModel("res/models/Olimpo ghost/ghost.obj", "res/models/Olimpo ghost/", "Ghost_lambert1_BaseColor.png");
		//_model4->SetPos(3, 0, 5);
		//_model4->SetScale(0.5f, 0.5f, 0.5f);
		//_model4->SetRotY(180);
		//
		//_model5 = new Model(GetRenderer());
		//_model5->LoadModel("res/models/helicopter/uh60.obj", "res/models/helicopter/");
		//_model5->SetPos(0, 0, 0);
		//_model5->SetScale(1, 1, 1);
		//
		//_model6 = new Model(GetRenderer());
		//_model6->LoadModel("res/models/chicken/Chicken1.fbx", "res/models/chicken/");
		//_model6->SetPos(0, 2, 7);
		//_model6->SetRotY(180);
		//
		////_model6->SetScale(0.25f, 0.25f, 0.25f);
		//
		//_camera->SetEntity(_model4);

		//_camera->LookAt(_model4->transform.position);
		//_model4->SetPos(_model4->transform.position, (_model4->transform.forward * 3.0f));
		//
		//_shape = new Shape(GetRenderer());
		//_shape->InitShape(TypeShape::Cube, TypeShader::Colour);
		//_shape->SetScale(0.33f, 0.33f, 0.33f);
		//_shape->SetPos(-1.0f, -1, 5);
		////_shape->LoadTexture("res/textures/", "img1.jpg");
		//_shape->SetMaterial(_goldMaterial);
		//_shape->SetAffectedByLight(false);
		//
		////
		//_shape2 = new Shape(GetRenderer());
		//_shape2->InitShape(TypeShape::Cube, TypeShader::Colour);
		//_shape2->SetScale(0.33f, 0.33f, 0.33f);
		//_shape2->SetPos(0.0f, -1, 5);
		////_shape2->SetMaterial(_obsidianMaterial);
		//_shape2->SetAffectedByLight(false);
		//
		//_shape3 = new Shape(GetRenderer());
		//_shape3->InitShape(TypeShape::Cube, TypeShader::Colour);
		//_shape3->SetScale(0.33f, 0.33f, 0.33f);
		//_shape3->SetPos(1.0f, -1, 5);
		//_shape3->SetMaterial(_goldMaterial);
		//
		////
		////
		////
		//
		//GetLightManager()->AddLight(TypeOfLight::Spot);
		//SpotLight* _lightAux = GetLightManager()->GetSpotLightByIndex(0);
		//if (_lightAux != NULL) {
		//	_lightAux->SetPos(0, 0, -2);
		//	_lightAux->SetColour(glm::vec3(1.0f, 1.0f, 1.0f));
		//	_lightAux->SetAmbient(glm::vec3(0.33f, 0.33f, 0.33f));
		//	_lightAux->SetDiffuse(glm::vec3(0.5, 0.5, 0.5));
		//	_lightAux->SetSpecular(glm::vec3(1, 1, 1));
		//	_lightAux->SetConstantLinearQuadratic(1.0f, 0.007f, 0.0002f);
		//	_lightAux->SetCutOff(33.0f);
		//	_lightAux->SetDirection(glm::vec3(0, 0, 1));
		//}

		//	//
		//	GetLightManager()->AddLight(TypeOfLight::Point);
		//	PointLight* _lightAux2 = GetLightManager()->GetPointLightByIndex(0);
		//	if (_lightAux2 != NULL) {
		//		_lightAux2->SetPos(0,0,3);
		//		_lightAux2->SetColour(glm::vec3(1.0f,1.0f,1.0f));
		//		_lightAux2->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
		//		_lightAux2->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
		//		_lightAux2->SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
		//		_lightAux2->SetConstantLinearQuadratic(1.0f, 0.045f, 0.0075f);
		//	}
		//
		//// 
		//	GetLightManager()->AddLight(TypeOfLight::Directional);
		//	GetLightManager()->AddLight(TypeOfLight::Directional);
		//	//
		//	DirectionalLight* dirAux = GetLightManager()->GetDirectionalLightByIndex(0);
		//	if (dirAux != NULL) {
		//		dirAux->SetColour(glm::vec3(1, 1, 1));
		//		dirAux->SetDirection(glm::vec3(0, 0, 1));
		//		dirAux->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		//		dirAux->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
		//		dirAux->SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
		//	}
		//	
		//	dirAux = GetLightManager()->GetDirectionalLightByIndex(1);
		//	
		//	if (dirAux != NULL) {
		//		dirAux->SetColour(glm::vec3(1.0f, 0, 1.0f));
		//		dirAux->SetDirection(glm::vec3(0, -1, 0));
		//	}

		//std::vector<Mesh*> meshes = _model1->GetMeshes();
		//for (int i = 0; i < meshes.size(); i++) {
		//	std::cout << "mesh name:" << meshes[i]->GetName() << std::endl;
		//	
		//	std::vector<Mesh*> meshesSon = meshes[i]->GetMeshesSons();
		//	for (int j = 0; j < meshesSon.size(); j++) 
		//		std::cout << "Mesh son[" << j << "] name: " << meshesSon[j]->GetName() << std::endl;
		//	
		//	std::cout << std::endl;
		//}

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
		
		//_model2->SetRotY(rotY);
		//_model3->SetRotY(rotY);
		//_model4->SetRotations(rotY, rotY, rotY);
		//
		//if (Input::GetKeyDown(Keycode::ENTER)) {
		//	system("cls");
		//
		//	if (inFirstPersonMode)
		//		_camera->SetEntity(_model5);
		//	else
		//		_camera->SetEntity(_model4);
		//
		//	inFirstPersonMode = !inFirstPersonMode;
		//}
		//
		//if (inFirstPersonMode) {
		//	if (Input::GetKeyDown(Keycode::ALPHA1))
		//		_camera->SetEntity(_model1);
		//	if (Input::GetKeyDown(Keycode::ALPHA2))
		//		_camera->SetEntity(_model2);
		//	if (Input::GetKeyDown(Keycode::ALPHA3))
		//		_camera->SetEntity(_model3);
		//	if (Input::GetKeyDown(Keycode::ALPHA4))
		//		_camera->SetEntity(_model4);
		//
		//	_camera->FirstPersonLook(glm::vec3(0, 1.66f, 0), false);
		//}
		//else {
		//	if (Input::GetKey(Keycode::W))
		//		_model5->SetPos(_model5->transform.position + (_model5->transform.forward * speed * deltaTime));
		//	else if (Input::GetKey(Keycode::S))
		//		_model5->SetPos(_model5->transform.position - (_model5->transform.forward * speed * deltaTime));
		//
		//	if (Input::GetKey(Keycode::A))
		//		_model5->SetPos(_model5->transform.position + (_model5->transform.right * speed * deltaTime));
		//	else if (Input::GetKey(Keycode::D))
		//		_model5->SetPos(_model5->transform.position - (_model5->transform.right * speed * deltaTime));
		//
		//	if (Input::GetMouseButtonDown(MouseButtons::LEFT_MOUSE_BUTTON))
		//		_model5->SetPos(_model5->transform.position + (_model5->transform.up * speed * deltaTime));
		//	else if (Input::GetMouseButtonDown(MouseButtons::RIGHT_MOUSE_BUTTON))
		//		_model5->SetPos(_model5->transform.position - (_model5->transform.up * speed * deltaTime));
		//
		//	if (Input::GetKey(Keycode::Q))
		//		_model5->SetRotY(_model5->transform.rotation.y + (speedRotationCamera * deltaTime));
		//	else if (Input::GetKey(Keycode::E))
		//		_model5->SetRotY(_model5->transform.rotation.y - (speedRotationCamera * deltaTime));
		//
		//	if (Input::GetKeyDown(Keycode::ALPHA0)) {
		//		_model5->SetPos(0.0f, 0.0f, 0.0f);
		//		_model5->SetRotations(0, 0, 0);
		//	}
		//
		//	_camera->ThirdPersonLook(glm::vec3(0, 5, 0), 15, true);
		//}

		//else {
		//	if (Input::GetKey(Keycode::W))
		//		_camera->SetPos(_camera->transform.position + (glm::vec3(0, 1, 0) * speed * deltaTime));
		//	else if (Input::GetKey(Keycode::S))
		//		_camera->SetPos(_camera->transform.position + (glm::vec3(0, -1, 0) * speed * deltaTime));
		//
		//	if (Input::GetKey(Keycode::A))
		//		_camera->SetPos(_camera->transform.position + (glm::vec3(1, 0, 0) * speed * deltaTime));
		//	else if (Input::GetKey(Keycode::D))
		//		_camera->SetPos(_camera->transform.position + (glm::vec3(-1, 0, 0) * speed * deltaTime));
		//
		//	if (Input::GetMouseButtonDown(MouseButtons::LEFT_MOUSE_BUTTON))
		//		_camera->SetPos(_camera->transform.position + (glm::vec3(0, 0, 1) * speed * deltaTime));
		//	else if (Input::GetMouseButtonDown(MouseButtons::RIGHT_MOUSE_BUTTON))
		//		_camera->SetPos(_camera->transform.position + (glm::vec3(0, 0, -1) * speed * deltaTime));
		//
		//	if (Input::GetKey(Keycode::Q))
		//		_camera->SetRotY(_camera->transform.rotation.y + (speedRotationCamera * deltaTime));
		//	else if (Input::GetKey(Keycode::E))
		//		_camera->SetRotY(_camera->transform.rotation.y - (speedRotationCamera * deltaTime));
		//
		//	if (Input::GetKeyDown(Keycode::ALPHA0)) {
		//		_camera->SetPos(0.0f, 0.0f, 0.0f);
		//		_camera->SetRotations(0, 0, 0);
		//	}
		//
		//	_camera->LookAt(_camera->transform.position + _camera->transform.forward);
		//}

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

		if (Input::GetKey(Keycode::ALPHA4))
			posXFootModel += deltaTime;
		else if (Input::GetKey(Keycode::ALPHA5))
			posXFootModel -= deltaTime;

		_model1->SetMeshPos(posXFootModel, 0, 0, 9);
		_model1->SetMeshPos(posXModel, 0, 0, 8);

		_camera->LookAt(_camera->transform.position + _camera->transform.forward);

		_camera->UseCamera();
		GetRenderer()->SetView(_camera->GetViewMatrix());
		GetLightManager()->UseLights();

		//GetLightManager()->GetPointLightByIndex(0)->SetPos(_camera->transform.position);
		//
		//GetLightManager()->GetSpotLightByIndex(0)->SetDirection(_camera->transform.forward);
		//GetLightManager()->GetSpotLightByIndex(0)->SetPos(_camera->transform.position.x, _camera->transform.position.y, _camera->transform.position.z);
		//
		//_shape->DrawShape();
		//_shape2->DrawShape();
		//_shape3->DrawShape();
		////
		//_model1->DrawModel();
		//_model2->DrawModel();
		//_model3->DrawModel();
		//_model4->DrawModel();
		//_model5->DrawModel();
		//
		//for (int i = 0; i < 5; i++)
		//	for (int j = 0; j < 5; j++) {
		//		_model6->SetPos(glm::vec3(i * 2, 2, 5 + j * 2));
		//		_model6->SetAffectedByLight(i % 2 == 0);
		//		_model6->DrawModel();
		//	}
		//
		//_model6->SetPos(glm::vec3(-1, 2, 7));
		//_model6->SetAffectedByLight(false);
		//_model6->DrawModel();

		_model1->DrawModel();

		GetWindow()->SwapBuffers();
	}
	void Game::End() {
		EndEngine();
	}
}