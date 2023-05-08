#include "Precompiled.h"

#include "BoneAnimation.h"
using namespace Graphics;

BoneAnimation::BoneAnimation()
	: mBone(nullptr)
	, mBoneIndex(0)
{}

BoneAnimation::~BoneAnimation()
{
}

Math::Matrix BoneAnimation::GetTransform(float time) const
{
	return Math::Matrix();
}

float BoneAnimation::GetEndTime() const
{
	return mKeyframes.empty() ? 0.0f : mKeyframes.back().time;
}
uint32_t BoneAnimation::FindKeyframeIndex(float time) const
{
	uint32_t index = 0;

	for (uint32_t i = 0; i < mKeyframes.size(); ++i)
	{
		if (mKeyframes[i].time < time)
		{
			index = i;
		}
	}

	return index;
}