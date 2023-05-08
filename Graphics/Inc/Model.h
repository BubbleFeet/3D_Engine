//====================================================================================================
// Filename:	Model.h
// Created by:	Peter Chan
//====================================================================================================

#ifndef INCLUDED_GRAPHICS_MODEL_H
#define INCLUDED_GRAPHICS_MODEL_H

#include "Texture.h"
#include "Vertex.h"

namespace Graphics {

struct Bone;
class AnimationClip;
class Mesh;
class MeshBuffer;
class Texture;

class Model
{
public:
	Model();
	~Model();
	
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

	void Terminate();

	Bone* FindBone(const char* name);
	AnimationClip* FindAnimationClip(const char* name);

public:
	struct Part
	{
		Mesh* mesh;
		MeshBuffer* meshBuffer;
		Texture texture;
	};

	std::vector<Part> mParts;
	
	Bone* mRoot;
	std::vector<Bone*> mBones;
	std::vector<AnimationClip*> mAnimations;
};

} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_MODEL_H