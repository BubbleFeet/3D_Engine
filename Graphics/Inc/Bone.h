#ifndef INCLUDED_GRAPHICS_BONE_H
#define INCLUDED_GRAPHICS_BONE_H

namespace Graphics
{
	struct Bone;
	typedef std::vector<Bone*> Bones;

	struct Bone
	{
		Bone()
			: mParent(nullptr)
			, parentIndex(-1)
			, mIndex(0)
		{}

		~Bone()
		{}

		std::string name;

		Bone* mParent;
		Bones mChildren;

		int parentIndex;
		std::vector<uint32_t> childrenIndex;

		Math::Matrix mTransform;
		Math::Matrix mOffsetTransform;

		uint32_t mIndex;
	};


} // namespace Graphics

#endif // INCLUDED_GRAPHICS_BONE_H