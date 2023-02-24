#include "TriangleRenderComponent.h"

TriangleRenderComponent::TriangleRenderComponent() : RenderComponent() {
	indeces.insert(indeces.end(), { 0, 1, 2 });
}

TriangleRenderComponent::TriangleRenderComponent(
	DirectX::XMFLOAT4 fillColor,
	D3D11_FILL_MODE fillMode,
	std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset
) : RenderComponent(fillColor, fillMode, renderOffset) {
	indeces.insert(indeces.end(), { 0, 1, 2 });
}