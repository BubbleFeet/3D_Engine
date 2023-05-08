#ifndef INCLUDED_GRAPHICS_PIXELSHADER_H
#define INCLUDED_GRAPHICS_PIXELSHADER_H


namespace Graphics
{
	class PixelShader
	{
	public:

		PixelShader() : mPixelShader(nullptr) {}
		~PixelShader() {}
	
		ID3D11PixelShader* mPixelShader;

		void Bind();
		void Initialize(const wchar_t* fileName, const char* entry = "PS");
		void Terminate();

	};
} // namespace Graphics

#endif // INCLUDED_GRAPHICS_PIXELSHADER_H
