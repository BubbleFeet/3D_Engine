#ifndef INCLUDED_PHYSICS_CONSTRAINT_H
#define INCLUDED_PHYSICS_CONSTRAINT_H

namespace Physics {

class Particle;

class Constraint
{
public:
	virtual ~Constraint() {}

	virtual void Apply() const = 0;
	virtual void DebugDraw() const {}
};

class Fixed : public Constraint
{
public:
	Fixed(Particle* p);
	Fixed(Particle* p, const Math::Vector3& location);

	void Apply() const override;
	void DebugDraw() const override;

protected:
	Particle* mParticle;
	Math::Vector3 mLocation;
};

class Spring : public Constraint
{
public:
	Spring(Particle* a, Particle* b, float restLength = -1.0f);

	void Apply() const override;
	void DebugDraw() const override;

protected:
	Particle* mParticleA;
	Particle* mParticleB;
	float mRestLength;
};
}
#endif // !INCLUDED_PHYSICS_CONSTRAINT_H
