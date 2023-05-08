#ifndef INCLUDED_PHYSICS_SETTINGS_H
#define INCLUDED_PHYSICS_SETTINGS_H

namespace Physics {

	struct Settings
	{
		Settings()
			: mGravity(0.0f, -9.8f, 0.0f)
			, mTimeStep(1.0f / 60.0f)
			, mDrag(0.0f)
			, mIterations(1)
		{}

		Math::Vector3 mGravity;
		float mTimeStep;
		float mDrag;
		uint32_t mIterations;
	};

} // namespace Physics

#endif // !INCLUDED_PHYSICS_SETTINGS_H
