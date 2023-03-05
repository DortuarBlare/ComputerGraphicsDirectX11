#pragma once
#include "RenderComponent.h"

class RectangleRenderComponent : public RenderComponent {
private:
	void ConfigureRectangle();

public:
	DirectX::XMFLOAT3 extents;

	RectangleRenderComponent();
	RectangleRenderComponent(
		DirectX::SimpleMath::Color fillColor,
		D3D11_FILL_MODE fillMode,
		DirectX::XMFLOAT3 extents
	);

	void Initialize() override;
};