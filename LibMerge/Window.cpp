#include "Window.h"
typedef void(Window::*wptr)(GLFWwindow*, int, int);
typedef void(*ptr)(GLFWwindow*, int, int);

Window::Window()
{

}

Window::~Window()
{
}



void Window::CreateWindow(int _height, int _width)
{
	m_Height = _height;
	m_Width = _width;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_WinPtr = glfwCreateWindow(m_Height, m_Width, "LearnOpenGL", NULL, NULL);
	if (m_WinPtr == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	auto lamfunc = [](GLFWwindow* window, int x, int y)
	{
		Window::GetSinleton().WindowSizeChangeCallBack(window, x, y);
	};
	glfwSetFramebufferSizeCallback(m_WinPtr, lamfunc);
	glfwMakeContextCurrent(m_WinPtr);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glViewport(0, 0, m_Height, m_Width);
}

bool Window::Run()
{
	if (glfwWindowShouldClose(m_WinPtr))
	{
		Close();
		return false;
	}
	ProcessInput(m_WinPtr);
	
	return true;
}

void Window::ProcessInput(GLFWwindow * window)
{
	
}

void Window::WindowSizeChangeCallBack(GLFWwindow * window, int width, int height)
{
	m_Width = width;
	m_Height = height;
	
	glViewport(0, 0, m_Height, m_Width);
}

int Window::GetHeight()
{
	return m_Height;
}

int Window::GetWidth()
{
	return m_Width;
}

GLFWwindow* Window::GetWinPtr()
{
	return m_WinPtr;
}


void Window::Close()
{
	glfwTerminate();
}






