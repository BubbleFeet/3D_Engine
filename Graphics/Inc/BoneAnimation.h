#ifndef INCLUDED_GRAPHICS_BONEANIMATION_H
#define INCLUDED_GRAPHICS_BONEANIMATION_H

#include "Keyframe.h"
namespace Graphics {

struct Bone;

class BoneAnimation
{
public:
	BoneAnimation();
	~BoneAnimation();

	Math::Matrix GetTransform(float time) const;

	float GetEndTime() const;
	uint32_t FindKeyframeIndex(float time) const;

	Keyframes mKeyframes;
	Bone* mBone;
	uint32_t mBoneIndex;
};

typedef std::vector<BoneAnimation*> BoneAnimations;
typedef std::vector<Math::Matrix> BoneTransforms;
}

#endif // INCLUDED_GRAPHICS_BONEANIMATION_H