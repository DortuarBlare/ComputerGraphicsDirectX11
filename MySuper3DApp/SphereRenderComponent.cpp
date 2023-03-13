#include "pch.h"
#include "SphereRenderComponent.h"

SphereRenderComponent::SphereRenderComponent(
	D3D11_FILL_MODE fillMode,
	float radius,
	int sliceCount,
	int stackCount,
	Color topColor,
	Color bottomColor
) : RenderComponent({}, fillMode) {
	this->radius = radius;
	this->sliceCount = sliceCount;
	this->stackCount = stackCount;
	this->topColor = topColor;
	this->bottomColor = bottomColor;
}

SphereRenderComponent::SphereRenderComponent(
	LPCWSTR textureFileName,
	float radius,
	int sliceCount,
	int stackCount
) : RenderComponent(textureFileName, D3D11_FILL_SOLID) {
	this->radius = radius;
	this->sliceCount = sliceCount;
	this->stackCount = stackCount;
	this->topColor = { 0.0f, 0.0f, 0.0f };
	this->bottomColor = { 0.0f, 0.0f, 0.0f };
}

SphereRenderComponent::SphereRenderComponent(
	LPCWSTR textureFileName,
	D3D11_FILL_MODE fillMode,
	float radius,
	int sliceCount,
	int stackCount
) : RenderComponent(textureFileName, fillMode) {
	this->radius = radius;
	this->sliceCount = sliceCount;
	this->stackCount = stackCount;
	this->topColor = { 0.0f, 0.0f, 0.0f };
	this->bottomColor = { 0.0f, 0.0f, 0.0f };
}

void SphereRenderComponent::GenerateSphere() {
	points.push_back({ 0.0f, radius, 0.0f, 1.0f }); // Position
	points.push_back({ 0.0f, 0.0f, 0.0f, 0.0f, }); // Texture coordinates
	points.push_back({ 0.0f, 0.0f, 0.0f, 0.0f, }); // Normal

	const float phiStep = XM_PI / static_cast<float>(stackCount);
	const float thetaStep = XM_2PI / static_cast<float>(sliceCount);

	for (int i = 1; i <= stackCount - 1; i++) {
		const float phi = static_cast<float>(i) * phiStep;

		for (int j = 0; j <= sliceCount; j++) {
			const float theta = static_cast<float>(j) * thetaStep;
			Vector4 tempPoint = {};
			Vector4 tempTexCoords = {};

			tempPoint.x = radius * sinf(phi) * cosf(theta);
			tempPoint.y = radius * cosf(phi);
			tempPoint.z = radius * sinf(phi) * sinf(theta);
			tempPoint.w = 1.0f;

			tempTexCoords.x = theta / XM_2PI;
			tempTexCoords.y = phi / XM_2PI;

			points.push_back(tempPoint);
			points.push_back(tempTexCoords);
			points.push_back({ 0.0f, 0.0f, 0.0f, 0.0f, }); // Normal
		}
	}

	points.push_back({ 0.0f, -radius, 0.0f, 1.0f });
	points.push_back({ 0.0f, 1.0f, 0.0f, 0.0f, });
	points.push_back({ 0.0f, 0.0f, 0.0f, 0.0f, }); // Normal

	for (int i = 1; i <= sliceCount; i++) {
		indexes.push_back(0);
		indexes.push_back(i + 1);
		indexes.push_back(i);
	}

	int baseIndex = 1;
	const int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount - 2; i++) {
		for (int j = 0; j < sliceCount; j++) {
			indexes.push_back(baseIndex + i * ringVertexCount + j);
			indexes.push_back(baseIndex + i * ringVertexCount + j + 1);
			indexes.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			indexes.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indexes.push_back(baseIndex + i * ringVertexCount + j + 1);
			indexes.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	const int southPoleIndex = points.size() / 3 - 1;

	baseIndex = southPoleIndex - ringVertexCount;

	for (int i = 0; i < sliceCount; i++) {
		indexes.push_back(southPoleIndex);
		indexes.push_back(baseIndex + i);
		indexes.push_back(baseIndex + i + 1);
	}
}

void SphereRenderComponent::Initialize() {
	GenerateSphere();
	RenderComponent::Initialize();
}

void SphereRenderComponent::ChangeRadius(float radius) {
	/*for (int i = 0; i < points.size(); i += 3) {
		if (i > points.size())
			break;

		points[i].x *= scale;
		points[i].y *= scale;
		points[i].z *= scale;
	}*/

	this->radius = radius;
	points.clear();
	GenerateSphere();
	RenderComponent::Initialize();
}
