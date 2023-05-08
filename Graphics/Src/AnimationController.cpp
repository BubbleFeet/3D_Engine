#include "Precompiled.h"

#include "AnimationController.h"
#include "AnimationClip.h"
#include "Model.h"
#include "Bone.h"

using namespace Graphics;

AnimationController::AnimationController()
	: mModel{ nullptr }
	, mCurrentAnimationClip{ nullptr }
	, mCurrentTime{ 0.0f }
	, mCurrentFrame{ 0 }
	, mIsPlaying{ false }
	, mIsLooping{ false }
{
}

AnimationController::~AnimationController()
{
}


void AnimationController::Initialize(Model& model)
{
	mModel = &model;
	mToRootTransforms.resize(model.mBones.size());
	mFinalTransforms.resize(model.mBones.size());
}

void AnimationController::StartClip(const char* animationClipName, bool loop)
{
	mCurrentAnimationClip = mModel->FindAnimationClip(animationClipName);
	ASSERT(mCurrentAnimationClip != nullptr, "[AnimationController] Failed to find animation '%s'", animationClipName);

	mCurrentTime = 0;
	mCurrentFrame = 0;
	mIsPlaying;
	mIsLooping = loop;

	//HACK: force root transform to identity
	//mModel->mRoot->transform = Math::Matrix::Identity();

	mInverseRootTransform = Math::Inverse(mModel->mRoot->mTransform);
	GetBindPose(mModel->mRoot);
}


void AnimationController::Update(float deltaTime)
{
	if (!mIsPlaying)
	{
		return;
	}

	mCurrentTime += deltaTime * mCurrentAnimationClip->mTicksPerSecond;
	if (mCurrentTime >= mCurrentAnimationClip->mDuration)
	{
		if (mIsLooping)
		{
			mCurrentTime = 0.0f;
		}
		else
		{
			mIsPlaying = false;
		}
	}

	if (mIsPlaying)
	{
		GetPose(mCurrentTime, mModel->mRoot);
	}
}

void AnimationController::Pause()
{
	mIsPlaying = false;
}

void AnimationController::Play()
{
	mIsPlaying = true;
}

void AnimationController::Stop()
{
	mIsPlaying = false;
	mCurrentTime = 0.0f;
}



void AnimationController::GetBindPose(Bone* bone)
{
	Math::Matrix toParentTransform = bone->mTransform;
	Math::Matrix toRootTransform = toParentTransform;
	if (bone->mParent != nullptr)
	{
		toRootTransform = toParentTransform * mToRootTransforms[bone->mParent->mIndex];
	}

	mToRootTransforms[bone->mIndex] = toRootTransform;
	mFinalTransforms[bone->mIndex] = bone->mOffsetTransform * toRootTransform * mInverseRootTransform;

	for (auto child : bone->mChildren)
	{
		GetBindPose(child);
	}
}

void AnimationController::GetPose(float time, Bone* bone)
{
	Math::Matrix toParentTransform;
	mCurrentAnimationClip->GetTransform(time, bone, toParentTransform);
	Math::Matrix toRootTransform = toParentTransform;

	if (bone->mParent != nullptr)
	{
		toRootTransform = toParentTransform * mToRootTransforms[bone->mParent->mIndex];
	}

	mToRootTransforms[bone->mIndex] = toRootTransform;
	mFinalTransforms[bone->mIndex] = bone->mOffsetTransform * toRootTransform * mInverseRootTransform;

	for (auto child : bone->mChildren)
	{
		GetPose(time, child);
	}
}
