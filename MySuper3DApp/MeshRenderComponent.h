#pragma once
#include "RenderComponent.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace DirectX;

class MeshRenderComponent : public RenderComponent {
public:
	std::string modelFileName;
	float importScale = 1.0f;

	MeshRenderComponent() = delete;
	MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName);
	MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName, float importScale);

	void Initialize() override;
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};
