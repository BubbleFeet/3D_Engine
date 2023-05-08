#include "Precompiled.h"

#include "Camera.h"

using namespace Graphics;

Camera::Camera()
	: mPosition(0.0f, 0.0f, 0.0f)
	, mDirection(0.0f, 0.0f, 1.0f)
	, mNearPlane(0.01f)
	, mFarPlane(10000.0f)
	, mFOV(60.0f * Math::kDegToRad)
	, mAspect(16.0f / 9.0f)
{
}

Camera::~Camera()
{
}

void Camera::Setup(float nearPlane, float farPlane, float fov, float aspect)
{
	mNearPlane = nearPlane;
	mFarPlane = farPlane;
	mFOV = fov;
	mAspect = aspect;
}

void Camera::Walk(float distance)
{
	mPosition += mDirection * distance;
}

void Camera::Strafe(float distance)
{
	const Math::Vector3 right = Math::Normalize(Math::Cross(Math::Vector3::YAxis(), mDirection));
	mPosition += right * distance;
}

void Camera::Rise(float distance)
{
	mPosition += Math::Vector3::YAxis() * distance;
}

void Camera::Yaw(float degree)
{
	Math::Matrix matRotate = Math::Matrix::RotationY(degree * Math::kDegToRad);
	mDirection = Math::TransformNormal(mDirection, matRotate);
}

void Camera::Pitch(float degree)
{
	const Math::Vector3 right = Math::Normalize(Math::Cross(Math::Vector3::YAxis(), mDirection));
	const Math::Matrix matRotate = Math::Matrix::RotationAxis(right, degree * Math::kDegToRad);
	const Math::Vector3 newLook = Math::TransformNormal(mDirection, matRotate);
	const float dot = Math::Dot(newLook, Math::Vector3::YAxis());

	// Avoid looking straight up or down
	if (Math::Abs(dot) < 0.995f)
	{
		mDirection = newLook;
	}
}

void Camera::SetFOV(float fov)
{
	const float kMinFOV = 10.0f * Math::kDegToRad;
	const float kMaxFOV = 150.0f * Math::kDegToRad;
	mFOV = Math::Clamp(fov, kMinFOV, kMaxFOV);
}

void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

Math::Matrix Camera::GetViewMatrix() const
{
	Math::Vector3 look = Math::Normalize(mDirection);
	Math::Vector3 right = Math::Normalize(Math::Cross(Math::Vector3::YAxis(), look));
	Math::Vector3 up = Math::Normalize(Math::Cross(look, right));
	float x = Math::Dot(-mPosition, right);
	float y = Math::Dot(-mPosition, up);
	float z = Math::Dot(-mPosition, look);
	return Math::Matrix
	(
		right.x, up.x, look.x, 0.0f,
		right.y, up.y, look.y, 0.0f,
		right.z, up.z, look.z, 0.0f,
		x,		 y,    z,      1.0f
	);
}

Math::Matrix Camera::GetProjectionMatrix() const
{
	const double h = 1.0 / tan(mFOV * 0.5f);
	const double w = h / mAspect;
	const float f = mFarPlane;
	const float n = mNearPlane;
	const double d = f / (f - n);
	return Math::Matrix
	(
		w, 0.0f, 0.0f, 0.0f,
		0.0f, h, 0.0f, 0.0f,
		0.0f, 0.0f, d, 1.0f,
		0.0f, 0.0f, -n * d, 0.0f
	);
}