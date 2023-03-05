#include "pch.h"
#include "CircleRenderComponent.h"

CircleRenderComponent::CircleRenderComponent() : RenderComponent() {
	radius = 0.0f;
	pointsAmount = 0;
}

CircleRenderComponent::CircleRenderComponent(
	DirectX::SimpleMath::Color fillColor,
	D3D11_FILL_MODE fillMode,
	float radius,
	unsigned int pointsAmount
) : RenderComponent(fillColor, fillMode) {
	this->radius = radius;
	this->pointsAmount = pointsAmount;
}

void CircleRenderComponent::Initialize() {
	ConfigureCircle();
	RenderComponent::Initialize();
}

void CircleRenderComponent::ConfigureCircle() {
	points.push_back(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	points.push_back(fillColor);

	for (unsigned int i = 1; i <= pointsAmount; i++) {
		points.push_back(
			DirectX::XMFLOAT4(
				radius * DirectX::XMScalarSin(DirectX::XM_PI * 2 * (static_cast<float>(i) / pointsAmount)),
				radius * DirectX::XMScalarCos(DirectX::XM_PI * 2 * (static_cast<float>(i) / pointsAmount)),
				0.0f,
				1.0f
			)
		);
		points.push_back(fillColor);
	}

	for (unsigned int i = 1; i < pointsAmount; i++) {
		indexes.insert(indexes.end(), { 0, i, i + 1 });
	}
	indexes.insert(indexes.end(), { 0, pointsAmount, 1 });
}
