#include "Precompiled.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Heightmap.h"

using namespace Graphics;

namespace 
{
	std::vector<Vertex> sVertices;
	std::vector<uint32_t> sIndices;
}

void MeshBuilder::StartMesh()
{
	sVertices.clear();
	sIndices.clear();
}

uint32_t MeshBuilder::AddVertexToMesh(const Vertex& vertex)
{
	sVertices.push_back(vertex);
	return sVertices.size() - 1;
}

void MeshBuilder::AddFaceToMesh(uint32_t a, uint32_t b, uint32_t c)
{
	sIndices.push_back(a);
	sIndices.push_back(b);
	sIndices.push_back(c);
}

void MeshBuilder::FinalizeMesh(Mesh& mesh)
{
	GenerateMesh(mesh, sVertices.data(), sVertices.size(), sIndices.data(), sIndices.size());
}

void MeshBuilder::GenerateMesh(Mesh& mesh, const Vertex* vertexData, uint32_t numVertices, const uint32_t* indexData, uint32_t numIndices)
{
	// Free any existing data
	mesh.Terminate();

	// Allocate memory
	Vertex* vertices = new Vertex[numVertices];
	uint32_t* indices = new uint32_t[numIndices];

	// Copy data
	memcpy(vertices, vertexData, numVertices * sizeof(Vertex));
	memcpy(indices, indexData, numIndices * sizeof(uint32_t));

	// Bind new data
	mesh.Initialize(vertices, numVertices, indices, numIndices);
}

// =========================== Mesh Builders ================================

void MeshBuilder::CreatePlane(Mesh& mesh, uint32_t rows, uint32_t columns, float scale)
{
	ASSERT(rows > 1 && columns > 1, "[MeshBuilder] Invalid parameters.");

	const uint32_t kNumVertices = rows * columns;
	const uint32_t kNumIndices = (rows - 1) * (columns - 1) * 6;

	mesh.Initialize(kNumVertices, kNumIndices);

	const float posOffsetX = scale * -0.5f;
	const float posOffsetZ = scale * -0.5f;
	const float xStep = scale / (columns - 1);
	const float zStep = scale / (rows - 1);
	const float uStep = 1.0f / (columns - 1);
	const float vStep = 1.0f / (rows - 1);

	for (uint32_t z = 0; z < rows; ++z)
	{
		for (uint32_t x = 0; x < columns; ++x)
		{
			const uint32_t index = x + (z * columns);
			mesh.GetVertex(index).position = Math::Vector3(posOffsetX + (x * xStep), 0.0f, posOffsetZ + (z * zStep));
			mesh.GetVertex(index).normal = Math::Vector3::YAxis();
			mesh.GetVertex(index).tangent = Math::Vector3::XAxis();
			mesh.GetVertex(index).color = Math::Vector4::White();
			mesh.GetVertex(index).texcoord = Math::Vector2(x * uStep, z * vStep);
		}
	}

	uint32_t index = 0;
	for (uint32_t z = 0; z < rows - 1; ++z)
	{
		for (uint32_t x = 0; x < columns - 1; ++x)
		{
			mesh.GetIndex(index++) = (x + 0) + ((z + 0) * columns);
			mesh.GetIndex(index++) = (x + 0) + ((z + 1) * columns);
			mesh.GetIndex(index++) = (x + 1) + ((z + 1) * columns);

			mesh.GetIndex(index++) = (x + 0) + ((z + 0) * columns);
			mesh.GetIndex(index++) = (x + 1) + ((z + 1) * columns);
			mesh.GetIndex(index++) = (x + 1) + ((z + 0) * columns);
		}
	}
}

void MeshBuilder::CreateCube(Mesh& mesh)
{
	const uint32_t kNumVertices = 24;
	const uint32_t kNumIndices = 36;

	mesh.Initialize(kNumVertices, kNumIndices);

	// Pos X
	mesh.GetVertex(0).position = Math::Vector3(1.0f, -1.0f, -1.0f);
	mesh.GetVertex(1).position = Math::Vector3(1.0f, 1.0f, -1.0f);
	mesh.GetVertex(2).position = Math::Vector3(1.0f, 1.0f, 1.0f);
	mesh.GetVertex(3).position = Math::Vector3(1.0f, -1.0f, 1.0f);

	// Neg X
	mesh.GetVertex(4).position = Math::Vector3(-1.0f, -1.0f, 1.0f);
	mesh.GetVertex(5).position = Math::Vector3(-1.0f, 1.0f, 1.0f);
	mesh.GetVertex(6).position = Math::Vector3(-1.0f, 1.0f, -1.0f);
	mesh.GetVertex(7).position = Math::Vector3(-1.0f, -1.0f, -1.0f);

	// Pos Y
	mesh.GetVertex(8).position = Math::Vector3(-1.0f, 1.0f, -1.0f);
	mesh.GetVertex(9).position = Math::Vector3(-1.0f, 1.0f, 1.0f);
	mesh.GetVertex(10).position = Math::Vector3(1.0f, 1.0f, 1.0f);
	mesh.GetVertex(11).position = Math::Vector3(1.0f, 1.0f, -1.0f);

	// Neg Y
	mesh.GetVertex(12).position = Math::Vector3(-1.0f, -1.0f, 1.0f);
	mesh.GetVertex(13).position = Math::Vector3(-1.0f, -1.0f, -1.0f);
	mesh.GetVertex(14).position = Math::Vector3(1.0f, -1.0f, -1.0f);
	mesh.GetVertex(15).position = Math::Vector3(1.0f, -1.0f, 1.0f);

	// Pos Z
	mesh.GetVertex(16).position = Math::Vector3(1.0f, -1.0f, 1.0f);
	mesh.GetVertex(17).position = Math::Vector3(1.0f, 1.0f, 1.0f);
	mesh.GetVertex(18).position = Math::Vector3(-1.0f, 1.0f, 1.0f);
	mesh.GetVertex(19).position = Math::Vector3(-1.0f, -1.0f, 1.0f);

	// Neg Z
	mesh.GetVertex(20).position = Math::Vector3(-1.0f, -1.0f, -1.0f);
	mesh.GetVertex(21).position = Math::Vector3(-1.0f, 1.0f, -1.0f);
	mesh.GetVertex(22).position = Math::Vector3(1.0f, 1.0f, -1.0f);
	mesh.GetVertex(23).position = Math::Vector3(1.0f, -1.0f, -1.0f);

	const Math::Vector3 kNormals[] =
	{
		Math::Vector3(1.0f,  0.0f,  0.0f),	// Pos X
		Math::Vector3(-1.0f,  0.0f,  0.0f),	// Neg X
		Math::Vector3(0.0f,  1.0f,  0.0f),	// Pos Y
		Math::Vector3(0.0f, -1.0f,  0.0f),	// Neg Y
		Math::Vector3(0.0f,  0.0f,  1.0f),	// Pos Z
		Math::Vector3(0.0f,  0.0f, -1.0f)	// Neg Z
	};

	for (uint32_t i = 0; i < 6; ++i)
	{
		mesh.GetVertex(i * 4).normal = kNormals[i];
		mesh.GetVertex(i * 4 + 1).normal = kNormals[i];
		mesh.GetVertex(i * 4 + 2).normal = kNormals[i];
		mesh.GetVertex(i * 4 + 3).normal = kNormals[i];
	}

	const Math::Vector3 kTangents[] =
	{
		Math::Vector3(0.0f, 0.0f,  1.0f),	// Pos X
		Math::Vector3(0.0f, 0.0f, -1.0f),	// Neg X
		Math::Vector3(1.0f, 0.0f,  0.0f),	// Pos Y
		Math::Vector3(1.0f, 0.0f,  0.0f),	// Neg Y
		Math::Vector3(-1.0f, 0.0f,  0.0f),	// Pos Z
		Math::Vector3(1.0f, 0.0f,  0.0f)	// Neg Z
	};

	for (uint32_t i = 0; i < 6; ++i)
	{
		mesh.GetVertex(i * 4).tangent = kTangents[i];
		mesh.GetVertex(i * 4 + 1).tangent = kTangents[i];
		mesh.GetVertex(i * 4 + 2).tangent = kTangents[i];
		mesh.GetVertex(i * 4 + 3).tangent = kTangents[i];
	}

	for (uint32_t i = 0; i < 6; ++i)
	{
		mesh.GetVertex(i * 4).texcoord = Math::Vector2(0.0f, 1.0f);
		mesh.GetVertex(i * 4 + 1).texcoord = Math::Vector2(0.0f, 0.0f);
		mesh.GetVertex(i * 4 + 2).texcoord = Math::Vector2(1.0f, 0.0f);
		mesh.GetVertex(i * 4 + 3).texcoord = Math::Vector2(1.0f, 1.0f);
	}

	for (uint32_t i = 0; i < kNumVertices; ++i)
	{
		mesh.GetVertex(i).color = Math::Vector4::White();
	}

	const uint16_t kIndices[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	for (uint32_t i = 0; i < kNumIndices; ++i)
	{
		mesh.GetIndex(i) = kIndices[i];
	}
}

void MeshBuilder::CreateSkybox(Mesh& mesh)
{
	const uint32_t kNumVertices = 24;
	const uint32_t kNumIndices = 36;

	mesh.Initialize(kNumVertices, kNumIndices);

	// Pos X
	mesh.GetVertex(0).position = Math::Vector3(1.0f, -1.0f, 1.0f);
	mesh.GetVertex(1).position = Math::Vector3(1.0f, 1.0f, 1.0f);
	mesh.GetVertex(2).position = Math::Vector3(1.0f, 1.0f, -1.0f);
	mesh.GetVertex(3).position = Math::Vector3(1.0f, -1.0f, -1.0f);

	// Neg X
	mesh.GetVertex(4).position = Math::Vector3(-1.0f, -1.0f, -1.0f);
	mesh.GetVertex(5).position = Math::Vector3(-1.0f, 1.0f, -1.0f);
	mesh.GetVertex(6).position = Math::Vector3(-1.0f, 1.0f, 1.0f);
	mesh.GetVertex(7).position = Math::Vector3(-1.0f, -1.0f, 1.0f);

	// Pos Y
	mesh.GetVertex(8).position = Math::Vector3(-1.0f, 1.0f, 1.0f);
	mesh.GetVertex(9).position = Math::Vector3(-1.0f, 1.0f, -1.0f);
	mesh.GetVertex(10).position = Math::Vector3(1.0f, 1.0f, -1.0f);
	mesh.GetVertex(11).position = Math::Vector3(1.0f, 1.0f, 1.0f);

	// Neg Y
	mesh.GetVertex(12).position = Math::Vector3(-1.0f, -1.0f, -1.0f);
	mesh.GetVertex(13).position = Math::Vector3(-1.0f, -1.0f, 1.0f);
	mesh.GetVertex(14).position = Math::Vector3(1.0f, -1.0f, 1.0f);
	mesh.GetVertex(15).position = Math::Vector3(1.0f, -1.0f, -1.0f);

	// Pos Z
	mesh.GetVertex(16).position = Math::Vector3(-1.0f, -1.0f, 1.0f);
	mesh.GetVertex(17).position = Math::Vector3(-1.0f, 1.0f, 1.0f);
	mesh.GetVertex(18).position = Math::Vector3(1.0f, 1.0f, 1.0f);
	mesh.GetVertex(19).position = Math::Vector3(1.0f, -1.0f, 1.0f);

	// Neg Z
	mesh.GetVertex(20).position = Math::Vector3(1.0f, -1.0f, -1.0f);
	mesh.GetVertex(21).position = Math::Vector3(1.0f, 1.0f, -1.0f);
	mesh.GetVertex(22).position = Math::Vector3(-1.0f, 1.0f, -1.0f);
	mesh.GetVertex(23).position = Math::Vector3(-1.0f, -1.0f, -1.0f);

	const uint16_t kIndices[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	for (uint32_t i = 0; i < 36; ++i)
	{
		mesh.GetIndex(i) = kIndices[i];
	}
}

void MeshBuilder::CreateSphere(Mesh& mesh, uint32_t slices, uint32_t rings)
{
	const uint32_t kNumVertices = (slices + 1) * rings;
	const uint32_t kNumIndices = slices * (rings - 1) * 6;
	const float kSliceStep = Math::kTwoPi / slices;
	const float kRingStep = Math::kPi / (rings - 1);

	// Allocate memory
	mesh.Initialize(kNumVertices, kNumIndices);

	// Fill vertex data
	float uStep = 1.0f / slices;
	float vStep = 1.0f / rings;
	uint32_t index = 0;
	for (uint32_t j = 0; j < rings; ++j)
	{
		const float phi = j * kRingStep;
		for (uint32_t i = 0; i <= slices; ++i)
		{
			const float theta = i * kSliceStep;
			const float y = cos(phi);
			const float r = sqrt(1.0f - (y * y));
			const float s = sin(theta);
			const float c = cos(theta);
			const float x = r * c;
			const float z = r * s;

			mesh.GetVertex(index).position = Math::Vector3(x, y, z);
			mesh.GetVertex(index).normal = Math::Vector3(x, y, z);
			mesh.GetVertex(index).tangent = Math::Vector3(-s, 0.0f, c);
			mesh.GetVertex(index).color = Math::Vector4::White();
			mesh.GetVertex(index).texcoord = Math::Vector2(i * uStep, j * vStep);

			++index;
		}
	}

	// Fill index data
	index = 0;
	for (uint32_t j = 0; j < rings - 1; ++j)
	{
		for (uint32_t i = 0; i < slices; ++i)
		{
			const uint32_t a = i % (slices + 1);
			const uint32_t b = (i + 1) % (slices + 1);
			const uint32_t c = j * (slices + 1);
			const uint32_t d = (j + 1) * (slices + 1);

			//     a     b
			//   c +-----+
			//     |     |
			//     |     |
			//   d +-----+
			//
			mesh.GetIndex(index++) = a + c;
			mesh.GetIndex(index++) = b + c;
			mesh.GetIndex(index++) = a + d;

			mesh.GetIndex(index++) = b + c;
			mesh.GetIndex(index++) = b + d;
			mesh.GetIndex(index++) = a + d;
		}
	}
}

void MeshBuilder::CreateTerrain(Mesh& mesh, const Heightmap& heightMap, uint32_t width, uint32_t length, float maxHeight)
{
	uint32_t vertCounts = width * length;
	uint32_t indCounts = (width - 1) * (length - 1) * 6;

	Vertex* TerrainVerts = new Vertex[vertCounts];
	uint32_t* TerrainIndices = new uint32_t[indCounts];

	float minX = -(float)width / 2.0f;
	float minZ = -(float)length / 2.0f;

	for (uint32_t row = 0; row < length; ++row)
	{
		for (uint32_t col = 0; col < width; ++col)
		{
			TerrainVerts[col + (row * width)] = Vertex
			(Math::Vector3(minX + col, heightMap.GetHeight(col, row) * maxHeight, -(minZ + row)), // pos
				Math::Vector3::YAxis(),															 // norm
				Math::Vector4::Black(),															 // color
				Math::Vector2(col / (float)(width - 1), row / (float)(length - 1)));							 // uv
		}
	}



	for (uint32_t row = 0; row < length - 1; ++row)
	{
		for (uint32_t col = 0; col < width - 1; ++col)
		{
			TerrainIndices[(row *(width - 1) + col) * 6 + 0] = row * length + col;
			TerrainIndices[(row *(width - 1) + col) * 6 + 1] = row * length + col + 1;
			TerrainIndices[(row *(width - 1) + col) * 6 + 2] = row * length + col + length + 1;
			TerrainIndices[(row *(width - 1) + col) * 6 + 3] = row * length + col;
			TerrainIndices[(row *(width - 1) + col) * 6 + 4] = row * length + col + length + 1;
			TerrainIndices[(row *(width - 1) + col) * 6 + 5] = row * length + col + length;
		}
	}

	mesh.Initialize(TerrainVerts, vertCounts, TerrainIndices, indCounts);

}