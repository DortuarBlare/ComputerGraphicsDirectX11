#pragma once
#include "pch.h"
#include "RenderComponent.h"

using namespace DirectX::SimpleMath;

class CircleRenderComponent : public RenderComponent {
public:
	float radius;
	unsigned int pointsAmount;

	CircleRenderComponent() = delete;
	CircleRenderComponent(
		Color fillColor,
		D3D11_FILL_MODE fillMode,
		float radius,
		unsigned int pointsAmount
	);
	CircleRenderComponent(
		LPCWSTR textureFileName,
		Color fillColor,
		D3D11_FILL_MODE fillMode,
		float radius,
		unsigned int pointsAmount
	);

	void Initialize() override;

	void ConfigureCircle();
};
