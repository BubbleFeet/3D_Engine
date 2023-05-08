#pragma once
#include "BoneAnimation.h"


namespace Graphics
{
struct Bone;
class Model;
class AnimationClip;

using BoneTransforms = std::vector<Math::Matrix>;

class AnimationController
{
	Model* mModel;
	AnimationClip* mCurrentAnimationClip;
	BoneTransforms mToRootTransforms;
	BoneTransforms mFinalTransforms;
	Math::Matrix mInverseRootTransform;

	float mCurrentTime;
	uint32_t mCurrentFrame;
	bool mIsPlaying;
	bool mIsLooping;
public:
	AnimationController();
	~AnimationController();

	//=====================================================
	void StartClip(const char* animationClipName, bool loop);
	void Pause();
	void Play();
	void Stop();
	//=====================================================
	void Update(float deltaTime);
	void Initialize(Model& model);
	

	const BoneTransforms& ToRootTransforms() const { return mToRootTransforms; }
	const BoneTransforms& ToLocalTransforms() const { return mFinalTransforms; }
	const Math::Matrix& InverseRootTransform() const { return mInverseRootTransform; }
private:
	void GetBindPose(Bone* bone);
	void GetPose(float time, Bone* bone);
};

}//namespace Graphics