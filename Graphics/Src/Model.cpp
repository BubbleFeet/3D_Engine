#include "Precompiled.h"
#include "Model.h"

#include "AnimationClip.h"
#include "Bone.h"
#include "BoneAnimation.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "Vertex.h"

using namespace Graphics;

Model::Model()
	: mRoot(nullptr)
{
}

Model::~Model()
{
	ASSERT(mParts.empty(), "[Model] Mesh data not freed.");
	ASSERT(mBones.empty(), "[Model] Bones not freed.");
	ASSERT(mAnimations.empty(), "[Model] Animations not freed.");
}

void Model::Terminate()
{
	for (auto& part : mParts)
	{
		part.mesh->Terminate();
		part.meshBuffer->Terminate();

		SafeDelete(part.mesh);
		SafeDelete(part.meshBuffer);
		part.texture.Terminate();
	}
	mParts.clear();

	for (auto bone : mBones)
	{
		SafeDelete(bone);
	}
	mBones.clear();

	for (auto animation : mAnimations)
	{
		SafeDelete(animation);
	}
	mAnimations.clear();
}

Bone* Model::FindBone(const char* name)
{
	for (auto bone : mBones)
	{
		if (strcmp(bone->name.c_str(), name) == 0)
		{
			return bone;
		}
	}
	return nullptr;
}

AnimationClip* Model::FindAnimationClip(const char* name)
{
	for (auto animation : mAnimations)
	{
		if (strcmp(animation->mName.c_str(), name) == 0)
		{
			return animation;
		}
	}
	return nullptr;
}