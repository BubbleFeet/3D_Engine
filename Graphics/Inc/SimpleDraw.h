#ifndef INCLUDED_GRAPHICS_SIMPLEDRAW_H
#define INCLUDED_GRAPHICS_SIMPLEDRAW_H

//====================================================================================================
// Filename:	SimpleDraw.h
// Created by:	Peter Chan
// Description:	Header containing some useful rendering functions.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

namespace Math
{
	struct AABB;
	struct Vector2;
	struct Vector3;
}

class Camera;
class GraphicsSystem;

//====================================================================================================
// Function Declarations
//====================================================================================================

namespace Graphics
{
namespace SimpleDraw
{

// Functions to startup/shutdown simple draw
void Initialize(GraphicsSystem& gs, uint32_t maxVertices = 10000);
void Terminate();

// Functions for world space rendering
void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector4& color);
void AddLine(float x0, float y0, float z0, float x1, float y1, float z1, const Math::Vector4& color);
void AddAABB(const Math::AABB& aabb, const Math::Vector4& color);
void AddAABB(const Math::Vector3& center, float extend, const Math::Vector4& color);
void AddAABB(const Math::Vector3& min, const Math::Vector3& max, const Math::Vector4& color);
void AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Math::Vector4& color);
void AddPlane(const Math::Plane& plane, const Math::Vector3& referencePoint, float size, float spacing, Math::Vector4& color);
void AddSphere(const Math::Vector3& center, float radius, const Math::Vector4& color, uint32_t slices = 8, uint32_t rings = 4);
void AddSphere(const Math::Sphere& sphere, const Math::Vector4& color, uint32_t slices = 8, uint32_t rings = 4);

// Functions for screen space rendering
void AddScreenLine(const Math::Vector2& v0, const Math::Vector2& v1, const Math::Vector4& color);
void AddScreenLine(float x0, float y0, float x1, float y1, const Math::Vector4& color);
void AddScreenRect(const Math::Vector2& min, const Math::Vector2& max, const Math::Vector4& color);
void AddScreenRect(float x, float y, float w, float h, const Math::Vector4& color);
void AddScreenCircle(const Math::Vector2& center, float r, const Math::Vector4& color);
void AddScreenCircle(float x, float y, float r, const Math::Vector4& color);
void AddTransform(const Math::Matrix& matrix);

// Function to actually render all the geometry.
void Render(const Camera& camera);

} // namespace SimpleDraw
} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_SIMPLEDRAW_H