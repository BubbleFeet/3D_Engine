#include "Precompiled.h"
#include "Constraint.h"

#include "Graphics\Inc\SimpleDraw.h"
#include "Particle.h"

using namespace Physics;

Fixed::Fixed(Particle* p)
	: mParticle(p)
	, mLocation(p->mPosition)
{
}

Fixed::Fixed(Particle* p, const Math::Vector3& position)
	: mParticle(p)
	, mLocation(position)
{
}

void Fixed::Apply() const
{
	mParticle->SetPosition(mLocation);
}

void Fixed::DebugDraw() const
{
	Graphics::SimpleDraw::AddAABB(mLocation, 0.1f, Math::Vector4::Cyan());
}

Spring::Spring(Particle* a, Particle* b, float restLength)
	: mParticleA(a)
	, mParticleB(b)
	, mRestLength(restLength)
{
	if (mRestLength <= 0.0f)
	{
		mRestLength = Math::Distance(a->mPosition, b->mPosition);
	}
}

void Spring::Apply() const
{
	Math::Vector3 delta = mParticleB->mPosition - mParticleA->mPosition;
	float dist = Math::Magnitude(delta);
	float diff = (dist - mRestLength) / (dist * (mParticleA->mInvMass + mParticleB->mInvMass));
	mParticleA->mPosition += delta * diff * mParticleA->mInvMass;
	mParticleB->mPosition -= delta * diff * mParticleB->mInvMass;
}

void Spring::DebugDraw() const
{
	Graphics::SimpleDraw::AddLine(mParticleA->mPosition, mParticleB->mPosition, Math::Vector4::Green());
}