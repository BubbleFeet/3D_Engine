//====================================================================================================
// Filename:	SimpleDraw.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SimpleDraw.h"

#include "Camera.h"
#include "ConstantBuffer.h"
#include "GraphicsSystem.h"
#include "PixelShader.h"
#include "VertexShader.h"

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	struct SimpleVertex
	{
		Math::Vector3 position;
		Math::Vector3 normal;
		Math::Vector3 tangent;
		Math::Vector4 color;
		Math::Vector2 texcoord;

		SimpleVertex()
			: position(0.0f, 0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f)
		{}

		SimpleVertex(float x, float y, float z, const Math::Vector4& color)
			: position(x, y, z)
			, color(color)
		{}

		SimpleVertex(const Math::Vector3& v0, const Math::Vector4& color)
			: position(v0)
			, color(color)
		{}
	};

	struct CBSimpleDraw
	{
		Math::Matrix transform;
	};
}

//====================================================================================================
// Class Declarations
//====================================================================================================

namespace Graphics {
	namespace SimpleDraw
	{

		class SimpleDrawImpl
		{
		public:
			// Constructor
			SimpleDrawImpl(GraphicsSystem& gs);

			// Destructor
			~SimpleDrawImpl();

			// Functions to startup/shutdown simple draw
			void Initialize(uint32_t maxVertices);
			void Terminate();

			// Functions to add 3D lines
			void AddLine(float x0, float y0, float z0, float x1, float y1, float z1, const Math::Vector4& color);
			void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector4& color);
			void AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Math::Vector4& color);
			void AddPlane(const Math::Plane& plane, const Math::Vector3& referencePoint, float size, float spacing, Math::Vector4& color);
			void AddSphere(const Math::Sphere& sphere, const Math::Vector4& color, uint32_t slices, uint32_t rings);
			void AddTransform(const Math::Matrix& transform);

			// Functions to add screen lines
			void AddScreenLine(float x0, float y0, float x1, float y1, const Math::Vector4& color);
			void AddScreenRect(float l, float t, float r, float b, const Math::Vector4& color);
			void AddScreenCircle(float x, float y, float r, const Math::Vector4& color);

			// Function to render all the lines added
			void Render(const Camera& camera);

		private:
			GraphicsSystem& mGS;

			VertexShader mVertexShader;
			PixelShader mPixelShader;

			TypedConstantBuffer<CBSimpleDraw> mConstantBuffer;

			ID3D11Buffer* mpVertexBuffer;
			ID3D11Buffer* mpVertexBuffer2D;

			SimpleVertex* mpVertices3D;
			SimpleVertex* mpVertices2D;

			uint32_t mMaxVertices;
			uint32_t mNumVertices3D;
			uint32_t mNumVertices2D;

			bool mInitialized;
		};

		//====================================================================================================
		// Class Definitions
		//====================================================================================================

		SimpleDrawImpl::SimpleDrawImpl(GraphicsSystem& gs)
			: mGS(gs)
			, mpVertexBuffer(nullptr)
			, mpVertexBuffer2D(nullptr)
			, mpVertices3D(nullptr)
			, mpVertices2D(nullptr)
			, mMaxVertices(0)
			, mNumVertices2D(0)
			, mNumVertices3D(0)
			, mInitialized(false)
		{
			// Empty
		}

		//----------------------------------------------------------------------------------------------------

		SimpleDrawImpl::~SimpleDrawImpl()
		{
			// Empty
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::Initialize(uint32_t maxVertices)
		{
			ASSERT(!mInitialized, "[SimpleDraw] Already initialized.");

			mVertexShader.Initialize(L"../Engine/Shaders/SimpleDraw.fx");
			mPixelShader.Initialize(L"../Engine/Shaders/SimpleDraw.fx");
			mConstantBuffer.Initialize();

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = maxVertices * sizeof(SimpleVertex);
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bd.MiscFlags = 0;

			// Create vertex buffers for 3D/2D lines
			mGS.GetDevice()->CreateBuffer(&bd, nullptr, &mpVertexBuffer);
			mGS.GetDevice()->CreateBuffer(&bd, nullptr, &mpVertexBuffer2D);

			// Create line buffers
			mpVertices3D = new SimpleVertex[maxVertices];
			mpVertices2D = new SimpleVertex[maxVertices];

			mMaxVertices = maxVertices;
			mNumVertices3D = 0;
			mNumVertices2D = 0;

			// Set flag
			mInitialized = true;
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::Terminate()
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			// Release everything
			if (mpVertices2D != nullptr)
			{
				delete[] mpVertices2D;
				mpVertices2D = nullptr;
			}
			if (mpVertices3D != nullptr)
			{
				delete[] mpVertices3D;
				mpVertices3D = nullptr;
			}

			SafeRelease(mpVertexBuffer2D);
			SafeRelease(mpVertexBuffer);

			mConstantBuffer.Terminate();
			mPixelShader.Terminate();
			mVertexShader.Terminate();

			// Clear flag
			mInitialized = false;
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::AddLine(float x0, float y0, float z0, float x1, float y1, float z1, const Math::Vector4& color)
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			// Check if we have enough space
			if (mNumVertices3D + 2 <= mMaxVertices)
			{
				// Add line
				mpVertices3D[mNumVertices3D++] = SimpleVertex(x0, y0, z0, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(x1, y1, z1, color);
			}

			ASSERT(mNumVertices3D < mMaxVertices, "[SimpleDraw] Too many vertices!");
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector4& color)
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			// Check if we have enough space
			if (mNumVertices3D + 2 <= mMaxVertices)
			{
				// Add line
				mpVertices3D[mNumVertices3D++] = SimpleVertex(v0, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(v1, color);
			}

			ASSERT(mNumVertices3D < mMaxVertices, "[SimpleDraw] Too many vertices!");
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Math::Vector4& color)
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			// Check if we have enough space
			if (mNumVertices3D + 24 <= mMaxVertices)
			{
				// Add lines
				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, minZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, maxZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, maxZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, maxZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, maxZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, minZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, minZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, minZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, minZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, minZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, minY, maxZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, maxZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, maxZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, maxZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, minY, minZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, minZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, minZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, maxZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, maxZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, maxZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, maxZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, minZ, color);

				mpVertices3D[mNumVertices3D++] = SimpleVertex(maxX, maxY, minZ, color);
				mpVertices3D[mNumVertices3D++] = SimpleVertex(minX, maxY, minZ, color);
			}

			ASSERT(mNumVertices3D < mMaxVertices, "[SimpleDraw] Too many vertices!");
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::AddPlane(const Math::Plane& plane, const Math::Vector3& referencePoint, float size, float spacing, Math::Vector4& color)
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			float dist = Math::Dot(referencePoint, plane.n);

			float distFromPointToPlane = dist - plane.d;
			Math::Vector3 pointOnPlane = referencePoint - (plane.n * (distFromPointToPlane));

			Math::Vector3 PlaneAxisX = Math::Vector3::XAxis();
			Math::Vector3 PlaneAxisY = Normalize(Math::Cross(plane.n, PlaneAxisX));

			
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::AddSphere(const Math::Sphere& sphere, const Math::Vector4& color, uint32_t slices, uint32_t rings)
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			const float x = sphere.center.x;
			const float y = sphere.center.y;
			const float z = sphere.center.z;
			const float radius = sphere.radius;

			const uint32_t kSlices = Math::Max(3u, slices);
			const uint32_t kRings = Math::Max(2u, rings);
			const uint32_t kLines = (4 * kSlices * kRings) - (2 * kSlices);

			// Check if we have enough space
			if (mNumVertices3D + kLines <= mMaxVertices)
			{
				// Add lines
				const float kTheta = Math::kPi / (float)kRings;
				const float kPhi = Math::kTwoPi / (float)kSlices;
				for (uint32_t j = 0; j < kSlices; ++j)
				{
					for (uint32_t i = 0; i < kRings; ++i)
					{
						const float a = i * kTheta;
						const float b = a + kTheta;
						const float ay = radius * cos(a);
						const float by = radius * cos(b);

						const float theta = j * kPhi;
						const float phi = theta + kPhi;

						const float ar = sqrt(radius * radius - ay * ay);
						const float br = sqrt(radius * radius - by * by);

						const float x0 = x + (ar * sin(theta));
						const float y0 = y + (ay);
						const float z0 = z + (ar * cos(theta));

						const float x1 = x + (br * sin(theta));
						const float y1 = y + (by);
						const float z1 = z + (br * cos(theta));

						const float x2 = x + (br * sin(phi));
						const float y2 = y + (by);
						const float z2 = z + (br * cos(phi));

						mpVertices3D[mNumVertices3D++] = { Math::Vector3(x0, y0, z0), color };
						mpVertices3D[mNumVertices3D++] = { Math::Vector3(x1, y1, z1), color };

						if (i < kRings - 1)
						{
							mpVertices3D[mNumVertices3D++] = { Math::Vector3(x1, y1, z1), color };
							mpVertices3D[mNumVertices3D++] = { Math::Vector3(x2, y2, z2), color };
						}
					}
				}
			}

			ASSERT(mNumVertices3D < mMaxVertices, "[SimpleDraw] Too many vertices!");
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::AddScreenLine(float x0, float y0, float x1, float y1, const Math::Vector4& color)
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			// Check if we have enough space
			if (mNumVertices2D + 2 <= mMaxVertices)
			{
				// Add line
				mpVertices2D[mNumVertices2D++] = SimpleVertex(x0, y0, 0.0f, color);
				mpVertices2D[mNumVertices2D++] = SimpleVertex(x1, y1, 0.0f, color);
			}

			ASSERT(mNumVertices2D < mMaxVertices, "[SimpleDraw] Too many vertices!");
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::AddScreenRect(float l, float t, float r, float b, const Math::Vector4& color)
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			// Check if we have enough space
			if (mNumVertices2D + 8 <= mMaxVertices)
			{
				// Add lines
				mpVertices2D[mNumVertices2D++] = SimpleVertex(l, t, 0.0f, color);
				mpVertices2D[mNumVertices2D++] = SimpleVertex(r, t, 0.0f, color);

				mpVertices2D[mNumVertices2D++] = SimpleVertex(r, t, 0.0f, color);
				mpVertices2D[mNumVertices2D++] = SimpleVertex(r, b, 0.0f, color);

				mpVertices2D[mNumVertices2D++] = SimpleVertex(r, b, 0.0f, color);
				mpVertices2D[mNumVertices2D++] = SimpleVertex(l, b, 0.0f, color);

				mpVertices2D[mNumVertices2D++] = SimpleVertex(l, b, 0.0f, color);
				mpVertices2D[mNumVertices2D++] = SimpleVertex(l, t, 0.0f, color);
			}

			ASSERT(mNumVertices2D < mMaxVertices, "[SimpleDraw] Too many vertices!");
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::AddScreenCircle(float x, float y, float r, const Math::Vector4& color)
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			// Check if we have enough space
			if (mNumVertices2D + 32 <= mMaxVertices)
			{
				// Add line
				const float kAngle = Math::kPi / 8.0f;
				for (uint32_t i = 0; i < 16; ++i)
				{
					const float alpha = i * kAngle;
					const float beta = alpha + kAngle;
					const float x0 = x + (r * sin(alpha));
					const float y0 = y + (r * cos(alpha));
					const float x1 = x + (r * sin(beta));
					const float y1 = y + (r * cos(beta));
					mpVertices2D[mNumVertices2D++] = SimpleVertex(x0, y0, 0.0f, color);
					mpVertices2D[mNumVertices2D++] = SimpleVertex(x1, y1, 0.0f, color);
				}
			}

			ASSERT(mNumVertices2D < mMaxVertices, "[SimpleDraw] Too many vertices!");
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::AddTransform(const Math::Matrix& transform)
		{
			Math::Vector3 position = Math::GetTranslation(transform);
			Math::Vector3 right = Math::GetRight(transform);
			Math::Vector3 up = Math::GetUp(transform);
			Math::Vector3 forward = Math::GetForward(transform);
			AddLine(position, position + right, Math::Vector4::Red());
			AddLine(position, position + up, Math::Vector4::Green());
			AddLine(position, position + forward, Math::Vector4::Blue());
		}

		//----------------------------------------------------------------------------------------------------

		void SimpleDrawImpl::Render(const Camera& camera)
		{
			ASSERT(mInitialized, "[SimpleDraw] Not initialized.");

			Math::Matrix matView = camera.GetViewMatrix();
			Math::Matrix matProj = camera.GetProjectionMatrix();

			mVertexShader.Bind();
			mPixelShader.Bind();

			CBSimpleDraw cb;
			cb.transform = Math::Transpose(matView * matProj);
			mConstantBuffer.Set( cb);
			mConstantBuffer.BindVS(0);

			UINT stride = sizeof(SimpleVertex);
			UINT offset = 0;

			// Draw 3D lines
			D3D11_MAPPED_SUBRESOURCE resource;
			mGS.GetContext()->Map(mpVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
			memcpy(resource.pData, mpVertices3D, mNumVertices3D * stride);
			mGS.GetContext()->Unmap(mpVertexBuffer, 0);

			mGS.GetContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
			mGS.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			mGS.GetContext()->Draw(mNumVertices3D, 0);

			const uint32_t w = mGS.GetWidth();
			const uint32_t h = mGS.GetHeight();
			Math::Matrix matInvScreen
			(
				2.0f / w, 0.0f, 0.0f, 0.0f,
				0.0f, -2.0f / h, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				-1.0f, 1.0f, 0.0f, 1.0f
			);
			cb.transform = Math::Transpose(matInvScreen);
			mConstantBuffer.Set(cb);
			mConstantBuffer.BindVS(0);

			// Draw 2D lines
			mGS.GetContext()->Map(mpVertexBuffer2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
			memcpy(resource.pData, mpVertices2D, mNumVertices2D * stride);
			mGS.GetContext()->Unmap(mpVertexBuffer2D, 0);

			mGS.GetContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer2D, &stride, &offset);
			mGS.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			mGS.GetContext()->Draw(mNumVertices2D, 0);

			// Reset index
			mNumVertices3D = 0;
			mNumVertices2D = 0;
		}

		//====================================================================================================
		// Statics
		//====================================================================================================

		static SimpleDrawImpl* sSimpleDrawImpl = nullptr;

		//====================================================================================================
		// Function Definitions
		//====================================================================================================

		void Initialize(GraphicsSystem& GraphicsSystem, uint32_t maxVertices)
		{
			if (nullptr == sSimpleDrawImpl)
			{
				sSimpleDrawImpl = new SimpleDrawImpl(GraphicsSystem);
				sSimpleDrawImpl->Initialize(maxVertices);
			}
		}

		//----------------------------------------------------------------------------------------------------

		void Terminate()
		{
			if (nullptr != sSimpleDrawImpl)
			{
				sSimpleDrawImpl->Terminate();
				delete sSimpleDrawImpl;
				sSimpleDrawImpl = nullptr;
			}
		}

		//----------------------------------------------------------------------------------------------------

		void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddLine(v0.x, v0.y, v0.z, v1.x, v1.y, v1.z, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddLine(float x0, float y0, float z0, float x1, float y1, float z1, const Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddLine(x0, y0, z0, x1, y1, z1, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddAABB(const Math::AABB& aabb, const Math::Vector4& color)
		{
			SimpleDraw::AddAABB(aabb.center - aabb.extend, aabb.center + aabb.extend, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddAABB(const Math::Vector3& center, float extend, const Math::Vector4& color)
		{
			SimpleDraw::AddAABB(center.x - extend, center.y - extend, center.z - extend, center.x + extend, center.y + extend, center.z + extend, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddAABB(const Math::Vector3& min, const Math::Vector3& max, const Math::Vector4& color)
		{
			SimpleDraw::AddAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddAABB(minX, minY, minZ, maxX, maxY, maxZ, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddPlane(const Math::Plane& plane, const Math::Vector3& referencePoint, float size, float spacing, Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddPlane(plane, referencePoint, size, spacing, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddSphere(const Math::Vector3& center, float radius, const Math::Vector4& color, uint32_t slices, uint32_t rings)
		{
			AddSphere(Math::Sphere(center, radius), color, slices, rings);
		}

		//----------------------------------------------------------------------------------------------------

		void AddSphere(const Math::Sphere& sphere, const Math::Vector4& color, uint32_t slices, uint32_t rings)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddSphere(sphere, color, slices, rings);
		}

		//----------------------------------------------------------------------------------------------------

		void AddSphere(float x, float y, float z, float radius, const Math::Vector4& color, uint32_t slices, uint32_t rings)
		{
			AddSphere(Math::Sphere(x, y, z, radius), color, slices, rings);
		}

		//----------------------------------------------------------------------------------------------------

		void AddScreenLine(const Math::Vector2& v0, const Math::Vector2& v1, const Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddScreenLine(v0.x, v0.y, v1.x, v1.y, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddScreenLine(float x0, float y0, float x1, float y1, const Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddScreenLine(x0, y0, x1, y1, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddScreenRect(const Math::Vector2& min, const Math::Vector2& max, const Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddScreenRect(min.x, min.y, max.x, max.y, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddScreenRect(float x, float y, float w, float h, const Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddScreenRect(x, y, w, h, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddScreenCircle(const Math::Vector2& center, float r, const Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddScreenCircle(center.x, center.y, r, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddScreenCircle(float x, float y, float r, const Math::Vector4& color)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->AddScreenCircle(x, y, r, color);
		}

		//----------------------------------------------------------------------------------------------------

		void AddTransform(const Math::Matrix matrix)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");

			Math::Vector3 objPosition(matrix._41, matrix._42, matrix._43);

			Math::Vector3 xAxis = objPosition + Math::Normalize(Math::Vector3(matrix._11, matrix._12, matrix._13));
			Math::Vector3 yAxis = objPosition + Math::Normalize(Math::Vector3(matrix._21, matrix._22, matrix._23));
			Math::Vector3 zAxis = objPosition + Math::Normalize(Math::Vector3(matrix._31, matrix._32, matrix._33));

			sSimpleDrawImpl->AddLine(objPosition, xAxis, Math::Vector4::Red());
			sSimpleDrawImpl->AddLine(objPosition, yAxis, Math::Vector4::Green());
			sSimpleDrawImpl->AddLine(objPosition, zAxis, Math::Vector4::Blue());
		}

		void Render(const Camera& camera)
		{
			ASSERT(sSimpleDrawImpl != nullptr, "[SimpleDraw] Not initialized.");
			sSimpleDrawImpl->Render(camera);
		}

	} // namespace SimpleDraw
} // namespace Graphics