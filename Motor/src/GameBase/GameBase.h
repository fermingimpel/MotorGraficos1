#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "../src/Exports/Exports.h"
#include "../src/Window/Window.h"
#include "../src/Renderer/Renderer.h"
#include "../src/Shape/Shape.h"
#include "../src/Sprite/Sprite.h"
#include "../src/Input/Input.h"
#include "../src/CollisionManager/CollisionManager.h"
#include "../src/Camera/Camera.h"
#include "../src/Light/LightManager.h"
#include "../Model/Model.h"
#include "../Timer/Timer.h"

struct GLFWmonitor;

namespace Coco {

	class GraficosEngine_API GameBase {
		Window* _window;
		Renderer* _renderer;
		CollisionManager* _collisionManager;
		LightManager* _lightManager;
	public:
		GameBase();
		~GameBase();

		int StartEngine(int width, int height, const char* windowName);
		void UpdateEngine();
		void EndEngine();

		Window* GetWindow();
		Renderer* GetRenderer();
		Input* GetInput();
		LightManager* GetLightManager();

		virtual void Start() = 0;
		virtual void Update(float deltaTime) = 0;
		void virtual End() = 0;
	};

}

#endif