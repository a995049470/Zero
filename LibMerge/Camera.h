#pragma once
#include "Transform.h"
#include "Window.h"
class Camera
{
public:
	Camera();
	~Camera();
	Transform& GetTransform();
	mat4 GetViewMatrix();
	mat4 GetProMatrix();
	
private:
	Transform* m_Transform;
	float m_Fov;
	float m_Near;
	float m_Far;
};

