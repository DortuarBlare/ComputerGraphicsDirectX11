#include "pch.h"
#include "RectangleRenderComponent.h"

RectangleRenderComponent::RectangleRenderComponent(
	Color fillColor,
	D3D11_FILL_MODE fillMode,
	XMFLOAT3 extents
) : RenderComponent(fillColor, fillMode) {
	this->extents = extents;
}

RectangleRenderComponent::RectangleRenderComponent(
	LPCWSTR textureFileName,
	Color fillColor,
	D3D11_FILL_MODE fillMode,
	XMFLOAT3 extents
) : RenderComponent(textureFileName, fillColor, fillMode) {
	this->extents = extents;
}

void RectangleRenderComponent::Initialize() {
	ConfigureRectangle();
	RenderComponent::Initialize();
}

void RectangleRenderComponent::ConfigureRectangle() {
	points.insert(points.end(),
		{
			/* Vertex position										*/ /* Vertex color */
			XMFLOAT4(0.0f + extents.x,  0.0f + extents.y, 0.0f, 1.0f), fillColor,
			XMFLOAT4(0.0f - extents.x,  0.0f - extents.y, 0.0f, 1.0f), fillColor,
			XMFLOAT4(0.0f + extents.x,  0.0f - extents.y, 0.0f, 1.0f), fillColor,
			XMFLOAT4(0.0f - extents.x,  0.0f + extents.y, 0.0f, 1.0f), fillColor
		}
	);

	indexes.insert(indexes.end(), { 0, 1, 2, 1, 0, 3 });
}
