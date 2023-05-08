//====================================================================================================
// Filename:	Math.h
// Created by:	Peter Chan
//====================================================================================================

#ifndef INCLUDED_ENGINE_MATH_H
#define INCLUDED_ENGINE_MATH_H
#include <cmath>
namespace Math
{
struct Vector2
{
	float x, y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float inX, float inY) : x(inX), y(inY) {}

	static Vector2 Zero() { return Vector2(); }
	static Vector2 One() { return Vector2(1.0f, 1.0f); }
	static Vector2 XAxis() { return Vector2(1.0f, 0.0f); }
	static Vector2 YAxis() { return Vector2(0.0f, 1.0f); }

	Vector2 operator-() const { return Vector2(-x, -y); }
	Vector2 operator+(const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator-(const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator*(float s) const { return Vector2(x * s, y * s); }
	Vector2 operator/(float s) const { return Vector2(x / s, y / s); }

	Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
	Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	Vector2& operator*=(float s) { x *= s; y *= s; return *this; }
	Vector2& operator/=(float s) { x /= s; y /= s; return *this; }
};

//----------------------------------------------------------------------------------------------------

struct Vector3
{
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}

	static Vector3 Zero() { return Vector3(); }
	static Vector3 One() { return Vector3(1.0f, 1.0f, 1.0f); }
	static Vector3 XAxis() { return Vector3(1.0f, 0.0f, 0.0f); }
	static Vector3 YAxis() { return Vector3(0.0f, 1.0f, 0.0f); }
	static Vector3 ZAxis() { return Vector3(0.0f, 0.0f, 1.0f); }

	Vector3 operator-() const { return Vector3(-x, -y, -z); }
	Vector3 operator+(const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator-(const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
	Vector3 operator/(float s) const { return Vector3(x / s, y / s, z / s); }
	float& operator[](size_t i) { return (&x)[i]; }
	float operator[](size_t i) const { return (&x)[i]; }

	Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
	Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }
};

//----------------------------------------------------------------------------------------------------

struct Vector4
{
	float x, y, z, w;

	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(float inX, float inY, float inZ, float inW) : x(inX), y(inY), z(inZ), w(inW) {}

	static Vector4 Zero() { return Vector4(); }
	static Vector4 One() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
	static Vector4 Black() { return Vector4(0.0f, 0.0f, 0.0f, 1.0f); }
	static Vector4 Gray() { return Vector4(0.5f, 0.5f, 0.5f, 1.0f); }
	static Vector4 DarkGray() { return Vector4(0.25f, 0.25f, 0.25f, 1.0f); }
	static Vector4 White() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
	static Vector4 LightRed() { return Vector4(1.0f, 0.5f, 0.5f, 1.0f); }
	static Vector4 Red() { return Vector4(1.0f, 0.0f, 0.0f, 1.0f); }
	static Vector4 Green() { return Vector4(0.0f, 1.0f, 0.0f, 1.0f); }
	static Vector4 Blue() { return Vector4(0.0f, 0.0f, 1.0f, 1.0f); }
	static Vector4 Yellow() { return Vector4(1.0f, 1.0f, 0.0f, 1.0f); }
	static Vector4 Orange() { return Vector4(1.0f, 0.5f, 0.0f, 1.0f); }
	static Vector4 Cyan() { return Vector4(0.0f, 1.0f, 1.0f, 1.0f); }
	static Vector4 Magenta() { return Vector4(1.0f, 0.0f, 1.0f, 1.0f); }

	Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }
	Vector4 operator+(const Vector4& rhs) const { return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
	Vector4 operator-(const Vector4& rhs) const { return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
	Vector4 operator*(float s) const { return Vector4(x * s, y * s, z * s, w * s); }
	Vector4 operator/(float s) const { return Vector4(x / s, y / s, z / s, w / s); }

	Vector4& operator+=(const Vector4& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
	Vector4& operator-=(const Vector4& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }
	Vector4& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
	Vector4& operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }
};

//----------------------------------------------------------------------------------------------------

struct Quaternion
{
	float x, y, z, w;

	Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	static Quaternion Quaternion::Zero() { return Quaternion(0.0f, 0.0f, 0.0f, 0.0f); }
	static Quaternion Quaternion::Identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }

	Quaternion operator+(const Quaternion& rhs) const { return Quaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
	Quaternion operator*(float s) const { return Quaternion(x * s, y * s, z * s, w * s); }
	Quaternion operator/(float s) const { return Quaternion(x / s, y / s, z / s, w / s); }
};

//----------------------------------------------------------------------------------------------------

struct Matrix
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;

	Matrix()
		: _11(0.0f), _12(0.0f), _13(0.0f), _14(0.0f)
		, _21(0.0f), _22(0.0f), _23(0.0f), _24(0.0f)
		, _31(0.0f), _32(0.0f), _33(0.0f), _34(0.0f)
		, _41(0.0f), _42(0.0f), _43(0.0f), _44(0.0f)
	{}

	Matrix(
		float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44)
		: _11(_11), _12(_12), _13(_13), _14(_14)
		, _21(_21), _22(_22), _23(_23), _24(_24)
		, _31(_31), _32(_32), _33(_33), _34(_34)
		, _41(_41), _42(_42), _43(_43), _44(_44)
	{}

	static Matrix Zero() { return Matrix(); }
	static Matrix Identity() { return Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	static Matrix Translation(float x, float y, float z) { return Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, x, y, z, 1.0f); }
	static Matrix Translation(const Vector3& v) { return Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, v.x, v.y, v.z, 1.0f); }
	static Matrix Transpose(const Matrix& mat) { return Matrix( mat._11, mat._21, mat._31, mat._41, mat._12, mat._22, mat._32, mat._42, mat._13, mat._23, mat._33, mat._43, mat._14, mat._24, mat._34, mat._44 ); }
	static Matrix RotationX(float rad) { return Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cosf(rad), sinf(rad), 0.0f, 0.0f, -sinf(rad), cosf(rad), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	static Matrix RotationY(float rad) { return Matrix(cosf(rad), 0.0f, -sinf(rad), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sinf(rad), 0.0f, cosf(rad), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	static Matrix RotationZ(float rad) { return Matrix(cosf(rad), sinf(rad), 0.0f, 0.0f, -sinf(rad), cosf(rad), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	static Matrix Scaling(float s) { return Matrix(s, 0.0f, 0.0f, 0.0f, 0.0f, s, 0.0f, 0.0f, 0.0f, 0.0f, s, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	static Matrix Scaling(float sx, float sy, float sz) { return Matrix(sx, 0.0f, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, 0.0f, sz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }
	static Matrix Scaling(const Vector3& s) { return Matrix(s.x, 0.0f, 0.0f, 0.0f, 0.0f, s.y, 0.0f, 0.0f, 0.0f, 0.0f, s.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }

	static Matrix RotationAxis(const Vector3& axis, float rad);

	static Matrix MakeTranspose(const Matrix& mat)
	{
		Matrix ret;

		ret._11 = mat._11;
		ret._12 = mat._21;
		ret._13 = mat._31;
		ret._14 = mat._41;
		ret._21 = mat._12;
		ret._22 = mat._22;
		ret._23 = mat._33;
		ret._24 = mat._42;
		ret._31 = mat._13;
		ret._32 = mat._23;
		ret._33 = mat._33;
		ret._34 = mat._43;
		ret._41 = mat._14;
		ret._42 = mat._24;
		ret._43 = mat._34;
		ret._44 = mat._44;

		return ret;
	}

	Matrix operator-() const
	{
		return Matrix(
			-_11, -_12, -_13, -_14,
			-_21, -_22, -_23, -_24,
			-_31, -_32, -_33, -_34,
			-_41, -_42, -_43, -_44);
	}
	Matrix operator+(const Matrix& rhs) const
	{
		return Matrix(
			_11 + rhs._11, _12 + rhs._12, _13 + rhs._13, _14 + rhs._14,
			_21 + rhs._21, _22 + rhs._22, _23 + rhs._23, _24 + rhs._24,
			_31 + rhs._31, _32 + rhs._32, _33 + rhs._33, _34 + rhs._34,
			_41 + rhs._41, _42 + rhs._42, _43 + rhs._43, _44 + rhs._44);
	}
	Matrix operator-(const Matrix& rhs) const
	{
		return Matrix(
			_11 - rhs._11, _12 - rhs._12, _13 - rhs._13, _14 - rhs._14,
			_21 - rhs._21, _22 - rhs._22, _23 - rhs._23, _24 - rhs._24,
			_31 - rhs._31, _32 - rhs._32, _33 - rhs._33, _34 - rhs._34,
			_41 - rhs._41, _42 - rhs._42, _43 - rhs._43, _44 - rhs._44);
	}
	Matrix operator*(const Matrix& rhs) const
	{
		return Matrix(
			(_11 * rhs._11) + (_12 * rhs._21) + (_13 * rhs._31) + (_14 * rhs._41),
			(_11 * rhs._12) + (_12 * rhs._22) + (_13 * rhs._32) + (_14 * rhs._42),
			(_11 * rhs._13) + (_12 * rhs._23) + (_13 * rhs._33) + (_14 * rhs._43),
			(_11 * rhs._14) + (_12 * rhs._24) + (_13 * rhs._34) + (_14 * rhs._44),

			(_21 * rhs._11) + (_22 * rhs._21) + (_23 * rhs._31) + (_24 * rhs._41),
			(_21 * rhs._12) + (_22 * rhs._22) + (_23 * rhs._32) + (_24 * rhs._42),
			(_21 * rhs._13) + (_22 * rhs._23) + (_23 * rhs._33) + (_24 * rhs._43),
			(_21 * rhs._14) + (_22 * rhs._24) + (_23 * rhs._34) + (_24 * rhs._44),

			(_31 * rhs._11) + (_32 * rhs._21) + (_33 * rhs._31) + (_34 * rhs._41),
			(_31 * rhs._12) + (_32 * rhs._22) + (_33 * rhs._32) + (_34 * rhs._42),
			(_31 * rhs._13) + (_32 * rhs._23) + (_33 * rhs._33) + (_34 * rhs._43),
			(_31 * rhs._14) + (_32 * rhs._24) + (_33 * rhs._34) + (_34 * rhs._44),

			(_41 * rhs._11) + (_42 * rhs._21) + (_43 * rhs._31) + (_44 * rhs._41),
			(_41 * rhs._12) + (_42 * rhs._22) + (_43 * rhs._32) + (_44 * rhs._42),
			(_41 * rhs._13) + (_42 * rhs._23) + (_43 * rhs._33) + (_44 * rhs._43),
			(_41 * rhs._14) + (_42 * rhs._24) + (_43 * rhs._34) + (_44 * rhs._44));
	}
	Matrix operator*(float s) const
	{
		return Matrix(
			_11 * s, _12 * s, _13 * s, _14 * s,
			_21 * s, _22 * s, _23 * s, _24 * s,
			_31 * s, _32 * s, _33 * s, _34 * s,
			_41 * s, _42 * s, _43 * s, _44 * s);
	}
	Matrix operator/(float s) const
	{
		return Matrix(
			_11 / s, _12 / s, _13 / s, _14 / s,
			_21 / s, _22 / s, _23 / s, _24 / s,
			_31 / s, _32 / s, _33 / s, _34 / s,
			_41 / s, _42 / s, _43 / s, _44 / s);
	}
	Matrix operator+=(const Matrix& rhs)
	{
		_11 += rhs._11; _12 += rhs._12; _13 += rhs._13; _14 += rhs._14;
		_21 += rhs._21; _22 += rhs._22; _23 += rhs._23; _24 += rhs._24;
		_31 += rhs._31; _32 += rhs._32; _33 += rhs._33; _34 += rhs._34;
		_41 += rhs._41; _42 += rhs._42; _43 += rhs._43; _44 += rhs._44;
		return *this;
	}
};

//----------------------------------------------------------------------------------------------------

struct Rect
{
	float left, top, right, bottom;

	Rect() : left(0.0f), top(0.0f), right(1.0f), bottom(1.0f) {}
	Rect(float left, float top, float right, float bottom) : left(left), top(top), right(right), bottom(bottom) {}
};

//----------------------------------------------------------------------------------------------------

struct Circle
{
	Math::Vector2 center;
	float radius;

	Circle() : center(0.0f, 0.0f), radius(1.0f) {}
	Circle(const Math::Vector2& center, float radius) : center(center), radius(radius) {}
	Circle(float x, float y, float radius) : center(x, y), radius(radius) {}
};

//----------------------------------------------------------------------------------------------------

struct AABB
{
	Vector3 center;
	Vector3 extend;

	AABB() : center(0.0f, 0.0f, 0.0f), extend(0.0f, 0.0f, 0.0f) {}
	AABB(const Vector3& center, const Vector3& extend) : center(center), extend(extend) {}
};

//----------------------------------------------------------------------------------------------------

struct OBB
{
	Vector3 center;
	Vector3 extend;
	Quaternion orientation;

	OBB()
		: center(0.0f, 0.0f, 0.0f)
		, extend(1.0f, 1.0f, 1.0f)
		, orientation(0.0f, 0.0f, 0.0f, 1.0f)
	{}

	OBB(float x, float y, float z, float sx, float sy, float sz)
		: center(x, y, z)
		, extend(sx, sy, sz)
		, orientation(0.0f, 0.0f, 0.0f, 1.0f)
	{}

	OBB(float x, float y, float z, float sx, float sy, float sz, const Quaternion& orientation)
		: center(x, y, z)
		, extend(sx, sy, sz)
		, orientation(orientation)
	{}

	OBB(const Vector3& center, const Vector3& extend, const Quaternion& orientation)
		: center(center)
		, extend(extend)
		, orientation(orientation)
	{}
};

//----------------------------------------------------------------------------------------------------

struct Sphere
{
	Vector3 center;
	float radius;

	Sphere() : center(0.0f, 0.0f, 0.0f), radius(1.0f) {}
	Sphere(float x, float y, float z, float radius) : center(x, y, z), radius(radius) {}
	Sphere(const Vector3& center, float radius) : center(center), radius(radius) {}
};

//----------------------------------------------------------------------------------------------------

struct Ray
{
	Vector3 org;
	Vector3 dir;

	Ray() : org(0.0f, 0.0f, 0.0f), dir(0.0f, 0.0f, 1.0f) {}
	Ray(float x, float y, float z, float dx, float dy, float dz) : org(x, y, z), dir(dx, dy, dz) {}
	Ray(const Vector3& org, const Vector3& dir) : org(org), dir(dir) {}
};

//----------------------------------------------------------------------------------------------------

struct Plane
{
	Vector3 n;
	float d;

	Plane() : n(0.0f, 1.0f, 0.0f), d(0.0f) {}
	Plane(float a, float b, float c, float d) : n(a, b, c), d(d) {}
};

//----------------------------------------------------------------------------------------------------

extern const float kPi;
extern const float kTwoPi;
extern const float kPiByTwo;
extern const float kRootTwo;
extern const float kRootThree;
extern const float kDegToRad;
extern const float kRadToDeg;

//----------------------------------------------------------------------------------------------------

template <typename T> inline T Min(T a, T b) { return (a > b) ? b : a; }
template <typename T> inline T Max(T a, T b) { return (a < b) ? b : a; }
template <typename T> inline T Clamp(T value, T min, T max) { return Max(min, Min(max, value)); }

inline float Abs(float value) { return (value >= 0.0f) ? value : -value; }
inline float Sign(float value) { return (value >= 0.0f) ? 1.0f : -1.0f; }
inline float Sqr(float value) { return value * value; }
inline float Sqrt(float value) { return sqrtf(value); }

inline bool Compare(float a, float b, float epsilon = 1.175494351e-38F) { return Abs(a - b) <= epsilon; }
inline bool IsZero(float value) { return Compare(value, 0.0f); }
inline bool IsZero(const Vector3& v) { return IsZero(v.x) && IsZero(v.y) && IsZero(v.z); }

inline float MagnitudeSqr(const Vector3& v) { return (v.x * v.x) + (v.y * v.y) + (v.z * v.z); }
inline float Magnitude(const Vector3& v) { return Sqrt(MagnitudeSqr(v)); }
inline float MagnitudeXZSqr(const Vector3& v) { return (v.x * v.x) + (v.z * v.z); }
inline float MagnitudeXZ(const Vector3& v) { return Sqrt(MagnitudeXZSqr(v)); }
inline float Magnitude(const Quaternion& q) { return Sqrt((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w)); }

inline Vector3 Normalize(const Vector3& v) { return v / Magnitude(v); };
inline Quaternion Normalize(const Quaternion& q) { return q / Magnitude(q); }

inline float DistanceSqr(const Vector3& a, const Vector3& b) { return MagnitudeSqr(a - b); }
inline float Distance(const Vector3& a, const Vector3& b) { return Sqrt(DistanceSqr(a, b)); }
inline float DistanceXZSqr(const Vector3& a, const Vector3& b) { return MagnitudeXZSqr(a - b); }
inline float DistanceXZ(const Vector3& a, const Vector3& b) { return Sqrt(DistanceXZSqr(a, b)); }
inline float Dot(const Vector3& a, const Vector3& b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
inline Vector3 Cross(const Vector3& a, const Vector3& b) { return Vector3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)); }
inline Vector3 Project(const Vector3& v, const Vector3& n) { return n * (Dot(v, n) / Dot(n, n)); }

inline Vector3 GetTranslation(const Matrix& m) { return Vector3(m._41, m._42, m._43); }
inline Vector3 GetRight(const Matrix& m) { return Vector3(m._11, m._12, m._13); }
inline Vector3 GetUp(const Matrix& m) { return Vector3(m._21, m._22, m._23); }
inline Vector3 GetForward(const Matrix& m) { return Vector3(m._31, m._32, m._33); }
inline Vector3 GetPoint(const Ray& ray, float distance) { return ray.org + (ray.dir * distance); }
inline Vector3 Reflect(const Vector3& v, const Vector3& n);

inline Vector3 Lerp(const Vector3& v0, const Vector3& v1, float t) { return v0 + ((v1 - v0) * t); }
inline Quaternion Lerp(Quaternion q0, Quaternion q1, float t) { return q0 * (1.0f - t) + (q1 * t); }
inline Quaternion Conjugate(Quaternion q0) { return Quaternion(-q0.x, -q0.y, -q0.z, q0.w); }



inline float Determinant(const Matrix& m)
{
	float det = 0.0f;
	det = (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
	det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
	det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
	det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
	return det;
}

inline Matrix Adjoint(const Matrix& m)
{
	return Matrix
	(
		(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
		-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
		(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
		-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

		-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
		(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
		-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
		(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

		(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
		-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
		(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
		-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

		-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
		(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
		-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
		(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
	);
}

inline Matrix Inverse(const Matrix& m)
{
	const float determinant = Determinant(m);
	const float invDet = 1.0f / determinant;
	return Adjoint(m) * invDet;
}

inline Matrix Transpose(const Matrix& m)
{
	return Matrix
	(
		m._11, m._21, m._31, m._41,
		m._12, m._22, m._32, m._42,
		m._13, m._23, m._33, m._43,
		m._14, m._24, m._34, m._44
	);
}

inline Vector3 TransformCoord(const Vector3& v, const Matrix& m)
{
	return Vector3
	(
		v.x * m._11 + v.y * m._21 + v.z * m._31 + m._41,
		v.x * m._12 + v.y * m._22 + v.z * m._32 + m._42,
		v.x * m._13 + v.y * m._23 + v.z * m._33 + m._43
	);
}

inline Vector3 TransformNormal(const Vector3& v, const Matrix& m)
{
	return Vector3
	(
		v.x * m._11 + v.y * m._21 + v.z * m._31,
		v.x * m._12 + v.y * m._22 + v.z * m._32,
		v.x * m._13 + v.y * m._23 + v.z * m._33
	);
}

static Vector2 CalcUV(Vector3 input)
{
	Vector3 point = input;
	Normalize(point);
	float a, t, pi = 3.14159f;

	a = acosf(point[2]);
	float temp = sin(a);

	if (abs(temp) < 0.001f)
	{
		t = 0.0f;
	}
	else
	{
		float temp2 = point[0] / temp;

		temp2 = Math::Min(Math::Max(temp2, -1.0f), 1.0f);
		t = acosf(temp2);

		if (point[1] < 0.0f)
		{
			t = 2.0f * pi - t;
		}
	}

	float v = 1.0f - a / pi;
	float u = t / (2.0f * pi);

	return Vector2(u, v);
}

inline Quaternion QuaternionLookRotation(const Vector3& forward, const Vector3& up);
inline Quaternion RotationAxis(const Vector3& axis, float rad);
inline Matrix ToMatrix(const Quaternion& q);

inline Quaternion Slerp(Quaternion q0, Quaternion q1, float t);
//
//
//bool Intersect(const Ray& ray, const Vector3& a, const Vector3& b, const Vector3& c, float& distance);
//bool Intersect(const Ray& ray, const Plane& plane, float& distance);
//bool Intersect(const Ray& ray, const AABB& aabb, float& distEntry, float& distExit);
//bool Intersect(const Ray& ray, const OBB& obb, float& distEntry, float& distExit);
//bool Intersect(const Vector3& point, const AABB& aabb);
//bool Intersect(const Vector3& point, const OBB& obb);
//
//void GetCorners(const OBB& obb, std::vector<Vector3>& corners);
//bool GetContactPoint(const Ray& ray, const OBB& obb, Vector3& point, Vector3& normal);
//
//Vector3 GetClosestPoint(const Ray& ray, const Vector3& point);
//
//Vector3 Mean(const Vector3* v, uint32_t count);

} // namespace Math

#endif // #ifndef INCLUDED_ENGINE_MATH_H
