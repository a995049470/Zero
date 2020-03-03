#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh
{
public:
	Mesh();
	~Mesh();
	Mesh(float* _vertices, unsigned int _vsize, int* _locationStep = NULL, unsigned int _lsize = NULL, int* _indices = NULL, unsigned int _isize = NULL);
	void SetVertices(float* _vertices, unsigned int _vsize, int* _locationStep = NULL, unsigned int _lsize = NULL);
	void SetIndices(int * _indices = NULL, unsigned int _isize = NULL);
	void BindVertexArray();
	unsigned int GetVAO();
private:
	int* m_LocationStep;
	unsigned int m_LSize;
	unsigned int m_VB0;
	unsigned int m_VAO;
	unsigned int m_EBO;
	float* m_Vertices;
	unsigned int m_VSize;
	int* m_Indices;
	unsigned int m_ISize;

};

