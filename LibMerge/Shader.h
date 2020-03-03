#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "File.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Shader
{
public:
	Shader();
	Shader(const char * _vs, const char * _fs);
	~Shader();
	unsigned int GetShaderProgram();
	void Use();
	void SetInt(char * _name, int value);
	void SetMatrix(char* _name, mat4 _val);
private:
	static char* vs;
	static char* fs;
	int m_Success;
	char m_InfoLog[512];
	unsigned int m_ShaderProgram;
	void CreateShader(const char* vs, const char * fs);
};

