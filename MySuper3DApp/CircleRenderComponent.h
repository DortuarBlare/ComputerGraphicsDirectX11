#pragma once
#include "pch.h"
#include "RenderComponent.h"

class CircleRenderComponent : public RenderComponent {
public:
	float radius;
	unsigned int pointsAmount;

	CircleRenderComponent();
	CircleRenderComponent(
		DirectX::SimpleMath::Color fillColor,
		D3D11_FILL_MODE fillMode,
		float radius,
		unsigned int pointsAmount
	);

	void Initialize() override;

	void ConfigureCircle();
};
