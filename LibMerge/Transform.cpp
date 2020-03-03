#include "Transform.h"

Transform::Transform()
{
	m_Position = vec3(0.0f, 0.0f, 0.0f);
	m_Scale = vec3(1.0f, 1.0f, 1.0f);
	m_Qua = Quaternion(vec3(0));
	m_UpDir = vec3(0.0f, 1.0f, 0.0f);
	m_FrontDir = vec3(0.0f, 0.0f, 1.0f);
	m_RightDir = vec3(1.0f, 0.0f, 0.0f);
	m_IsDity = true;
}

void Transform::Move(vec3 dis)
{
	m_Position += dis;
	m_IsDity = true;
}

void Transform::SetPosition(vec3 _val)
{
	if (_val == m_Position)
	{
		return;
	}
	m_IsDity = true;
	m_Position = _val;
}

vec3 Transform::GetPosition()
{
	return m_Position;
}

void Transform::SetScale(vec3 _val)
{
	if (_val == m_Scale)
	{
		return;
	}
	m_IsDity = true;
	m_Scale = _val;
}

vec3 Transform::GetScale()
{
	return m_Scale;
}

void Transform::SetEulerAngle(vec3 _val)
{
	m_IsDity = true;
	m_Qua.SetEulerAngle(_val);
	vec3 ag = _val;
	//m_FrontDir.x = cos(radians(ag.x)) * cos(radians(ag.y));
	//m_FrontDir.y = sin(radians(ag.x));
	//m_FrontDir.z = cos(radians(ag.x)) * sin(radians(ag.y));
	//m_FrontDir = normalize(m_FrontDir);
	//m_RightDir = normalize(cross(vec3(0.0f, 1.0f, 0.0f), m_FrontDir));
	//m_UpDir = normalize(cross(m_FrontDir, m_RightDir));
}

vec3 Transform::GetEulerAngle()
{
	return m_Qua.ToEulerAngle();
}

vec4 Transform::GetQuaternion()
{
	return m_Qua.GetQuaternion();
}

mat4 Transform::GetModelMatrix()
{
	if (m_IsDity)
	{
		m_IsDity = false;
		m_ModelMatrix = mat4(1.0f);
		m_ModelMatrix = translate(m_ModelMatrix, m_Position);
		m_ModelMatrix = scale(m_ModelMatrix, m_Scale);
		//ZXY
		m_ModelMatrix = m_Qua.ToRotationMatrix() * m_ModelMatrix;
		/*m_ModelMatrix = rotate(m_ModelMatrix, radians(m_EulerAngle.z), vec3(0.0f, 0.0f, 1.0f));
		m_ModelMatrix = rotate(m_ModelMatrix, radians(m_EulerAngle.x), vec3(1.0f, 0.0f, 0.0f));
		m_ModelMatrix = rotate(m_ModelMatrix, radians(m_EulerAngle.y), vec3(0.0f, 1.0f, 0.0f));*/
	}
	return m_ModelMatrix;
}

vec3 Transform::GetUpDir()
{
	vec3 v = (mat3)m_Qua.ToRotationMatrix() * vec3(0, 1, 0);
	return normalize(v);
}

vec3 Transform::GetFrontDir()
{
	vec3 v = (mat3)m_Qua.ToRotationMatrix() * vec3(0, 0, 1);
	return normalize(v);
}

vec3 Transform::GetRightDir()
{
	vec3 v = (mat3)m_Qua.ToRotationMatrix() * vec3(1, 0, 0);
	return normalize(v);
}

void Transform::Rotate(vec3 _ag)
{
	if (_ag == vec3())
	{
		return;
	}
	m_IsDity = true;
	m_Qua.Rotate(_ag);

}

void Transform::Rotate(vec3 aixs, float angle)
{
	if (angle == 0)
	{
		return;
	}
	m_IsDity = true;
	m_Qua.Rotate(aixs, angle);

}


