#include "Precompiled.h"
#include "Mesh.h"
#include "Vertex.h"
using namespace Graphics;


void Mesh::Initialize(Vertex* vertices, uint32_t numVertices, uint32_t* indices, uint32_t numIndices)
{
	ASSERT(mVertices == nullptr, "Vertices already instantiated.");
	ASSERT(mIndices == nullptr, "Indices already instantiated.");

	mVertices = vertices;
	mNumVertices = numVertices;
	mIndices = indices;
	mNumIndices = numIndices;
}

void Mesh::Initialize(uint32_t numVertices, uint32_t numIndices)
{
	ASSERT(mVertices == nullptr, "[Mesh] Already contain vertex data.");
	ASSERT(mIndices == nullptr, "[Mesh] Already contain index data.");
	ASSERT(numVertices != 0, "[Mesh] Invalid vertex count.");
	ASSERT(numIndices != 0, "[Mesh] Invalid index count.");

	mVertices = new Vertex[numVertices];
	mIndices = new uint32_t[numIndices];
	mNumVertices = numVertices;
	mNumIndices = numIndices;
}

void Mesh::Terminate()
{
	ASSERT(mVertices != nullptr, "Vertices already terminated.");
	ASSERT(mIndices != nullptr, "Indices already terminated.");

	SafeDeleteArray(mVertices);
	SafeDeleteArray(mIndices);
	mNumVertices = 0;
	mNumIndices = 0;
}
