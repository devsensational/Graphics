#include "pch.h"
#include "Engine.h"

void Engine::Init(const WindowInfo& info)
{
	_info = info;
	ResizeWindow(info.width, info.height);

	_viewport = { 0, 0, static_cast<FLOAT>(info.width), static_cast<FLOAT>(info.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, info.width, info.height);

	_device = make_shared<Device>();
	_cmdQueue = make_shared<CommandQueue>();
	_swapChain = make_shared<SwapChain>();
	_rootSignature = make_shared<RootSignature>();

	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(info, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCmdQueue());
	_rootSignature->Init(_device->GetDevice());
}

void Engine::Render()
{
	RenderBegin();

	//TODO : 나머지 물체들을 그려준다

	RenderCommit();
}

void Engine::RenderBegin()
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderCommit()
{
	_cmdQueue->RenderCommit();
}

void Engine::ResizeWindow(int32 width, int32 height) 
{
	_info.width = width;
	_info.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_info.hwnd, 0, 100, 100, width, height, 0);
}