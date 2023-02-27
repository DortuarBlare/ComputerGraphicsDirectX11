#pragma once
#include "RenderComponent.h"

class CircleRenderComponent : public RenderComponent {
public:
	float radius;

	CircleRenderComponent();
	CircleRenderComponent(
		DirectX::XMFLOAT4 fillColor,
		D3D11_FILL_MODE fillMode,
		std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset,
		float radius
	);

	void Initialize() override;

	void ConfigureCircle();
};
