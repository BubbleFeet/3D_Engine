#ifndef INCLUDED_GRAPHICS_CAMERA_H
#define INCLUDED_GRAPHICS_CAMERA_H


namespace Graphics {

class Camera
{
public:
	Camera();
	~Camera();

	void Setup(float nearPlane, float farPlane, float fov, float aspect);

	void Walk(float distance);
	void Strafe(float distance);
	void Rise(float distance);

	void Yaw(float degree);
	void Pitch(float degree);

	void SetFOV(float FOV);
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);

	void SetPosition(const Math::Vector3& position)		{ mPosition = position; }
	void SetDirection(const Math::Vector3& direction)	{ mDirection = direction; }
	void SetLookAt(const Math::Vector3& target)			{ mDirection = target - mPosition; }

	const Math::Vector3& GetPosition() const { return mPosition; }
	const Math::Vector3& GetDirection() const { return mDirection; }

	Math::Matrix GetViewMatrix() const;
	Math::Matrix GetProjectionMatrix() const;

private:
	Math::Vector3 mPosition;
	Math::Vector3 mDirection;

	float mNearPlane, mFarPlane, mFOV, mAspect;
};
}

#endif INCLUDED_GRAPHICS_CAMERA_H