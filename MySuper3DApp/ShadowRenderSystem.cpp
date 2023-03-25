#include "pch.h"
#include "ShadowRenderSystem.h"

ShadowRenderSystem::ShadowRenderSystem() {
	D3D11_TEXTURE2D_DESC textureDesc = {};
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	textureDesc.Width = Game::Instance()->renderSystem->display->GetClientWidth();
	textureDesc.Height = Game::Instance()->renderSystem->display->GetClientHeight();
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	auto result = Game::Instance()->renderSystem->device->CreateTexture2D(
		&textureDesc,
		NULL,
		lightDepthBufferTexture.GetAddressOf()
	);

	if (FAILED(result))
		return;

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc = {};
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	result = Game::Instance()->renderSystem->device->CreateRenderTargetView(
		lightDepthBufferTexture.Get(),
		&renderTargetViewDesc,
		lightDepthBufferRenderTargetView.GetAddressOf()
	);

	if (FAILED(result))
		return;

	CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R32G32B32A32_FLOAT);
	result = Game::Instance()->renderSystem->device->CreateShaderResourceView(
		lightDepthBufferTexture.Get(),
		&srvDesc,
		textureResourceView.GetAddressOf()
	);

	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = static_cast<float>(1024);
	depthStencilDesc.Height = static_cast<float>(1024);
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	result = Game::Instance()->renderSystem->device->CreateTexture2D(
		&depthStencilDesc,
		NULL,
		depthStencilBuffer.GetAddressOf()
	);

	if (FAILED(result)) {
		std::cout << "Failed to create depth stencil buffer" << std::endl;
		return;
	}

	result = Game::Instance()->renderSystem->device->CreateDepthStencilView(
		depthStencilBuffer.Get(),
		NULL,
		depthStencilView.GetAddressOf()
	);

	if (FAILED(result)) {
		std::cout << "Failed to create depth stencil view" << std::endl;
		return;
	}


	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.DepthClipEnable = true;

	result = Game::Instance()->renderSystem->device->CreateRasterizerState(&rastDesc, rastState.GetAddressOf());


	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	result = Game::Instance()->renderSystem->device->CreateDepthStencilState(
		&depthStencilStateDesc,
		depthStencilState.GetAddressOf()
	);


	ID3DBlob* errorPixelCode = nullptr;
	ID3DBlob* errorVertexCode = nullptr;
	ID3DBlob* pixelShaderByteCode = nullptr;
	ID3DBlob* vertexShaderByteCode = nullptr;

	// Compile pixel shader
	result = D3DCompileFromFile(
		L"./Shaders/DepthShader.hlsl",
		nullptr /*macros*/,
		nullptr /*include*/,
		"PSMain",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pixelShaderByteCode,
		&errorPixelCode
	);

	// Compile vertex shader
	result = D3DCompileFromFile(
		L"./Shaders/DepthShader.hlsl",
		nullptr /*macros*/,
		nullptr /*include*/,
		"VSMain",
		"vs_5_0", // Shader target (Pixel / Vertex)
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // Different flags (for example code translation)
		0,
		&vertexShaderByteCode,
		&errorVertexCode
	);

	if (FAILED(result)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
			MessageBox(Game::Instance()->renderSystem->display->GetHWnd(), L"SimpleShader.hlsl", L"Missing Shader File", MB_OK);

		return;
	}

	Game::Instance()->renderSystem->device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr,
		pixelShader.GetAddressOf()
	);

	Game::Instance()->renderSystem->device->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr,
		vertexShader.GetAddressOf()
	);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION", // HLSL semantic associated with this element in a shader input-signature
			0, // Semantic index modifies a semantic, with an integer index number
			DXGI_FORMAT_R32G32B32A32_FLOAT, // Data type of the element data
			0, // Integer value that identifies the input-assembler. Valid values are between 0 and 15
			0, // Offset (in bytes) from the start of the vertex (Optional)
			D3D11_INPUT_PER_VERTEX_DATA, // Identifies the input data class for a single input slot
			0 // The number of instances to draw using the same per-instance data before advancing in the buffer by one element
		},
		D3D11_INPUT_ELEMENT_DESC {
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		D3D11_INPUT_ELEMENT_DESC {
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	Game::Instance()->renderSystem->device->CreateInputLayout(
		inputElements,
		std::size(inputElements),
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		layout.GetAddressOf()
	);
}

void ShadowRenderSystem::Update() {

}

void ShadowRenderSystem::PrepareFrame() {
	Game::Instance()->renderSystem->context->OMSetRenderTargets(
		1,
		lightDepthBufferRenderTargetView.GetAddressOf(),
		depthStencilView.Get()
	);

	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Game::Instance()->renderSystem->context->ClearRenderTargetView(lightDepthBufferRenderTargetView.Get(), bgcolor);
	Game::Instance()->renderSystem->context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void ShadowRenderSystem::DrawInternal(std::vector<std::shared_ptr<GameObject>>& gameObjects) {
	for (auto& gameObject : gameObjects)
		gameObject->Draw(); // ¬место Draw что-то вроде DrawShadow
}

void ShadowRenderSystem::EndFrame() {
	Game::Instance()->renderSystem->context->OMSetRenderTargets(0, nullptr, nullptr);
}

void ShadowRenderSystem::Draw(std::vector<std::shared_ptr<GameObject>>& gameObjects) {
	PrepareFrame();
	DrawInternal(gameObjects);
	EndFrame();
}
