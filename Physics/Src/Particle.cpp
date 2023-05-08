#include "Precompiled.h"
#include "Physics.h"

using namespace Physics;

Particle::Particle()
	: mPosition(0.0f, 0.0f, 0.0f)
	, mPreviousPosition(0.0f, 0.0f, 0.0f)
	, mAcceleration(0.0f, 0.0f, 0.0f)
	, mInvMass(1.0f)
	, mRadius(0.01f)
{}

Particle::Particle(const Math::Vector3& pos, float radius, float invMass)
	: mPosition(pos)
	, mPreviousPosition(pos)
	, mAcceleration(0.0f, 0.0f, 0.0f)
	, mInvMass(invMass)
	, mRadius(radius)
{
}


void Particle::DebugDraw()
{
	// Draw In Render
	// Graphics::SimpleDraw::AddSphere(mPosition, mRadius, Math::Vector4::Cyan(), 4, 2);
}

void Particle::SetPosition(const Math::Vector3& position)
{
	// mPreviousPosition = mPosition = no motion
	mPosition = position;
	mPreviousPosition = position;
}

void Particle::SetVelocity(const Math::Vector3& velocity)
{
	mPreviousPosition = mPosition - velocity;
}