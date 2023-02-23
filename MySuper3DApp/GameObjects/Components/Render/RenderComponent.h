#pragma once
#include "../GameObjectComponent.h"

class RenderComponent : public GameObjectComponent {
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderByteCode;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderByteCode;

	std::shared_ptr<CD3D11_RASTERIZER_DESC> rastDesc;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rastState;

	std::shared_ptr<D3D11_BUFFER_DESC> vertexBufDesc;
	std::shared_ptr<D3D11_SUBRESOURCE_DATA> vertexData;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuf;

	std::shared_ptr<D3D11_BUFFER_DESC> indexBufDesc;
	std::shared_ptr<D3D11_SUBRESOURCE_DATA> indexData;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuf;

	std::shared_ptr<D3D11_BUFFER_DESC> constBufDesc;
	std::shared_ptr<D3D11_SUBRESOURCE_DATA> constData;
	Microsoft::WRL::ComPtr<ID3D11Buffer> constBuf;

	std::vector<int> indeces;
	std::vector<DirectX::XMFLOAT4> points;

	DirectX::XMFLOAT4 fillColor;
	D3D11_FILL_MODE fillMode;
	std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset; // For offset of rendering object

	UINT strides[1];
	UINT offsets[1];

public:
	RenderComponent();
	RenderComponent(
		DirectX::XMFLOAT4 fillColor,
		D3D11_FILL_MODE fillMode,
		std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset
	);
	RenderComponent(
		DirectX::XMFLOAT4 fillColor,
		D3D11_FILL_MODE fillMode,
		DirectX::SimpleMath::Vector4 renderOffset
	);

	virtual void Initialize();
	void Update();
	void FixedUpdate();
	void Draw();
	void Reload();
	void DestroyResources();
};
