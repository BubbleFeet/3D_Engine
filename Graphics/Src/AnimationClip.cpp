#include "Precompiled.h"

#include "AnimationClip.h"

#include "Bone.h"
#include "BoneAnimation.h"

using namespace Graphics;

AnimationClip::AnimationClip()
	: mDuration(0.0f)
	, mTicksPerSecond(0.0f)
	, mKeyframeCount(0)
{
}

AnimationClip::~AnimationClip()
{
	for (auto animation : boneAnimations)
	{
		SafeDelete(animation);
	}
	boneAnimations.clear();
}

void AnimationClip::GetTransform(float time, Bone* bone, Math::Matrix& transform) const
{
	BoneAnimation* boneAnim = boneAnimations[bone->mIndex];
	if (boneAnim != nullptr)
	{
		transform = boneAnim->GetTransform(time);
	}
	else
	{
		transform = Math::Matrix::Identity();
	}
}