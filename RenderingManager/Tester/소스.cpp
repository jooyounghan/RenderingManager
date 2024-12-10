#include "BufferManager.h"
#include "SRVOption.h"
#include "RTVOption.h"
#include "UAVOption.h"
#include "DSVOption.h"
#include "Texture2DInstance.h"
#include "VertexShader.h"
#include "PSOManager.h"

int main()
{
	Texture2DInstance<SRVOption, RTVOption, UAVOption> test1(0, 0, 0, std::vector<std::vector<uint8_t>>(), std::vector<UINT>(), D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ, D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS, D3D11_USAGE::D3D11_USAGE_DEFAULT, DXGI_FORMAT::DXGI_FORMAT_B4G4R4A4_UNORM, nullptr, nullptr);
	SRVOption* test2 = &test1;
	
	test1.GetSRV();
	test1.GetTexture2D();



	PSOManager test(nullptr);
	test.RegisterVertexShader("", {}, L"", "", "", nullptr);

	VertexShader vs({});
	vs.CreateShader(L"", "", "", nullptr);

	BufferManager bufferManager;
	GUID guid =	bufferManager.RegisterConstantBuffer(nullptr, 0, 0, nullptr);


	return 0;
}