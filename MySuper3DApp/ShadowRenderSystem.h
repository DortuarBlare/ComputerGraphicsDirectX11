#pragma once
#include "Game.h"

using namespace Microsoft::WRL;

class ShadowRenderSystem {
private:
	void PrepareFrame();
	void DrawInternal(std::vector<std::shared_ptr<GameObject>>& gameObjects);
	void EndFrame();

public:
	ComPtr<ID3D11Texture2D> lightDepthBufferTexture;
	ComPtr<ID3D11RenderTargetView> lightDepthBufferRenderTargetView;
	ComPtr<ID3D11ShaderResourceView> textureResourceView;

	ComPtr<ID3D11DepthStencilView> depthStencilView;
	ComPtr<ID3D11Texture2D> depthStencilBuffer;

	ComPtr<ID3D11InputLayout> layout;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11VertexShader> vertexShader;

	ComPtr<ID3D11RasterizerState> rastState;
	ComPtr<ID3D11DepthStencilState> depthStencilState;

	ShadowRenderSystem();

	void Update();
	void Draw(std::vector<std::shared_ptr<GameObject>>& gameObjects);
};
