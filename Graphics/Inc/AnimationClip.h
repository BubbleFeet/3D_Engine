#ifndef INCLUDED_GRAPHICS_ANIMATIONCLIP_H
#define INCLUDED_GRAPHICS_ANIMATIONCLIP_H

#include "BoneAnimation.h"

namespace Graphics
{
struct Bone;

class AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();

	void GetTransform(float time, Bone* bone, Math::Matrix& transform) const;

	BoneAnimations boneAnimations;
	std::string mName;
	float mDuration;
	float mTicksPerSecond;
	uint32_t mKeyframeCount;
private:
};

} // namespace Graphics

#endif //INCLUDED_GRAPHICS_ANIMATIONCLIP_H
