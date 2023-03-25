#include "pch.h"
#include "MeshRenderComponent.h"

MeshRenderComponent::MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName)
	: RenderComponent(textureFileName, D3D11_FILL_SOLID) {
	this->modelFileName = modelFileName;
}

MeshRenderComponent::MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName, float importScale)
	: RenderComponent(textureFileName, D3D11_FILL_SOLID) {
	this->modelFileName = modelFileName;
	this->importScale = importScale;
}

MeshRenderComponent::MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName, float importScale, Vector3 importTranslation)
	: RenderComponent(textureFileName, D3D11_FILL_SOLID) {
	this->modelFileName = modelFileName;
	this->importScale = importScale;
	this->importTranslation = importTranslation;
}

void MeshRenderComponent::Initialize() {
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(modelFileName, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (!pScene)
		return;

	LoadModel(pScene->mRootNode, pScene);
	
	RenderComponent::Initialize();
}

void MeshRenderComponent::LoadModel(aiNode* rootNode, const aiScene* scene) {
	ProcessNode(rootNode, scene);
}

void MeshRenderComponent::ProcessNode(aiNode* node, const aiScene* scene) {
	for (UINT i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (UINT i = 0; i < node->mNumChildren; i++) 
		ProcessNode(node->mChildren[i], scene);
}

void MeshRenderComponent::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
	for (UINT i = 0; i < mesh->mNumVertices; i++) {
		// Vertex position
		points.push_back(
			{
				mesh->mVertices[i].x * importScale + importTranslation.x,
				mesh->mVertices[i].y * importScale + importTranslation.y,
				mesh->mVertices[i].z * importScale + importTranslation.z,
				1.0f
			}
		);

		// Texture coordinates
		XMFLOAT4 textureCoordinate = {};

		if (mesh->mTextureCoords[0]) {
			textureCoordinate.x = (float)mesh->mTextureCoords[0][i].x;
			textureCoordinate.y = (float)mesh->mTextureCoords[0][i].y;
		}

		points.push_back(textureCoordinate);

		// Normals
		points.push_back(
			{
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z,
				0.0f
			}
		);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indexes.push_back(face.mIndices[j]);
	}
}
