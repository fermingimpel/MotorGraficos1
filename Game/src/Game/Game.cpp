#include "Game.h"
#include <time.h>
#include <iostream>
#include "../src/Timer/Timer.h"

namespace Graficos1 {

	Game::Game() :GameBase() {
	}
	Game::~Game() {
		if (_shape != NULL) {
			delete _shape;
			_shape = NULL;
		}
		if (_shape != NULL) {
			delete _shape2;
			_shape2 = NULL;
		}
		if (_camera != NULL) {
			delete _camera;
			_camera = NULL;
		}
	}
	void Game::Start() {
		StartEngine(1366, 768, "Coco");

		_camera = new Camera();
		_camera->InitCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
		_camera->SetPos(0.0f, 0.0f, 0.0f);
		GetRenderer()->SetView(_camera->CalculateViewMatrix());

		_shape = new Shape(GetRenderer(), NULL);
		_shape->InitShape(TypeShape::Cube, TypeShader::Colour);
		_shape->CreateShape();
		_shape->SetScale(0.33f, 0.33f, 0.33f);
		_shape->SetPos(0.0f, 0.0f, -3.0f);

		_shape2 = new Shape(GetRenderer(), NULL);
		_shape2->InitShape(TypeShape::Cube, TypeShader::Colour);
		_shape2->CreateShape();
		_shape2->SetScale(0.33f, 0.33f, 0.33f);
		_shape2->SetPos(0.0f, 1.0f, -3.0f);
	}
	void Game::Play() {
		UpdateEngine();
	}
	float speed = 5.0f;
	float speedRotationCamera = 50.0f;
	float timer = 0.0f;
	void Game::Update() {
		GetWindow()->ClearWindow(0.5f, 0.5f, 0.5f, 1.0f);
		GetRenderer()->SetView(_camera->CalculateViewMatrix());

		Timer::DeltaTime(timer);

		if (Input::GetKeyDown(Keycode::W)) 
			_camera->SetPos(_camera->positionVec.x, _camera->positionVec.y + (speed * timer), _camera->positionVec.z);
		else if (Input::GetKeyDown(Keycode::S)) 
			_camera->SetPos(_camera->positionVec.x, _camera->positionVec.y - (speed * timer), _camera->positionVec.z);
		

		if (Input::GetKeyDown(Keycode::A)) 
			_camera->SetPos(_camera->positionVec.x - (speed * timer), _camera->positionVec.y, _camera->positionVec.z);
		else if (Input::GetKeyDown(Keycode::D)) 
			_camera->SetPos(_camera->positionVec.x + (speed * timer), _camera->positionVec.y, _camera->positionVec.z);
	
		if (Input::GetKeyDown(Keycode::Q)) 
			_camera->SetPos(_camera->positionVec.x, _camera->positionVec.y, _camera->positionVec.z + (speed * timer));
		else if (Input::GetKeyDown(Keycode::E)) 
			_camera->SetPos(_camera->positionVec.x, _camera->positionVec.y, _camera->positionVec.z - (speed * timer));

		if (Input::GetMouseButtonDown(MouseButtons::LEFT_MOUSE_BUTTON)) 
			_camera->SetPitch(_camera->GetPitch() + (speed * timer));
		else if (Input::GetMouseButtonDown(MouseButtons::RIGHT_MOUSE_BUTTON)) 
			_camera->SetPitch(_camera->GetPitch() - (speed * timer));

		if (Input::GetKeyDown(Keycode::R))
			_camera->SetYaw(_camera->GetYaw() + (speedRotationCamera * timer));
		else if (Input::GetKeyDown(Keycode::T))
			_camera->SetYaw(_camera->GetYaw() - (speedRotationCamera * timer));

		_shape->DrawShape();
		_shape2->DrawShape();
		
		GetWindow()->SwapBuffers();
	}
	void Game::End() {
		EndEngine();
	}
}