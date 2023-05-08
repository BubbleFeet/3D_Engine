#ifndef INCLUDED_GRAPHICS_GEOMETRYSHADER_H
#define INCLUDED_GRAPHICS_GEOMETRYSHADER_H

namespace Graphics
{
	class GeometryShader
	{
	public:

		GeometryShader() : mGeometryShader(nullptr) {}
		~GeometryShader() {}

		ID3D11GeometryShader* mGeometryShader;

		void Bind();
		void Initialize(const wchar_t* fileName);
		void Terminate();

	};
} // namespace Graphics

#endif // INCLUDED_GRAPHICS_GEOMETRYSHADER_H

