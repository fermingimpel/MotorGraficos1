#include "Renderer.h"
#include <iostream>
#include <glew.h>
#include <glfw/glfw3.h>
#include <glm\gtc\type_ptr.hpp>

namespace Graficos1 {

	typedef unsigned int uint;
	
	static uint posLocation;
	static uint colorLocation;
	static uint uniformModel;

	Renderer::Renderer() {

	}
	Renderer::~Renderer() {

	}
	int Renderer::InitGlew() {
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK) {
			std::cout << "Error in Glew Init" << std::endl;
			return 0;
		}

		return 1;
	}
	void Renderer::SetBuffers(int tam, float* verts, uint& vbo, uint& vao) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, tam, verts, GL_STATIC_DRAW);

	}
	void Renderer::SetQuadThings(int tam, uint* indexs) {
		unsigned int ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, tam, indexs, GL_STATIC_DRAW);
	}
	void Renderer::SetAttribs(glm::mat4 model, TypeShader t) {
		posLocation = glGetAttribLocation(GetShader(), "pos");
		glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		glEnableVertexAttribArray(posLocation);

		uint useTextureLoc = glGetUniformLocation(GetShader(), "useTexture");
		glUseProgram(GetShader());
		if (t == TypeShader::Colour) {
			glUniform1i(useTextureLoc, false);
			unsigned int colorLocation = glGetAttribLocation(GetShader(), "colorrrr");
			glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(colorLocation);
		}
		else {
			glUniform1i(useTextureLoc, true);
			unsigned int texLocation = glGetAttribLocation(GetShader(), "tex");
			glVertexAttribPointer(texLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(texLocation);
		}

		unsigned int uniformModel = glGetUniformLocation(GetShader(), "model");
		glUseProgram(GetShader());
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Renderer::InitShaders() {
		CompileShaders();
	}

	void Renderer::StopShaders() {
		glDeleteProgram(_shader);
	}

	void Renderer::Draw(uint shape, int verts, uint vao, uint vbo, float* vertexs, float tamVertexs, TypeShader t){
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, tamVertexs, vertexs, GL_STATIC_DRAW);

		uint useTextureLoc = glGetUniformLocation(GetShader(), "useTexture");
		glUseProgram(GetShader());
		if (t == TypeShader::Colour) {
			glUniform1i(useTextureLoc, false);
			unsigned int colorLocation = glGetAttribLocation(GetShader(), "colorrrr");
			glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(colorLocation);
		}
		else {
			glUniform1i(useTextureLoc, true);
			unsigned int texLocation = glGetAttribLocation(GetShader(), "tex");
			glVertexAttribPointer(texLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(texLocation);
		}

		switch (shape) {
		case GL_QUADS:
			glDrawElements(GL_TRIANGLES, verts, GL_UNSIGNED_INT, nullptr);
			break;
		case GL_TRIANGLES:
			glDrawArrays(GL_TRIANGLES, 0, verts);
			break;
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	void Renderer::UpdateModel(glm::mat4 model) {
		uniformModel = glGetUniformLocation(GetShader(), "model");
		glUseProgram(GetShader());
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	}

	uint Renderer::GetShader() {
		return _shader;
	}

	void Renderer::AddShader(uint program, const char* shaderCode, uint type) {
		uint theShader = glCreateShader(type);

		const char* code[1];
		code[0] = shaderCode;

		int codeLength[1];
		codeLength[0] = strlen(shaderCode);

		glShaderSource(theShader, 1, code, codeLength);

		glCompileShader(theShader);

		int result = 0;
		char eLog[1024] = { 0 };

		glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

		if (!result) {
			glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
			std::cout << "Error compiling the " << type << " program: " << eLog << std::endl;
			return;
		}
		glAttachShader(program, theShader);
	}

	void Renderer::CompileShaders() {
		_shader = glCreateProgram();
		if (!_shader) {
			std::cout << "Error creating the shader program!" << std::endl;
			return;
		}

		AddShader(_shader, vShader, GL_VERTEX_SHADER);
		AddShader(_shader, fShader, GL_FRAGMENT_SHADER);

		int result = 0;
		char eLog[1024] = { 0 };

		glLinkProgram(_shader);

		glGetProgramiv(_shader, GL_LINK_STATUS, &result);

		if (!result) {
			glGetProgramInfoLog(_shader, sizeof(eLog), NULL, eLog);
			std::cout << "Error linking program: " << eLog << std::endl;
			return;
		}

		glValidateProgram(_shader);
		glGetProgramiv(_shader, GL_VALIDATE_STATUS, &result);
		if (!result) {
			glGetProgramInfoLog(_shader, sizeof(eLog), NULL, eLog);
			std::cout << "Error validating program: " << eLog << std::endl;
			return;
		}
	}

}