#pragma once
#include "RenderComponent.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace DirectX;

class MeshRenderComponent : public RenderComponent {
public:
	std::string modelFileName;

	MeshRenderComponent() = delete;
	MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName);

	void Initialize() override;
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};
