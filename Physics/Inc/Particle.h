#ifndef INCLUDED_PHYSICS_PARTICLE_H
#define INCLUDED_PHYSICS_PARTICLE_H

namespace Physics {

class Particle
{
	friend class PhysicsWorld;
	friend class Fixed;
	friend class Spring;
public:
	Particle();
	Particle(const Math::Vector3& position, float radius = 0.01f, float invMass = 1.0f);

	void DebugDraw();

	void SetPosition(const Math::Vector3& position);
	void SetVelocity(const Math::Vector3& position);

private:
	Math::Vector3 mPosition;
	Math::Vector3 mPreviousPosition;
	Math::Vector3 mAcceleration;

	float mRadius;
	float mInvMass;
	float mBounce;
	bool  mSleep;
};

} // namespace Physics

#endif // !INCLUDED_PHYSICS_PARTICLE_H
