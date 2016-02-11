#include "ProjectClass.h"

class Project {
void onInit(HWND hWnd)
{
	loadPipeline(hWnd);
	loadAssets();
}


void loadPipeline(HWND hWnd)
{
	//Vytvoøení popisovaèe SwapChainu

	DXGI_SWAP_CHAIN_DESC descSwapChain;
	ZeroMemory(&descSwapChain, sizeof(descSwapChain));
	descSwapChain.BufferCount = 2;
	descSwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descSwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	descSwapChain.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	descSwapChain.OutputWindow = hWnd;
	descSwapChain.SampleDesc.Count = 1;
	descSwapChain.Windowed = TRUE;

	//Vytvoøení zobrazovacího zaøízení

	HRESULT hardware_driver = CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		deviceFlags,
		D3D_FEATURE_LEVEL_9_1,
		D3D12_SDK_VERSION,
		&descSwapChain,
		IID_PPV_ARGS(mSwapChain.GetAddressOf()),
		IID_PPV_ARGS(mDevice.GetAddressOf()),
		IID_PPV_ARGS(mCommandQueue.GetAddressOf())
		);

	if (!SUCCEEDED(hardware_driver)) {
		CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_WARP,
			deviceFlags,
			D3D_FEATURE_LEVEL_9_1,
			D3D12_SDK_VERSION,
			&descSwapChain,
			IID_PPV_ARGS(mSwapChain.GetAddressOf()),
			IID_PPV_ARGS(mDevice.GetAddressOf()),
			IID_PPV_ARGS(mCommandQueue.GetAddressOf())
			);
	}

	//
	// create the command allocator object
	//

	mDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(mCommandAllocator.GetAddressOf()));
}

void loadAssets()
{
	//
	// handles to vert and pixel shaders
	//

	ComPtr<ID3DBlob> blobShaderVert, blobShaderPixel;

	//
	// compile shaders
	//

	D3DCompileFromFile(L"shaders.hlsl", nullptr, nullptr, "VShader", "vs_5_0", 0, 0, blobShaderVert.GetAddressOf(), nullptr);
	D3DCompileFromFile(L"shaders.hlsl", nullptr, nullptr, "PShader", "ps_5_0", 0, 0, blobShaderPixel.GetAddressOf(), nullptr);

	//
	// create input layout
	//

	D3D12_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//
	// create an empty root signature
	//

	ComPtr<ID3DBlob> pOutBlob, pErrorBlob;
	D3D12_ROOT_SIGNATURE_DESC descRootSignature;
	descRootSignature.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	D3D12SerializeRootSignature(&descRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, pOutBlob.GetAddressOf(), pErrorBlob.GetAddressOf());
	mDevice->CreateRootSignature(0, pOutBlob->GetBufferPointer(), pOutBlob->GetBufferSize(), IID_PPV_ARGS(mRootSignature.GetAddressOf()));

	//
	// create a PSO description
	//

	D3D12_GRAPHICS_PIPELINE_STATE_DESC descPso;
	ZeroMemory(&descPso, sizeof(descPso));
	descPso.InputLayout = { layout, numElements };
	descPso.pRootSignature = mRootSignature.Get();
	descPso.VS = { reinterpret_cast<BYTE*>(blobShaderVert->GetBufferPointer()), blobShaderVert->GetBufferSize() };
	descPso.PS = { reinterpret_cast<BYTE*>(blobShaderPixel->GetBufferPointer()), blobShaderPixel->GetBufferSize() };
	descPso.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	descPso.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	descPso.DepthStencilState.DepthEnable = FALSE;
	descPso.DepthStencilState.StencilEnable = FALSE;
	descPso.SampleMask = UINT_MAX;
	descPso.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	descPso.NumRenderTargets = 1;
	descPso.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	descPso.SampleDesc.Count = 1;

	//
	// create the actual PSO
	//

	mDevice->CreateGraphicsPipelineState(&descPso, IID_PPV_ARGS(mPSO.GetAddressOf()));

	//
	// create descriptor heap
	//

	D3D12_DESCRIPTOR_HEAP_DESC descHeap = {};
	descHeap.NumDescriptors = 1;
	descHeap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	descHeap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	mDevice->CreateDescriptorHeap(&descHeap, IID_PPV_ARGS(mDescriptorHeap.GetAddressOf()));

	//
	// create command list
	//

	mDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, mCommandAllocator.Get(), mPSO.Get(), IID_PPV_ARGS(mCommandList.GetAddressOf()));

	//
	// create backbuffer/rendertarget
	//

	mSwapChain->GetBuffer(0, IID_PPV_ARGS(mRenderTarget.GetAddressOf()));
	mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	//
	// set the viewport
	//

	mViewPort =
	{
		0.0f,
		0.0f,
		static_cast<float>(mWidth),
		static_cast<float>(mHeight),
		0.0f,
		1.0f
	};

	//
	// create scissor rectangle
	//

	mRectScissor = { 0, 0, mWidth, mHeight };

	//
	// create geometry for a triangle
	//

	VERTEX triangleVerts[] =
	{
		{ 0.0f, 0.5f, 0.0f,{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ 0.45f, -0.5, 0.0f,{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ -0.45f, -0.5f, 0.0f,{ 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	//
	// actually create the vert buffer
	// Note: using upload heaps to transfer static data like vert buffers is not recommended.
	// Every time the GPU needs it, the upload heap will be marshalled over.  Please read up on Default Heap usage.
	// An upload heap is used here for code simplicity and because there are very few verts to actually transfer
	//

	mDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(3 * sizeof(VERTEX)),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,    // Clear value
		IID_PPV_ARGS(mBufVerts.GetAddressOf()));

	//
	// copy the triangle data to the vertex buffer
	//

	UINT8* dataBegin;
	mBufVerts->Map(0, nullptr, reinterpret_cast<void**>(&dataBegin));
	memcpy(dataBegin, triangleVerts, sizeof(triangleVerts));
	mBufVerts->Unmap(0, nullptr);

	//
	// create vertex buffer view
	//

	mDescViewBufVert.BufferLocation = mBufVerts->GetGPUVirtualAddress();
	mDescViewBufVert.StrideInBytes = sizeof(VERTEX);
	mDescViewBufVert.SizeInBytes = sizeof(triangleVerts);

	//
	// create fencing object
	//

	mDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(mFence.GetAddressOf()));
	mCurrentFence = 1;

	//
	// close the command list and use it to execute the initial GPU setup
	//

	mCommandList->Close();
	ID3D12CommandList* ppCommandLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	//
	// create event handle
	//

	mHandleEvent = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);

	//
	// wait for the command list to execute; we are reusing the same command list in our main loop but for now, 
	// we just want to wait for setup to complete before continuing
	//

	waitForGPU();
}

void onUpdate()
{
}

void onRender()
{
	//
	// record all the commands we need to render the scene into the command list
	//

	populateCommandLists();

	//
	// execute the command list
	//

	ID3D12CommandList* ppCommandLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	//
	// swap the back and front buffers
	//

	mSwapChain->Present(1, 0);
	mIndexLastSwapBuf = (1 + mIndexLastSwapBuf) % cNumSwapBufs;
	mSwapChain->GetBuffer(mIndexLastSwapBuf, IID_PPV_ARGS(mRenderTarget.ReleaseAndGetAddressOf()));
	mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	//
	// wait and reset everything
	//

	waitForGPU();
}

void populateCommandLists()
{
	//
	// command list allocators can be only be reset when the associated command lists have finished execution on the GPU; 
	// apps should use fences to determine GPU execution progress
	//

	mCommandAllocator->Reset();

	//
	// HOWEVER, when ExecuteCommandList() is called on a particular command list, that command list can then be reset 
	// anytime and must be before rerecording
	//

	mCommandList->Reset(mCommandAllocator.Get(), mPSO.Get());

	//
	// set the graphics root signature
	//

	mCommandList->SetGraphicsRootSignature(mRootSignature.Get());

	//
	// set the viewport and scissor rectangle
	//

	mCommandList->RSSetViewports(1, &mViewPort);
	mCommandList->RSSetScissorRects(1, &mRectScissor);

	//
	// indicate this resource will be in use as a render target
	//

	setResourceBarrier(mCommandList.Get(), mRenderTarget.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	//
	// record commands
	//

	float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	mCommandList->ClearRenderTargetView(mDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), clearColor, nullptr, 0);
	mCommandList->OMSetRenderTargets(&mDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), true, 1, nullptr);
	mCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mCommandList->IASetVertexBuffers(0, &mDescViewBufVert, 1);
	mCommandList->DrawInstanced(3, 1, 0, 0);

	//
	// indicate that the render target will now be used to present when the command list is done executing
	//

	setResourceBarrier(mCommandList.Get(), mRenderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	//
	// all we need to do now is close the command list before executing it
	//

	mCommandList->Close();
}


void waitForGPU()
{
	//
	// signal and increment the fence value
	//

	const UINT64 fence = mCurrentFence;
	mCommandQueue->Signal(mFence.Get(), fence);
	mCurrentFence++;

	//
	// Let the previous frame finish before continuing
	//

	if (mFence->GetCompletedValue() < fence)
	{
		mFence->SetEventOnCompletion(fence, mHandleEvent);
		WaitForSingleObject(mHandleEvent, INFINITE);
	}
}

void setResourceBarrier(ID3D12GraphicsCommandList* commandList, ID3D12Resource* resource, UINT stateBefore, UINT stateAfter)
{
	D3D12_RESOURCE_BARRIER descBarrier = {};

	descBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	descBarrier.Transition.pResource = resource;
	descBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	descBarrier.Transition.StateBefore = stateBefore;
	descBarrier.Transition.StateAfter = stateAfter;

	commandList->ResourceBarrier(1, &descBarrier);
}

void onDestroy()
{
	//
	// wait for the GPU to be done with all resources
	//

	waitForGPU();

	mSwapChain->SetFullscreenState(FALSE, nullptr);

	CloseHandle(mHandleEvent);
}

};