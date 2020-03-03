#include "Quaternion.h"

Quaternion::Quaternion()
{
	m_DirtyBit = 3;
	m_Qua = EulerToQua(vec3());
	m_Ag = vec3();
	m_Matrix = mat4();
}

Quaternion::Quaternion(vec4 qua)
{
	m_DirtyBit = 3;
	m_Qua = qua;
	m_Ag = vec3();
	m_Matrix = mat4();
}

Quaternion::Quaternion(vec3 ag)
{
	m_DirtyBit = 3;
	m_Qua = EulerToQua(ag);
	m_Ag = ag;
	m_Matrix = mat4();
}


vec3 Quaternion::ToEulerAngle()
{
	if (BitHelp::GetTargetBit(m_DirtyBit, 1) == 0)
	{
		return m_Ag;
	}
	BitHelp::SetTargetBit(m_DirtyBit, 1, 0);
	//刷新欧拉角
	float q0 = m_Qua.w;

	float q1 = m_Qua.y;
	float q2 = m_Qua.x;
	float q3 = m_Qua.z;

	float f1 = 2 * (q0 * q1 + q2 * q3);
	float f2 = 1 - 2 * (q1 * q1 + q2 * q2);
	float f3 = 2 * (q0 * q2 - q3 * q1);
	float f4 = 2 * (q0 * q3 + q1 * q2);
	float f5 = 1 - 2 * (q2 * q2 + q3 * q3);
	m_Ag.y = atan2(f1, f2) / pi<float>() * 180.0f;
	m_Ag.x = asin(f3) / pi<float>() * 180.0f;
	m_Ag.z = atan2(f4, f5) / pi<float>() * 180.0f;

	return m_Ag;
}

mat4 Quaternion::ToRotationMatrix()
{
	if (BitHelp::GetTargetBit(m_DirtyBit, 2) == 0)
	{
		return m_Matrix;
	}
	BitHelp::SetTargetBit(m_DirtyBit, 2, 0);
	//刷新旋转矩阵
	m_Matrix = mat4(1.0f);
	//m_Matrix = rotate(m_Matrix, acos(m_Qua.x), vec3(m_Qua.y, m_Qua.z, m_Qua.w));
	float w = m_Qua.w;

	float x = m_Qua.x;
	float y = m_Qua.y;
	float z = m_Qua.z;
	//列主式 改 行主式 !!
	m_Matrix[0][0] = 1 - 2 * y * y - 2 * z * z;
	m_Matrix[1][0] = 2 * x * y - 2 * w * z;
	m_Matrix[2][0] = 2 * x * z + 2 * w * y;

	m_Matrix[0][1] = 2 * x * y + 2 * w * z;
	m_Matrix[1][1] = 1 - 2 * x * x - 2 * z * z;
	m_Matrix[2][1] = 2 * y * z - 2 * w * x;

	m_Matrix[0][2] = 2 * x * z - 2 * w * y;
	m_Matrix[1][2] = 2 * y * z + 2 * w * x;
	m_Matrix[2][2] = 1 - 2 * x * x - 2 * y * y;

	return m_Matrix;
}

vec4 Quaternion::GetQuaternion()
{
	return m_Qua;
}

void Quaternion::SetEulerAngle(vec3 ag)
{
	BitHelp::SetTargetBit(m_DirtyBit, 2, 1);
	BitHelp::SetTargetBit(m_DirtyBit, 1, 1);
	m_Qua = EulerToQua(ag);
	m_Ag = ag;
}

void Quaternion::Rotate(vec3 ag)
{
	if (ag == vec3())
	{
		return;
	}
	
	m_Ag = ToEulerAngle() + ag;
	m_Qua = EulerToQua(m_Ag);
	m_DirtyBit = 2;
}

void Quaternion::Rotate(vec3 aixs, float angle)
{
	if (aixs == vec3())
	{
		return;
	}
	vec4 v = vec4();
	float r = radians(angle / 2);
	aixs = normalize(aixs);
	float s = sin(r);
	float c = cos(r);

	v.w = c;

	v.x = s * aixs.x;
	v.y = s * aixs.y;
	v.z = s * aixs.z;
	m_Qua = QuaMul(v, m_Qua);
	m_DirtyBit = 3;
}

Quaternion Quaternion::operator * (Quaternion r)
{
	vec4 res = QuaMul(this->m_Qua, r.GetQuaternion());
	return Quaternion(res);
}

//OK
vec4 Quaternion::EulerToQua(vec3 ag)
{
	vec4 qua = vec4();
	float s1 = sin(radians(ag.y / 2));
	float s2 = sin(radians(ag.x / 2));
	float s3 = sin(radians(ag.z / 2));

	float c1 = cos(radians(ag.y / 2));
	float c2 = cos(radians(ag.x / 2));
	float c3 = cos(radians(ag.z / 2));

	qua.w = c1 * c2 * c3 + s1 * s2 * s3;
	qua.x = c1 * s2 * c3 + s1 * c2 * s3;
	qua.y = s1 * c2 * c3 - c1 * s2 * s3;
	qua.z = c1 * c2 * s3 - s1 * s2 * c3;

	return qua;
}

vec4 Quaternion::QuaMul(vec4 l, vec4 r)
{
	//???
	vec4 res;
	float w1 = l.w;
	vec3 v1 = vec3(l.x, l.y, l.z);
	float w2 = r.w;
	vec3 v2 = vec3(r.x, r.y, r.z);
	float w3 = w1 * w2 - dot(v1, v2);
	vec3 v3 = w1 * v2 + w2 * v1 + cross(v1, v2);
	res = vec4(v3, w3);
	
	/*res.x = l.y * r.z - l.z * r.y + l.w * r.x + l.x * r.w;
	res.y = l.z * r.x - l.x * r.z + l.w * r.y + l.y * r.w;
	res.z = l.x * r.y - l.y * r.x + l.w * r.z + l.z * r.w;
	res.w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;*/

	return res;
}
