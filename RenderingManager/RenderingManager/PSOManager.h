#pragma once
#include "AShader.h"
#include "PSOObject.h"
#include <unordered_map>

class PSOManager
{
public:
	PSOManager(ID3D11Device* device);

protected:
	ID3D11Device* m_deviceCached = nullptr;

protected:
	std::unordered_map<std::string, std::shared_ptr<AShader>> m_registeredShaders;

public:
	void RegisterShader(const std::string& shaderName, const std::shared_ptr<AShader>& shader);
	std::shared_ptr<AShader> GetRegisteredShader(const std::string& shaderName);

protected:
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11DepthStencilState>> m_registeredDepthStencilStates;
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11BlendState>> m_registeredBlendStates;
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11RasterizerState>> m_registeredRasterizerStates;
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11SamplerState>> m_registeredSamplerStates;

public:
	void RegisterDepthStencilState(
		const std::string& stateName,
		const BOOL& depthEnable,
		const D3D11_COMPARISON_FUNC& depthComparisonFunc,
		const BOOL& stencilEnable
	);
	void RegisterBlendState(
		const std::string& stateName,
		const BOOL& AlphaToCoverageEnable,
		const BOOL& IndependentBlendEnable, 
		const std::vector<D3D11_RENDER_TARGET_BLEND_DESC>& renderTargetBlendDescs
	);
	void RegisterRasterizerState(
		const std::string& stateName,
		const D3D11_FILL_MODE& fillMode,
		const D3D11_CULL_MODE& cullMode,
		const DXGI_SAMPLE_DESC& sampleDesc
	);
	void RegisterSamplerState(
		const std::string& stateName,
		const D3D11_TEXTURE_ADDRESS_MODE& textureAddressModeU,
		const D3D11_TEXTURE_ADDRESS_MODE& textureAddressModeV,
		const D3D11_TEXTURE_ADDRESS_MODE& textureAddressModeW,
		const D3D11_COMPARISON_FUNC& comparisonFunc,
		const D3D11_FILTER& filter
	);

public:
	ID3D11DepthStencilState* GetDepthStencilState(const std::string& stateName);
	ID3D11BlendState* GetBlendState(const std::string& stateName);
	ID3D11RasterizerState* GetRasterizerState(const std::string& stateName);
	ID3D11SamplerState* GetSamplerState(const std::string& stateName);
};

