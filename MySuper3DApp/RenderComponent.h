#pragma once
#include "pch.h"
#include "GameObjectComponent.h"
#include "WICTextureLoader.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

class RenderComponent : public GameObjectComponent {
protected:
	ComPtr<ID3D11InputLayout> layout;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3DBlob> pixelShaderByteCode;
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3DBlob> vertexShaderByteCode;

	ComPtr<ID3D11RasterizerState> rastState;

	std::shared_ptr<D3D11_SUBRESOURCE_DATA> vertexData;
	ComPtr<ID3D11Buffer> vertexBuf;

	std::shared_ptr<D3D11_SUBRESOURCE_DATA> indexData;
	ComPtr<ID3D11Buffer> indexBuf;

	std::shared_ptr<D3D11_SUBRESOURCE_DATA> constData;
	ComPtr<ID3D11Buffer> constBuf;
	std::shared_ptr<Matrix> constBufMatrix;

	LPCWSTR textureFileName;
	ComPtr<ID3D11Resource> texture;
	ComPtr<ID3D11ShaderResourceView> textureView;
	ComPtr<ID3D11SamplerState> samplerState;

	std::vector<unsigned int> indexes;
	std::vector<XMFLOAT4> points;

	D3D11_FILL_MODE fillMode;

	UINT strides[1];
	UINT offsets[1];

public:
	RenderComponent();
	RenderComponent(D3D11_FILL_MODE fillMode);
	RenderComponent(LPCWSTR textureFileName, D3D11_FILL_MODE fillMode);

	virtual void Initialize();
	void Update();
	void FixedUpdate();
	virtual void Draw();
	void Reload();
	void DestroyResources();
};
