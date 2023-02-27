#include "CircleRenderComponent.h"

CircleRenderComponent::CircleRenderComponent() : RenderComponent() {
	radius = 0.0f;
}

CircleRenderComponent::CircleRenderComponent(
	DirectX::XMFLOAT4 fillColor,
	D3D11_FILL_MODE fillMode,
	std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset,
	float radius
) : RenderComponent(fillColor, fillMode, renderOffset) {
	this->radius = radius;
}

void CircleRenderComponent::Initialize() {
	ConfigureCircle();
	RenderComponent::Initialize();
}

void CircleRenderComponent::ConfigureCircle() {
	int pointsAmount = 30;
	points.push_back(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	points.push_back(fillColor);

	for (int i = 1; i <= pointsAmount; i++) {
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

	for (int i = 1; i <= pointsAmount; i++) {
		if (i == pointsAmount)
			indeces.insert(indeces.end(), { 0, i, 1 });
		else 
			indeces.insert(indeces.end(), { 0, i, i + 1 });
	}

}
