#pragma once
#include "RenderComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class RectangleRenderComponent : public RenderComponent {
private:
	void ConfigureRectangle();

public:
	XMFLOAT3 extents;

	RectangleRenderComponent() = delete;
	RectangleRenderComponent(
		Color fillColor,
		D3D11_FILL_MODE fillMode,
		XMFLOAT3 extents
	);
	RectangleRenderComponent(
		LPCWSTR textureFileName,
		Color fillColor,
		D3D11_FILL_MODE fillMode,
		XMFLOAT3 extents
	);

	void Initialize() override;
};
