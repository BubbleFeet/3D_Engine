#pragma once

namespace Graphics {

	struct Vertex
	{
		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector3 tangent;
		Math::Vector4 color;
		Math::Vector2 texcoord;
		
		int mBoneIndex[4];
		float mBoneWeight[4];

		Vertex()
			: position(0.0f, 0.0f, 0.0f)
			, normal(0.0f, 0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f)
			, texcoord(0.0f, 0.0f)
		{}

		Vertex(Math::Vector3 pos, Math::Vector3 norm, Math::Vector4 col, Math::Vector2 tex)
			: position(pos)
			, normal(norm)
			, color(col)
			, texcoord(tex)
		{}

		~Vertex() {}

		Math::Vector2 getUV() { return texcoord; }
		Math::Vector3 getPosition() { return position; }
		Math::Vector4 getColor() { return color; }
		Math::Vector3 getNorm() { return normal; }
	};

}