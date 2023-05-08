#include "Constraint.h"
#include "Precompiled.h"
#include "PhysicsWorld.h"
#include "Particle.h"
#include "Constraint.h"

using namespace Physics;

PhysicsWorld::PhysicsWorld()
	: mTimer(0.0f)
{
}

PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::Setup(const Settings& settings)
{
	mSettings = settings;
}

void PhysicsWorld::Update(float deltaTime)
{
	mTimer += deltaTime;
	while (mTimer > mSettings.mTimeStep)
	{
		AccumulateForces();
		Integrate();
		SatisfyConstraints();

		mTimer -= mSettings.mTimeStep;
	}
}

void PhysicsWorld::AddParticle(Particle* p)
{
	mParticles.push_back(p);
}

void PhysicsWorld::AddPlane(const Math::Plane p)
{
	mPlanes.push_back(p);
}

void PhysicsWorld::ClearDynamic()
{
	SafeDeleteVector(mParticles);
	SafeDeleteVector(mConstraints);
}

void PhysicsWorld::ClearAll()
{
	ClearDynamic();
	mPlanes.clear();
}

void PhysicsWorld::DebugDraw()
{
	for (const auto p : mParticles)
	{
		p->DebugDraw();
	}

	for (const auto c : mConstraints)
	{
		c->DebugDraw();
	}
}

void PhysicsWorld::AccumulateForces()
{
	for (auto p : mParticles)
	{
		p->mAcceleration = mSettings.mGravity;
	}
}

void PhysicsWorld::Integrate()
{
	const float kTimeStepSqr = Math::Sqr(mSettings.mTimeStep);
	for (auto p : mParticles)
	{
		Math::Vector3 displacement = p->mPosition - p->mPreviousPosition + (p->mAcceleration * kTimeStepSqr);
		p->mPreviousPosition = p->mPosition;
		p->mPosition = p->mPosition + displacement;
	}
}

void PhysicsWorld::SatisfyConstraints() 
{
	for (uint32_t n = 0; n < mSettings.mIterations; ++n)
	{
		for (auto c : mConstraints)
		{
			c->Apply();
		}

		for (const auto& plane : mPlanes)
		{
			for (auto p : mParticles)
			{
				float dist = Math::Dot(p->mPosition, plane.n) - plane.d;
				if (dist >= 0.0f)
				{
					continue;
				}

				Math::Vector3 pointOnPlane = p->mPosition - (plane.n * dist);
				p->mPosition = pointOnPlane + (plane.n * mSettings.mTimeStep);

				Math::Vector3 vel = p->mPosition - p->mPreviousPosition;
				p->mPreviousPosition = p->mPosition - Math::Reflect(vel, plane.n);
			}
		}
	}
}