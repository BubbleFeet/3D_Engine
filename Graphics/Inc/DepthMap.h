#ifndef INCLUDED_GRAPHICS_DEPTHMAP_H
#define INCLUDED_GRAPHICS_DEPTHMAP_H

//====================================================================================================
// Filename:	DepthMap.h
// Created by:	Peter Chan
// Description:	Class for a depth map.
//====================================================================================================

namespace Graphics {

class DepthMap
{
public:
	DepthMap();
	~DepthMap();
	
	void Initialize(uint32_t width, uint32_t height);
	void Terminate();

	void BeginRender();
	void EndRender();
	
	void BindTexture(uint32_t index);
	void UnbindTexture(uint32_t index);

private:
	ID3D11ShaderResourceView* mShaderResourceView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mViewport;
};

} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_DEPTHMAP_H