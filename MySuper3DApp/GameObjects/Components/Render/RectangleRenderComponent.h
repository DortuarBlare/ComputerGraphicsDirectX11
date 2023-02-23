#pragma once
#include "RenderComponent.h"

class RectangleRenderComponent : public RenderComponent {
public:
	DirectX::XMFLOAT3 extents;

	RectangleRenderComponent();
	RectangleRenderComponent(
		DirectX::XMFLOAT4 fillColor,
		D3D11_FILL_MODE fillMode,
		DirectX::XMFLOAT3 extents
	);
	RectangleRenderComponent(
		DirectX::XMFLOAT4 fillColor,
		D3D11_FILL_MODE fillMode,
		std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset,
		DirectX::XMFLOAT3 extents
	);
	RectangleRenderComponent(
		DirectX::XMFLOAT4 fillColor,
		D3D11_FILL_MODE fillMode,
		DirectX::SimpleMath::Vector4 renderOffset,
		DirectX::XMFLOAT3 extents
	);

	void Initialize() override;

	void ConfigureRectangle();
};
