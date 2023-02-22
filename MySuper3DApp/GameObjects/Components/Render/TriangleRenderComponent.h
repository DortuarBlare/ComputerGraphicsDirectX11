#pragma once
#include "RenderComponent.h"

class RenderComponent;

class TriangleRenderComponent : public RenderComponent {
public:
	TriangleRenderComponent();
	TriangleRenderComponent(D3D11_FILL_MODE fillMode, std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset);
};
