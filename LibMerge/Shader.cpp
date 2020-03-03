#include "Shader.h"

char* Shader::vs = ".vs";
char* Shader::fs = ".fs";

Shader::Shader()
{
}

Shader::Shader(const char * _vs, const char * _fs)
{
	CreateShader(_vs, _fs);
}


Shader::~Shader()
{
}

unsigned int Shader::GetShaderProgram()
{
	return m_ShaderProgram;
}

void Shader::Use()
{
	glUseProgram(m_ShaderProgram);
}

void Shader::SetInt(char * _name, int value)
{
	auto location = glGetUniformLocation(m_ShaderProgram, _name);
	glUniform1i(location, value);
}

void Shader::SetMatrix(char * _name, mat4 _val)
{
	auto location = glGetUniformLocation(m_ShaderProgram, _name);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(_val));
}

void Shader::CreateShader(const char * vs, const char * fs)
{
	auto vcode = File::Read(vs);
	auto scode = File::Read(fs);
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vcode, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &m_Success);
	if (!m_Success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, m_InfoLog);
		std::cout << "¶¥µã×ÅÉ«Æ÷±àÒë´íÎó\n" << m_InfoLog << std::endl;
	}
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &scode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &m_Success);
	if (!m_Success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, m_InfoLog);
		std::cout << "Æ¬Ôª×ÅÉ«Æ÷±àÒë´íÎó\n" << m_InfoLog << std::endl;
	}
	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShader);
	glAttachShader(m_ShaderProgram, fragmentShader);
	glLinkProgram(m_ShaderProgram);
	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &m_Success);
	if (!m_Success) 
	{
		glGetProgramInfoLog(m_ShaderProgram, 512, NULL, m_InfoLog);
		std::cout << "×ÅÉ«Æ÷Á´½Ó´íÎó\n" << m_InfoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	delete[] vcode;
	delete[] scode;
}
