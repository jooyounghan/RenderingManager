#include "pch.h"
#include "BufferManager.h"

using namespace std;

size_t hash<GUID>::operator()(const GUID& Value) const
{
	return size_t();
}

BufferManager::BufferManager()
{
}

BufferManager::~BufferManager()
{
}

GUID BufferManager::RegisterConstantBuffer(
	ID3D11Device* device, 
	const UINT& elementSize, 
	const UINT& arrayCount,
	void* cpuDataIn, 
	const D3D11_USAGE& usage
)
{
	GUID guid = IssueGuid();
	m_guidToRegisteredConstantBuffers.emplace(
		guid, 
		RegisterWithCreateHelper<ConstantBuffer>(
			device, elementSize, arrayCount, cpuDataIn, usage
		));
	return guid;
}

GUID BufferManager::RegisterDynamicBuffer(
	ID3D11Device* device, 
	const UINT& elementSize, 
	const UINT& arrayCount
)
{
	GUID guid = IssueGuid();
	m_guidToRegisteredUploadableBuffers.emplace(
		guid, 
		RegisterWithCreateHelper<DynamicBuffer>(
			device, elementSize, arrayCount
		));
	return guid;
}

GUID BufferManager::RegisterStructureBuffer(
	ID3D11Device* device, 
	const UINT& elementSize, 
	const UINT& arrayCount
)
{
	GUID guid = IssueGuid();
	m_guidToRegisteredUploadableBuffers.emplace(
		guid,
		RegisterWithCreateHelper<StructureBuffer>(
			device, elementSize, arrayCount
		));
	return guid;
}

GUID BufferManager::RegisterBuffer(const std::shared_ptr<ConstantBuffer>& buffer)
{
	GUID guid = IssueGuid();
	m_guidToRegisteredConstantBuffers.emplace(guid, buffer);
	return guid;
}

GUID BufferManager::RegisterBuffer(const std::shared_ptr<AUploadableBuffer>& buffer)
{
	GUID guid = IssueGuid();
	m_guidToRegisteredUploadableBuffers.emplace(guid, buffer);
	return guid;
}

GUID BufferManager::IssueGuid()
{
	GUID guid;
	AssertIfFailed(CoCreateGuid(&guid));
	return guid;
}

template<typename IsInitializableBuffer, typename ...Args>
inline std::shared_ptr<IsInitializableBuffer> BufferManager::RegisterWithCreateHelper(ID3D11Device* device, Args ...args)
{
	shared_ptr<IsInitializableBuffer> buffer = make_shared<IsInitializableBuffer>(args...);
	buffer->Initialize(device);
	return buffer;
}


std::shared_ptr<ConstantBuffer> BufferManager::GetRegisteredConstantBuffer(const GUID& guid)
{
	if (m_guidToRegisteredConstantBuffers.find(guid) != m_guidToRegisteredConstantBuffers.end())
	{
		return m_guidToRegisteredConstantBuffers[guid];
	}
	return nullptr;
}

std::shared_ptr<AUploadableBuffer> BufferManager::GetRegisteredUploadableBuffer(const GUID& guid)
{
	if (m_guidToRegisteredUploadableBuffers.find(guid) != m_guidToRegisteredUploadableBuffers.end())
	{
		return m_guidToRegisteredUploadableBuffers[guid];
	}
	return nullptr;
}

void BufferManager::RequestUpload(const GUID& guid, ID3D11DeviceContext* deviceContext, const UINT& elementSize, const UINT& arrayCount, void* cpuDataIn)
{
	UploadRequestArgs uploadRequestArgs;
	AutoZeroMemory(uploadRequestArgs);

	shared_ptr<AUploadableBuffer> uploadableBuffer = GetRegisteredUploadableBuffer(guid);
	if (uploadableBuffer != nullptr)
	{
		uploadRequestArgs.uploadableBuffer = uploadableBuffer.get();
		uploadRequestArgs.deviceContext = deviceContext;
		uploadRequestArgs.elementSize = elementSize;
		uploadRequestArgs.arrayCount = arrayCount;
		uploadRequestArgs.cpuDataIn = cpuDataIn;

		m_uploadRequestedArgs.emplace_back(move(uploadRequestArgs));
	}
}

void BufferManager::ExecuteUpload()
{
	for (const UploadRequestArgs& uploadRequestedArg : m_uploadRequestedArgs)
	{
		uploadRequestedArg.uploadableBuffer->Upload(
			uploadRequestedArg.deviceContext,
			uploadRequestedArg.elementSize,
			uploadRequestedArg.arrayCount,
			uploadRequestedArg.cpuDataIn
		);
	}
	m_uploadRequestedArgs.clear();
}

