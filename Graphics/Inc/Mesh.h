#ifndef INCLUDED_GRAPHICS_MESH_H
#define INCLUDED_GRAPHICS_MESH_H

#include "Vertex.h"

namespace Graphics {

class Mesh
{
	//NONCOPYABLE(Mesh);

	friend class MeshBuilder;

	Vertex* mVertices;
	uint32_t* mIndices;

	uint32_t mNumVertices;
	uint32_t mNumIndices;

public:

	Mesh()
		: mVertices(nullptr)
		, mIndices(nullptr)
		, mNumVertices(0)
		, mNumIndices(0)
	{}

	~Mesh()
	{
		ASSERT(mVertices == nullptr, "Vertices were not terminated.");
		ASSERT(mIndices == nullptr, "Indices were not terminated.");
	}

	const Vertex* GetVertices() const { return mVertices; }
	const uint32_t* GetIndices() const { return mIndices; }
	const uint32_t GetNumVertices() const { return mNumVertices; }
	const uint32_t GetNumIndices() const { return mNumIndices; }
	Vertex& GetVertex(uint32_t index) { return mVertices[index]; }
	uint32_t& GetIndex(uint32_t index) { return mIndices[index]; }

	void Initialize(uint32_t numVertices, uint32_t numIndices);
	void Initialize(Vertex* vertices, uint32_t numVertices, uint32_t* indices, uint32_t numIndices);
	void Terminate();

};
} // namespace Graphics

#endif // INCLUDED_GRAPHICS_MESH_H