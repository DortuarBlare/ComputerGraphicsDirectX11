#pragma once
#include "RenderComponent.h"

class RenderComponent;

class TriangleRenderComponent : public RenderComponent {
public:
	TriangleRenderComponent();
	TriangleRenderComponent(
		DirectX::SimpleMath::Color fillColor,
		D3D11_FILL_MODE fillMode
	);
};
