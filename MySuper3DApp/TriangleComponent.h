#pragma once
#include "GameComponent.h"

class GameComponent;

class TriangleComponent : public GameComponent {
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderByteCode;
	std::shared_ptr<CD3D11_RASTERIZER_DESC> rastDesc;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rastState;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderByteCode;

	std::shared_ptr<D3D11_BUFFER_DESC> vertexBufDesc;
	std::shared_ptr<D3D11_SUBRESOURCE_DATA> vertexData;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuf;

	std::shared_ptr<D3D11_BUFFER_DESC> indexBufDesc;
	std::shared_ptr<D3D11_SUBRESOURCE_DATA> indexData;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuf;

	std::shared_ptr<D3D11_BUFFER_DESC> constBufDesc;
	std::shared_ptr<D3D11_SUBRESOURCE_DATA> constData;
	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuf; // For render offset
	std::shared_ptr<DirectX::SimpleMath::Vector4> offset; // For offset of rendering object

	std::vector<int> indeces; // Fill before Initialize()

	UINT strides[1];
	UINT offsets[1];

public:
	std::vector<DirectX::XMFLOAT4> points; // Fill before Initialize()

	TriangleComponent(std::shared_ptr<DirectX::SimpleMath::Vector4> offset);

	void Initialize();
	void Update();
	void Draw();
	void Reload();
	void DestroyResources();
};
