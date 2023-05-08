#ifndef INCLUDED_GRAPHICS_MESHBUILDER_H
#define INCLUDED_GRAPHICS_MESHBUILDER_H

namespace Graphics {

struct Vertex;
class Mesh;
class Heightmap;

class MeshBuilder
{
public:
	// Functions for building a custom mesh
	static void StartMesh();
	static uint32_t AddVertexToMesh(const Vertex& vertex);
	static void AddFaceToMesh(uint32_t a, uint32_t b, uint32_t c);
	static void FinalizeMesh(Mesh& mesh);

	static void GenerateMesh(Mesh& mesh, const Vertex* vertexData, uint32_t numVertices, const uint32_t* indexData, uint32_t numIndices);

	static void CreatePlane(Mesh& mesh, uint32_t rows, uint32_t columns, float scale);
	static void CreateCube(Mesh& mesh);
	static void CreateSkybox(Mesh& mesh);
	static void CreateSphere(Mesh& mesh, uint32_t slices, uint32_t rings);
	static void CreateTerrain(Mesh& mesh, const Heightmap& heightmap, uint32_t width, uint32_t length, float maxHeight);
};

} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_MESHBUILDER_H