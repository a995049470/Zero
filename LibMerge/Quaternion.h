#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include "BitHelp.h"
using namespace glm;
class Quaternion
{
public:
	Quaternion();
	Quaternion(vec4 qua);
	Quaternion(vec3 ag);
	vec3 ToEulerAngle();
	mat4 ToRotationMatrix();
	vec4 GetQuaternion();
	void SetEulerAngle(vec3 ag);
	void Rotate(vec3 ag);
	void Rotate(vec3 aixs, float angle);
	Quaternion operator * (Quaternion r);
private:
	vec4 EulerToQua(vec3 ag);
	static vec4 QuaMul(vec4 l, vec4 r);
	int m_DirtyBit;
	vec4 m_Qua;
	vec3 m_Ag;
	mat4 m_Matrix;
};

