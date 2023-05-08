#ifndef INCLUDED_GRAPHICS_VERTEXSHADER_H
#define INCLUDED_GRAPHICS_VERTEXSHADER_H

namespace Graphics
{
	class VertexShader
	{
	public:
		VertexShader() :mVertexShader(nullptr), mInputLayout(nullptr) {};
		~VertexShader() {}

		void Initialize(const wchar_t* fileName, const char* entry = "VS");
		void Terminate();

		void Bind();

	private:

		//ID3D11DeviceContext* context;
		ID3D11VertexShader* mVertexShader;
		ID3D11InputLayout* mInputLayout;

	};
} // namespace Graphics

#endif INCLUDED_GRAPHICS_VERTEXSHADER_H