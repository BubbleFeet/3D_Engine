#ifndef INCLUDED_GRAPHICS_GRAPHICSSYSTEM_H
#define INCLUDED_GRAPHICS_GRAPHICSSYSTEM_H

// Description: Class for the graphics system
namespace Graphics
{
	class GraphicsSystem
	{
		NONCOPYABLE(GraphicsSystem);

	public:
		static void StaticInitialize(HWND window, bool fullscreen);
		static void StaticTerminate();
		static GraphicsSystem* Get();

	public:
		GraphicsSystem();
		~GraphicsSystem();

		void Initialize(HWND window, bool fullscreen);
		void Terminate();

		void BeginRender(Math::Vector4 clearColor = Math::Vector4::Black());
		void EndRender();

		void ToggleFullscreen();

		void ResetRenderTarget();
		void ResetViewport();

		void EnableDepthTesting(bool enable);

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		ID3D11Device* GetDevice()			{ return mD3DDevice; }
		ID3D11DeviceContext* GetContext()	{ return mImmediateContext; }

	private:
		ID3D11Device* mD3DDevice;
		ID3D11DeviceContext* mImmediateContext;

		IDXGISwapChain* mSwapChain;
		ID3D11RenderTargetView* mRenderTargetView;

		ID3D11Texture2D* mDepthStencilBuffer;
		ID3D11DepthStencilView* mDepthStencilView;
		ID3D11DepthStencilState* mDisableDepthStencil;

		D3D_DRIVER_TYPE mDriverType;
		D3D_FEATURE_LEVEL mFeatureLevel;

		DXGI_SWAP_CHAIN_DESC mSwapChainDesc;

		D3D11_VIEWPORT mViewport;
	};

}

#endif