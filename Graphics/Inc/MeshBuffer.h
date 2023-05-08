#ifndef INCLUDED_GRAPHICS_MESHBUFFER_H
#define INCLUDED_GRAPHICS_MESHBUFFER_H

#include "Mesh.h"

namespace Graphics {

	class MeshBuffer
	{
	public:
		MeshBuffer();
		~MeshBuffer();

		void Initialize(const Mesh& mesh);
		void Initialize(const void* vertexData, uint32_t numVertices, const uint32_t* indexData, uint32_t numIndices, bool dynamic = false);
		void Terminate();

		void Render();

	private:
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;

		uint32_t mVertexCount;
		uint32_t mIndexCount;
	};

} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_MESHBUFFER_H