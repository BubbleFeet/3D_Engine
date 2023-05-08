#ifndef INCLUDED_PHYSICS_PHYSICSWORLD_H
#define INCLUDED_PHYSICS_PHYSICSWORLD_H

#include "Settings.h"

namespace Physics {

class Particle;
class Constraint;

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void Setup(const Settings& settings);

	void Update(float deltaTime);

	void AddParticle(Particle* p);
	void AddPlane(Math::Plane p);

	void ClearDynamic();
	void ClearAll();

	void DebugDraw();

private:

	void AccumulateForces();
	void Integrate();
	void SatisfyConstraints();

	typedef std::vector<Particle*> Particles;
	typedef std::vector<Constraint*> Constraints;
	typedef std::vector<Math::Plane> Planes;

	Settings mSettings;
	Particles mParticles;
	Constraints mConstraints;
	Planes mPlanes;

	float mTimer;
};

} // namespace Physics

#endif // !INCLUDED_PHYSICS_PHYSICSWORLD_H
