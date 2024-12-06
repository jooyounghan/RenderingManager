#include "pch.h"
#include "PSOObject.h"

using namespace std;

PSOObject::PSOObject(
	ID3D11DepthStencilState* depthStencilState, 
	ID3D11BlendState* blendState, 
	ID3D11RasterizerState* rasterizerState, 
	const vector<ID3D11SamplerState*>& samplerStates,
	const D3D11_PRIMITIVE_TOPOLOGY& topology,
	const vector<shared_ptr<AShader>>& shaders
)
	: m_depthStencilState(depthStencilState), m_blendState(blendState),
	m_rasterizerState(rasterizerState), m_samplerStates(samplerStates),
	m_topology(topology), m_shaders(shaders)
{
}

void PSOObject::ApplyPSOObject(ID3D11DeviceContext* deviceContext)
{
	for (const shared_ptr<AShader>& const shader : m_shaders)
	{
		shader->SetShader(deviceContext);
		shader->SetSamplerState(deviceContext, m_samplerStates);
	}

	deviceContext->IASetPrimitiveTopology(m_topology);
	
	deviceContext->RSSetState(m_rasterizerState);
	deviceContext->OMSetDepthStencilState(m_depthStencilState, 0);

	const FLOAT BlendFactor[4] = { 1.f, 1.f, 1.f, 1.f };
	deviceContext->OMSetBlendState(m_blendState, BlendFactor, 0xFFFFFFFF);

	//Viewport, RTV/DSV ´Â µû·Î!
}

void PSOObject::ResetPSOObject()
{
}
