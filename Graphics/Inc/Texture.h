#ifndef INCLUDED_GRAPHICS_TEXTURE_H
#define INCLUDED_GRAPHICS_TEXTURE_H

namespace Graphics {

class Texture
{
public:
	Texture();
	~Texture();

	void Initialize(const wchar_t* filename);
	void Initialize(const void* data, uint32_t width, uint32_t height);
	void Terminate();

	void BindPS(uint32_t slot);
	void BindVS(uint32_t slot);

private:
	ID3D11ShaderResourceView* mShaderResourceView;
	ID3D11Texture2D* texture;
};

}	// namespace Graphics

#endif // !INCLUDED_GRAPHICS_TEXTURE_H