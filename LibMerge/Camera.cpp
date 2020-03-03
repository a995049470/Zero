#include "Camera.h"

Camera::Camera()
{
	m_Transform = new Transform();
	m_Near = 0.1f;
	m_Far = 1000.0f;
	m_Fov = 45.0f;
}

Camera::~Camera()
{
	delete m_Transform;
}

Transform& Camera::GetTransform()
{
	return *m_Transform;
}

mat4 Camera::GetViewMatrix()
{	
	auto mat = lookAt(m_Transform->GetPosition(), m_Transform->GetPosition() +
		m_Transform->GetFrontDir(), m_Transform->GetUpDir());
	return mat;
}

mat4 Camera::GetProMatrix()
{
	float height = (float)Window::GetSinleton().GetHeight();
	float width = (float)Window::GetSinleton().GetWidth();
	auto mat = perspective(radians(m_Fov), width / height, m_Near, m_Far);
	return mat;
}



