#pragma once
#include "ITextureOption.h"



template<typename ...IsTextureOption>
class Texture2DInstance : public IsTextureOption...
{
public:
	Texture2DInstance(ID3D11Device* device);

public:
	static D3D11_BIND_FLAG GetBindFlags()
	{
		return (D3D11_BIND_FLAG)(IsTextureOption::GetBindFlag() | ...);
	};

public:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture2D;

private:
	virtual void InitializeByOption(ID3D11Resource* resource, ID3D11Device* device) override;
};

template<typename ...IsTextureOption>
inline Texture2DInstance<IsTextureOption...>::Texture2DInstance(ID3D11Device* device)
{


	InitializeByOption(m_texture2D.Get(), device);
}

template<typename ...IsTextureOption>
inline void Texture2DInstance<IsTextureOption...>::InitializeByOption(ID3D11Resource* resource, ID3D11Device* device)
{
	(IsTextureOption::InitializeByOption(resource, device), ...);
}

