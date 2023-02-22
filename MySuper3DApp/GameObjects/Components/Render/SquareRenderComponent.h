#pragma once
#include "RenderComponent.h"

class SquareRenderComponent : public RenderComponent {
public:
	SquareRenderComponent();
	SquareRenderComponent(D3D11_FILL_MODE fillMode, std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset);
};
