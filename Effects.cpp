//***************************************************************************************
// Effects.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "Effects.h"

#pragma region Effect
Effect::Effect(ID3D11Device* device, const std::wstring& filename)
	: mFX(0)
{
	std::ifstream fin(filename, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();
	
	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size, 
		0, device, &mFX));
}

Effect::~Effect()
{
	ReleaseCOM(mFX);
}
#pragma endregion

#pragma region BasicEffect
BasicEffect::BasicEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	Light1Tech    = mFX->GetTechniqueByName("Light1");
	Light2Tech    = mFX->GetTechniqueByName("Light2");
	Light3Tech    = mFX->GetTechniqueByName("Light3");

	Light0TexTech = mFX->GetTechniqueByName("Light0Tex");
	Light1TexTech = mFX->GetTechniqueByName("Light1Tex");
	Light2TexTech = mFX->GetTechniqueByName("Light2Tex");
	Light3TexTech = mFX->GetTechniqueByName("Light3Tex");

	Light0TexAlphaClipTech = mFX->GetTechniqueByName("Light0TexAlphaClip");
	Light1TexAlphaClipTech = mFX->GetTechniqueByName("Light1TexAlphaClip");
	Light2TexAlphaClipTech = mFX->GetTechniqueByName("Light2TexAlphaClip");
	Light3TexAlphaClipTech = mFX->GetTechniqueByName("Light3TexAlphaClip");

	Light1FogTech    = mFX->GetTechniqueByName("Light1Fog");
	Light2FogTech    = mFX->GetTechniqueByName("Light2Fog");
	Light3FogTech    = mFX->GetTechniqueByName("Light3Fog");

	Light0TexFogTech = mFX->GetTechniqueByName("Light0TexFog");
	Light1TexFogTech = mFX->GetTechniqueByName("Light1TexFog");
	Light2TexFogTech = mFX->GetTechniqueByName("Light2TexFog");
	Light3TexFogTech = mFX->GetTechniqueByName("Light3TexFog");

	Light0TexAlphaClipFogTech = mFX->GetTechniqueByName("Light0TexAlphaClipFog");
	Light1TexAlphaClipFogTech = mFX->GetTechniqueByName("Light1TexAlphaClipFog");
	Light2TexAlphaClipFogTech = mFX->GetTechniqueByName("Light2TexAlphaClipFog");
	Light3TexAlphaClipFogTech = mFX->GetTechniqueByName("Light3TexAlphaClipFog");

	WorldViewProj     = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	World             = mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldInvTranspose = mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	TexTransform      = mFX->GetVariableByName("gTexTransform")->AsMatrix();
	EyePosW           = mFX->GetVariableByName("gEyePosW")->AsVector();
	FogColor          = mFX->GetVariableByName("gFogColor")->AsVector();
	FogStart          = mFX->GetVariableByName("gFogStart")->AsScalar();
	FogRange          = mFX->GetVariableByName("gFogRange")->AsScalar();
	DirLights         = mFX->GetVariableByName("gDirLights");
	Mat               = mFX->GetVariableByName("gMaterial");
	DiffuseMap        = mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
}

BasicEffect::~BasicEffect()
{
}
#pragma endregion

#pragma region Effects

 ID3D11InputLayout*						Effects::mInputLayout_PosColor = 0;
 ID3D11InputLayout*						Effects::mInputLayout_PosTex = 0;
 ID3D11InputLayout*						Effects::mInputLayout_PosTexColor = 0;

 ID3DX11Effect*							Effects::mEffectPosColor = 0;
 ID3DX11EffectTechnique*				Effects::mEffectTechPosColor = 0;
 ID3DX11Effect*							Effects::mEffectPosTex = 0;
 ID3DX11EffectTechnique*				Effects::mEffectTechPosTex = 0;
 ID3DX11EffectMatrixVariable*			Effects::mEffectWorldViewProj_PosTex = 0;
 ID3DX11EffectMatrixVariable*			Effects::mEffectWorldViewProj_PosColor = 0;
 ID3DX11EffectShaderResourceVariable*	Effects::mDiffuseMap_PosTex = 0;

 ID3DX11Effect*							Effects::mEffectPosTexColor = 0;
 ID3DX11EffectTechnique*				Effects::mEffectTechPosTexColor = 0;

 ID3DX11EffectMatrixVariable*			Effects::mEffectWorldViewProj_PosTexColor = 0;
 ID3DX11EffectShaderResourceVariable*	Effects::mDiffuseMap_PosTexColor = 0;


 ID3D11RasterizerState*					Effects::mRS = 0;
 ID3D11BlendState*						Effects::mBS = 0;
 ID3D11BlendState*						Effects::TransparentBS = 0;
bool Effects::InitAll(ID3D11Device* device)
{
	//BasicFX = new BasicEffect(device, L"FX/Basic.fxo");
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr;
	hr = D3DX11CompileFromFile(L"FX/effect_pos_color.fx", 0, 0, 0, "fx_5_0", shaderFlags, 0, 0, &compiledShader, &compilationMsgs, 0);
	// compilationMsgs can store errors or warnings.
	if (compilationMsgs != 0)
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		ReleaseCOM(compilationMsgs);
	}
	// Even if there are no compilationMsgs, check to make sure there were no other errors.
	if (FAILED(hr))
	{
		DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
	}
	hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, device, &mEffectPosColor);
	if (FAILED(hr))
	{
		return false;
	}
	// Done with compiled shader.
	ReleaseCOM(compiledShader);
	mEffectTechPosColor = mEffectPosColor->GetTechniqueByName("PosColorTech");
	mEffectWorldViewProj_PosColor = mEffectPosColor->GetVariableByName("gWorldViewProj")->AsMatrix();
	//StaticMesh_DiffuseMap = mEffectPosColor->GetVariableByName("gDiffuseMap")->AsShaderResource();
	D3DX11_PASS_DESC passDesc;
	mEffectTechPosColor->GetPassByIndex(0)->GetDesc(&passDesc);
	hr = device->CreateInputLayout(PosColor, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &mInputLayout_PosColor);
	if (FAILED(hr))
	{
		return false;
	}

	hr = D3DX11CompileFromFile(L"FX/effect_pos_tex.fx", 0, 0, 0, "fx_5_0", shaderFlags, 0, 0, &compiledShader, &compilationMsgs, 0);
	// compilationMsgs can store errors or warnings.
	if (compilationMsgs != 0)
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		ReleaseCOM(compilationMsgs);
	}
	// Even if there are no compilationMsgs, check to make sure there were no other errors.
	if (FAILED(hr))
	{
		DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
	}
	hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, device, &mEffectPosTex);
	if (FAILED(hr))
	{
		return false;
	}
	// Done with compiled shader.
	ReleaseCOM(compiledShader);
	mEffectTechPosTex = mEffectPosTex->GetTechniqueByName("PosTexTech");
	mEffectWorldViewProj_PosTex = mEffectPosTex->GetVariableByName("gWorldViewProj")->AsMatrix();
	mDiffuseMap_PosTex = mEffectPosTex->GetVariableByName("gDiffuseMap")->AsShaderResource();
	//D3DX11_PASS_DESC passDesc;
	mEffectTechPosTex->GetPassByIndex(0)->GetDesc(&passDesc);
	hr = device->CreateInputLayout(PosTex, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &mInputLayout_PosTex);
	if (FAILED(hr))
	{
		return false;
	}

	hr = D3DX11CompileFromFile(L"FX/effect_pos_tex_color.fx", 0, 0, 0, "fx_5_0", shaderFlags, 0, 0, &compiledShader, &compilationMsgs, 0);
	// compilationMsgs can store errors or warnings.
	if (compilationMsgs != 0)
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		ReleaseCOM(compilationMsgs);
	}
	// Even if there are no compilationMsgs, check to make sure there were no other errors.
	if (FAILED(hr))
	{
		DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
	}
	hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, device, &mEffectPosTexColor);
	if (FAILED(hr))
	{
		return false;
	}
	// Done with compiled shader.
	ReleaseCOM(compiledShader);
	mEffectTechPosTexColor = mEffectPosTexColor->GetTechniqueByName("PosTexColorTech");
	mEffectWorldViewProj_PosTexColor = mEffectPosTexColor->GetVariableByName("gWorldViewProj")->AsMatrix();
	mDiffuseMap_PosTexColor = mEffectPosTexColor->GetVariableByName("gDiffuseMap")->AsShaderResource();
	//D3DX11_PASS_DESC passDesc;
	mEffectTechPosTexColor->GetPassByIndex(0)->GetDesc(&passDesc);
	hr = device->CreateInputLayout(PosTexColor, 3, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &mInputLayout_PosTexColor);
	if (FAILED(hr))
	{
		return false;
	}

	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.FrontCounterClockwise = true;
	rasterDesc.DepthClipEnable = true;

	hr = device->CreateRasterizerState(&rasterDesc, &mRS);
	if (FAILED(hr))
	{
		return false;
	}

	D3D11_BLEND_DESC blendDesc = { 0 };
	blendDesc.AlphaToCoverageEnable = true;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = false;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = device->CreateBlendState(&blendDesc, &mBS);
	if (FAILED(hr))
	{
		return false;
	}

	D3D11_BLEND_DESC transparentDesc = { 0 };
	transparentDesc.AlphaToCoverageEnable = false;
	transparentDesc.IndependentBlendEnable = false;

	transparentDesc.RenderTarget[0].BlendEnable = true;
	transparentDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
	transparentDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
	transparentDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	transparentDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	transparentDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = device->CreateBlendState(&transparentDesc, &TransparentBS);
	if (FAILED(hr))
	{
		return false;
	}

	//primitive_type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	return true;
}

void Effects::DestroyAll()
{
	/*SafeDelete(mInputLayout_PosColor);
	SafeDelete(mInputLayout_PosTex);
	SafeDelete(mEffectPosColor);
	SafeDelete(mEffectTechPosColor);
	SafeDelete(mEffectWorldViewProj_PosColor);
	SafeDelete(mEffectPosTex);
	SafeDelete(mEffectTechPosTex);
	SafeDelete(mEffectWorldViewProj_PosTex);

	SafeDelete(mDiffuseMap_PosTex);
	SafeDelete(mRS);
	SafeDelete(mBS);*/
}
#pragma endregion