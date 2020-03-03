#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Singleton.h"
using namespace std;
class Window : public Singleton<Window>
{
public:
	Window();
	~Window();
	void CreateWindow(int height, int width);
	bool Run();
	void ProcessInput(GLFWwindow* window);
	void WindowSizeChangeCallBack(GLFWwindow* window, int width, int height);
	int GetHeight();
	int GetWidth();
	GLFWwindow* GetWinPtr();
private:
	void Close();
	int m_Height;
	int m_Width;
	GLFWwindow* m_WinPtr;

};

