#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Quaternion.h"
using namespace glm;

#define RIGHT	vec3(1, 0, 0)
#define UP		vec3(0, 1, 0)
#define FORWARD vec3(0, 0, 1)

class Transform
{
public:
	Transform();
	void Move(vec3 dis);
	void SetPosition(vec3 _val);
	vec3 GetPosition();
	void SetScale(vec3 _val);
	vec3 GetScale();
	void SetEulerAngle(vec3 _val);
	vec3 GetEulerAngle();
	vec4 GetQuaternion();
	mat4 GetModelMatrix();
	vec3 GetUpDir();
	vec3 GetFrontDir();
	vec3 GetRightDir();
	void Rotate(vec3 ag);
	void Rotate(vec3 aixs, float angle);
private:
	Quaternion m_Qua;
	vec3 m_Position;
	vec3 m_Scale;
	// pitchÈÆRightÐý×ª  yawÈÆUpÐý×ª  roll ÈÆFrontÐý×ª
	bool m_IsDity;
	mat4 m_ModelMatrix;
	vec3 m_UpDir;
	vec3 m_FrontDir;
	vec3 m_RightDir;
};

