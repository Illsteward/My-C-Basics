#pragma once

#include <d3d12.h>
#include <d3d12sdklayers.h>
#include <wrl\client.h> //Obsahuje Component Object Model Pointer (ComPtr)

using namespace Microsoft::WRL;

class Project
{
public:

	///<SwapChain>
	///Promìnné pro úèely Swap Chainu

	int mIndexLastSwapBuf = 0;
	int cNumSwapBufs = 2;
	ComPtr<IDXGISwapChain> mSwapChain;

	///</SwapChain>

	///<VertexDefinition>
	///Obsahuje definici 3D bodu

	struct VERTEX { FLOAT X, Y, Z; FLOAT Color[4]; };

	///</VertexDefinition>

	///<PipelineObjects>
	///Definice objektù DX12 pipeline

	D3D12_VIEWPORT mViewPort;
	D3D12_RECT mRectScissor;

	ComPtr<ID3D12Device> mDevice;
	ComPtr<ID3D12Resource> mRenderTarget;
	ComPtr<ID3D12CommandAllocator> mCommandAllocator;
	ComPtr<ID3D12CommandQueue> mCommandQueue;
	ComPtr<ID3D12RootSignature> mRootSignature;
	ComPtr<ID3D12DescriptorHeap> mDescriptorHeap;

	///</PipelineObjects>

	///<FenceObjects>
	///Objekty pro použití synchronizaèního plotu

	ComPtr<ID3D12Fence> mFence;
	UINT64 mCurrentFence;
	HANDLE mHandleEvent;

	///</FenceObjects>

	///<AssetObjects>
	///Objekty pro zdroje

	ComPtr<ID3D12PipelineState> mPSO;
	ComPtr<ID3D12GraphicsCommandList> mCommandList;
	ComPtr<ID3D12Resource> mBufVerts;

	///<AssetObjects>

	D3D12_VERTEX_BUFFER_VIEW mDescViewBufVert;

	void onInit(HWND hWnd);

	void loadPipeline(HWND hWnd);

	static HRESULT CreateDeviceAndSwapChain(
		_In_opt_ IDXGIAdapter* pAdapter,
		D3D_DRIVER_TYPE DriverType,
		D3D_FEATURE_LEVEL MinimumFeatureLevel,
		UINT SDKVersion,
		_In_opt_ CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
		_In_ REFIID riidSwapchain,
		_COM_Outptr_opt_ void** ppSwapChain,
		_In_ REFIID riidDevice,
		_COM_Outptr_opt_ void** ppDevice,
		_In_ REFIID riidQueue,
		_COM_Outptr_opt_ void **ppQueue
		)
	{
		ComPtr<ID3D12Device> pDevice;
		ComPtr<IDXGIFactory> pDxgiFactory;
		ComPtr<IDXGISwapChain> pDxgiSwapChain;
		ComPtr<ID3D12CommandQueue> pQueue;
		//
		// create the D3D 12 device
		//

		HRESULT hr = D3D12CreateDevice(
			pAdapter,
			MinimumFeatureLevel,
			__uuidof(ID3D12Device),
			IID_PPV_ARGS(&pDevice)
			);
		if (FAILED(hr)) { return hr; }

		D3D12_COMMAND_QUEUE_DESC queueDesc;
		ZeroMemory(&queueDesc, sizeof(queueDesc));
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		hr = pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pQueue));

		hr = CreateDXGIFactory1(IID_PPV_ARGS(&pDxgiFactory));
		if (FAILED(hr)) { return hr; }

		// 
		//  create the swap chain 
		//

		DXGI_SWAP_CHAIN_DESC LocalSCD = *pSwapChainDesc;
		hr = pDxgiFactory->CreateSwapChain(
			pQueue.Get(), // Swap chain needs the queue so it can force a flush on it
			&LocalSCD,
			&pDxgiSwapChain
			);
		if (FAILED(hr)) { return hr; }

		//
		// get the required pointers to the device, queue and swap chain
		//

		hr = pDevice.Get()->QueryInterface(riidDevice, ppDevice);
		if (FAILED(hr)) { return hr; }

		hr = pQueue.Get()->QueryInterface(riidQueue, ppQueue);
		if (FAILED(hr)) { return hr; }

		hr = pDxgiSwapChain.Get()->QueryInterface(riidSwapchain, ppSwapChain);
		if (FAILED(hr))
		{
			reinterpret_cast<IUnknown*>(*ppDevice)->Release();
			return hr;
		}

		return S_OK;
	}



};