#pragma once
#include "GameComponent.h"

class GameComponent;

class TriangleComponent : public GameComponent {
protected:
	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode;
	DirectX::XMFLOAT4* points; // Pointer on array
	ID3D11RasterizerState* rastState;
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode;

	UINT strides[1];
	UINT offsets[1];
	D3D11_BUFFER_DESC vertexBufDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	ID3D11Buffer* vb;
	D3D11_BUFFER_DESC indexBufDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	CD3D11_RASTERIZER_DESC rastDesc;
	ID3D11Buffer* ib;
	int pointsAmount;

public:
	TriangleComponent();

	void Initialize();
	void Update();
	void Draw();
	void Reload();
	void DestroyResources();
};

