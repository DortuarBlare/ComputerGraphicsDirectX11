#include "RectangleRenderComponent.h"

RectangleRenderComponent::RectangleRenderComponent() : RenderComponent() {
	extents = {};
	indeces.insert(indeces.end(), { 0, 1, 2, 1, 0, 3 });
}

RectangleRenderComponent::RectangleRenderComponent(
	DirectX::XMFLOAT4 fillColor,
	D3D11_FILL_MODE fillMode,
	DirectX::XMFLOAT3 extents
) : RenderComponent(fillColor, fillMode, nullptr) {
	this->extents = extents;
	indeces.insert(indeces.end(), { 0, 1, 2, 1, 0, 3 });
}

RectangleRenderComponent::RectangleRenderComponent(
	DirectX::XMFLOAT4 fillColor,
	D3D11_FILL_MODE fillMode,
	std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset,
	DirectX::XMFLOAT3 extents
) : RenderComponent(fillColor, fillMode, renderOffset) {
	this->extents = extents;
	indeces.insert(indeces.end(), { 0, 1, 2, 1, 0, 3 });
}

void RectangleRenderComponent::Initialize() {
	ConfigureRectangle();
	RenderComponent::Initialize();
}

void RectangleRenderComponent::ConfigureRectangle() {
	points.insert(points.end(),
		{
			/* Vertex position																			   */ /* Vertex color */
			DirectX::XMFLOAT4(renderOffset->x + extents.x / 2,  renderOffset->y + extents.y / 2, 0.5f, 1.0f), fillColor,
			DirectX::XMFLOAT4(renderOffset->x - extents.x / 2,  renderOffset->y - extents.y / 2, 0.5f, 1.0f), fillColor,
			DirectX::XMFLOAT4(renderOffset->x + extents.x / 2,  renderOffset->y - extents.y / 2, 0.5f, 1.0f), fillColor,
			DirectX::XMFLOAT4(renderOffset->x - extents.x / 2,  renderOffset->y + extents.y / 2, 0.5f, 1.0f), fillColor
		}
	);
}
