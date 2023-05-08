#ifndef INCLUDED_GRAPHICS_KEYFRAME_H
#define INCLUDED_GRAPHICS_KEYFRAME_H

#include <Math\Inc\MathHeaders.h>

namespace Graphics {

struct Keyframe
{
	Math::Vector3 translation;
	Math::Quaternion rotation;
	Math::Vector3 scale;
	float time;

	Keyframe()
		: translation(Math::Vector3::Zero())
		, rotation(Math::Quaternion::Identity())
		, scale(Math::Vector3::One())
		, time(0.0f)
	{}

	Math::Matrix GetTransform() const
	{
		return Math::Matrix::Scaling(scale) * Math::ToMatrix(rotation) * Math::Matrix::Translation(translation);
	}


};

typedef std::vector<Keyframe> Keyframes;
}

#endif // INCLUDED_GRAPHICS_KEYFRAME_H