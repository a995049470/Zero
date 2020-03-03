#pragma once

#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


using namespace std;
class Texture
{
public :
	Texture(char * _name);
	void Bind(int index = 0);
private :
	
	void Load(char * _name);
	unsigned int m_Texture;
	int m_Height;
	int m_Width;
	int m_Channels;
};

