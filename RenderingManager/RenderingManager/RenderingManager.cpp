#include "pch.h"
#include "RenderingManager.h"

using namespace std;

void RenderingManager::Render(ID3D11DeviceContext* deviceContext)
{
	for (const auto& optionToRenderingArgs : m_optionsToRenderables)
	{
		const SRenderingOption& option = optionToRenderingArgs.first;
		const vector<IRenderable*>& renderables = optionToRenderingArgs.second;

		option.psoObject->ApplyPSOObject(deviceContext, option.renderTargetViews, option.depthStencilView, option.viewable);
		for (const IRenderable* const& renderable : renderables)
		{

		}
	}
}
