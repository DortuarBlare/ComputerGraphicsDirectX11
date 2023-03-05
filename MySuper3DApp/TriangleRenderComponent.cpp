#include "pch.h"
#include "TriangleRenderComponent.h"

TriangleRenderComponent::TriangleRenderComponent() : RenderComponent() {
	indexes.insert(indexes.end(), { 0, 1, 2 });
}

TriangleRenderComponent::TriangleRenderComponent(
	DirectX::SimpleMath::Color fillColor,
	D3D11_FILL_MODE fillMode
) : RenderComponent(fillColor, fillMode) {
	indexes.insert(indexes.end(), { 0, 1, 2 });
}
