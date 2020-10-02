#include "Window.h"
#include <iostream>

#include <glew.h>
#include <GLFW/glfw3.h>

namespace Graficos1 {
	
	Window::Window() {

	}
	Window::~Window() {

	}

	int Window::MakeWindow(int width, int height, const char* windowName, GLFWmonitor* fullScreen) {
		_window = glfwCreateWindow(width, height, windowName, fullScreen, NULL);
		if (!_window) {
			std::cout << "Fail to create GLFW window" << std::endl;
			return 0;
		}
		return 1;
	}

	void Window::InitWindow() {
		//Setear el contexto para usar GLEW
		//Par: GLFWwindow* creado anteriormente
		glfwMakeContextCurrent(_window);
	}

	int Window::CheckIfWindowIsOpen() {
		return (!glfwWindowShouldClose(_window));
	}
	void Window::SwapBuffers() {
		glfwSwapBuffers(_window);
	}
	void Window::DestroyWindow() {
		glfwDestroyWindow(_window);
	}
	GLFWwindow* Window::GetWindow(){
		return _window;
	}
}