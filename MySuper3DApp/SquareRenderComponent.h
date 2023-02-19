#pragma once
#include "TriangleRenderComponent.h"
class SquareRenderComponent : public TriangleRenderComponent {
public:
	SquareRenderComponent();
	SquareRenderComponent(std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset);
};
