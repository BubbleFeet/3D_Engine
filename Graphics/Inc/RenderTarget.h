#ifndef INCLUDED_GRAPHICS_RENDERTARGET_H
#define INCLUDED_GRAPHICS_RENDERTARGET_H

namespace Graphics {

class RenderTarget
{
	NONCOPYABLE(RenderTarget);

public:
	enum Format
	{
		RGBA_U8,
		RGBA_F16,
		RGBA_U32,
		R_F16,
		R_S32
	};

	RenderTarget();
	~RenderTarget();

	void Initialize(uint32_t width, uint32_t height, Format format);
	void Terminate();

	void BeginRender();
	void EndRender();

	void BindPS(uint32_t index);
	void UnbindPS(uint32_t index);
	void Copy(ID3D11Texture2D* texture);

private:
	ID3D11ShaderResourceView* mShaderResourceView;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mViewport;
	D3D11_MAPPED_SUBRESOURCE mSubresource;
};

} // namespace Graphics

#endif // !INCLUDED_GRAPHICS_RENDERTARGET_H