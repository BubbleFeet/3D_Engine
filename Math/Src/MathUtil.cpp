#pragma once
#include "Precompiled.h"

#include <MathUtil.h>

using namespace Math;

const float Math::kDegToRad = 3.1415926535f / 180;
const float Math::kPi = 3.1415926535f;
const float Math::kTwoPi = 3.1415926535f * 2;
const float Math::kRadToDeg = 180 / 3.1415926535f;

Matrix Matrix::RotationAxis(const Vector3& axis, float rad)
{
	Vector3 norm = Normalize(axis);

	const float x = norm.x;
	const float y = norm.y;
	const float z = norm.z;
	const float sinRad = sinf(rad);
	const float cosRad = cosf(rad);

	Matrix ret(
		cosf(rad) + (x * x * (1.0f - cosf(rad))), x * y * (1.0f - cosf(rad)) + z * sinf(rad), x * z * (1.0f - cosf(rad)) - y * sinf(rad), 0.0f,
		x * y * (1.0f - cosf(rad)) - z * sinf(rad), cosf(rad) + (y * y * (1.0f - cosf(rad))), y * z * (1.0f - cosf(rad)) + x * sinf(rad), 0.0f,
		x * z * (1.0f - cosf(rad)) + y * sinf(rad), y * z * (1.0f - cosf(rad)) - x * sinf(rad), cosf(rad) + (z * z * (1.0f - cosf(rad))), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	return ret;
}

inline Quaternion Math::RotationAxis(const Vector3& axis, float rad)
{
	float c = cosf(rad * 0.5f);
	float s = sinf(rad * 0.5f);

	Vector3 vec = Normalize(axis);

	return Quaternion(vec.x * s, vec.y * s, vec.z * s, c);
}

inline Matrix Math::ToMatrix(const Quaternion& q)
{
	const float xSq = q.x * q.x;
	const float ySq = q.y * q.y;
	const float zSq = q.z * q.z;

	return Matrix(
				1 - (2 * ySq) - (2 * zSq),	(2 * q.x * q.y) - (2 * q.w * q.z),	(2 * q.x * q.z) + (2 * q.w * q.y),	0,
		(2 * q.x * q.y) + (2 * q.w * q.z),			1 - (2 * xSq) - (2 * zSq),	(2 * q.y * q.z) - (2 * q.w * q.x),	0,
		(2 * q.x * q.z) - (2 * q.w * q.y),	(2 * q.y * q.z) + (2 * q.w * q.x),			1 - (2 * xSq) - (2 * ySq),	0,
										0,									0,									0,	1
	);
}

inline Quaternion Math::Slerp(Quaternion q0, Quaternion q1, float t)
{
	float dot = (q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z) + (q0.w * q1.w);

	if (dot < 0.0f)
	{
		dot = -dot;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
	}

	else if (dot > 0.999f)
	{
		return Normalize(Lerp(q0, q1, t));
	}

	float theta = acosf(dot);
	float sintheta = sinf(theta);
	float scale0 = sinf(theta * (1.0f - t)) / sintheta;
	float scale1 = sinf(theta * t) / sintheta;

	return Quaternion(
		(q0.x * scale0) + (q1.x * scale1),
		(q0.y * scale0) + (q1.y * scale1),
		(q0.z * scale0) + (q1.z * scale1),
		(q0.w * scale0) + (q1.w * scale1)
	);

}

inline Vector3 Reflect(const Vector3& v, const Vector3& n)
{
	float dotVector = 2 * Dot(v, Normalize(n));
	Vector3 reflectVector = v - (n * dotVector);

	return reflectVector;
}