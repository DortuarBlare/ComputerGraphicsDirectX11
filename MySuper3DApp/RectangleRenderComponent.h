#pragma once
#include "RenderComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class RectangleRenderComponent : public RenderComponent {
public:
	XMFLOAT3 extents;

	RectangleRenderComponent() = delete;
	RectangleRenderComponent(
		LPCWSTR textureFileName,
		D3D11_FILL_MODE fillMode,
		XMFLOAT3 extents
	);

	void Initialize() override;
};
