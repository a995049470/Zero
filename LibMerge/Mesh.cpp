#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}



Mesh::Mesh(float * _vertices, unsigned int _vsize, int * _locationStep, unsigned int _lsize, int * _indices, unsigned int _isize)
{
	SetVertices(_vertices, _vsize, _locationStep, _lsize);
	SetIndices(_indices, _isize);
	BindVertexArray();
}


void Mesh::SetVertices(float * _vertices, unsigned int _vsize, int * _locationStep, unsigned int _lsize)
{
	m_VSize = _vsize;
	m_Vertices = _vertices;
	if (!_locationStep)
	{
		m_LocationStep = new int[1]{ 3 };
		m_LSize = 1;
	}
	else
	{
		m_LocationStep = _locationStep;
		m_LSize = _lsize;
	}
	
}



void Mesh::SetIndices(int * _indices, unsigned int _isize)
{
	if (!_indices)
	{
		m_ISize = m_VSize / 3;
		m_Indices = new int[m_ISize];
		for (unsigned i = 0; i < m_ISize; i++)
		{
			m_Indices[i] = i;
		}
	}
	else
	{
		m_Indices = _indices;
		m_ISize = _isize;		
	}
	
}



void Mesh::BindVertexArray()
{
	glGenBuffers(1, &m_VB0);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB0);
	glBufferData(GL_ARRAY_BUFFER, m_VSize * sizeof(float), m_Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_ISize * sizeof(int), m_Indices, GL_STATIC_DRAW);
	
	int offset = 0;
	int len = 0;
	int total = m_LocationStep[m_LSize - 1];
	for (unsigned i = 0; i < m_LSize; i++)
	{
		if (i == 0)
		{
			offset = 0;
		}
		else
		{
			offset = m_LocationStep[i - 1];
		}
		len = m_LocationStep[i] - offset;
		glVertexAttribPointer(i, len, GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)(offset *  sizeof(float)));
		glEnableVertexAttribArray(i);
	}
	
	
}

unsigned int Mesh::GetVAO()
{
	return m_VAO;
}
