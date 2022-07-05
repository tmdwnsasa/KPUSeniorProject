﻿#pragma once

#include "Timer.h"
#include "Player.h"
#include "Scene.h"

class CGameFramework
{
public:
	CGameFramework();
	~CGameFramework();

	// 게임 프레임워크 복사 방지
	CGameFramework(const CGameFramework& other) = delete;
	CGameFramework& operator=(const CGameFramework& other) = delete;

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void CreateSwapChain();
	void CreateDirect3DDevice();
	void CreateCommandQueueAndList();

	void CreateRtvAndDsvDescriptorHeaps();

	void CreateRenderTargetViews();
	void CreateDepthStencilView();

	void ChangeSwapChainState();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	void WaitForGpuComplete();
	void MoveToNextFrame();

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void AddPlayer();

	CPlayer* GetPlayer() { return m_pPlayer; }
	CScene* GetScene() { return m_pScene; }
	CGameTimer* GetTimer() { return &m_GameTimer; }
	//CPlayer* GetPlayer(int id) { return players[id]; }
	//std::unordered_map<int, CPlayer*>* GetPlayers() { return &players; }

private:
	HINSTANCE					m_hInstance;
	HWND						m_hWnd; 

	int							m_nWndClientWidth;
	int							m_nWndClientHeight;

	IDXGIFactory4* m_pdxgiFactory;
	IDXGISwapChain3* m_pdxgiSwapChain;
	ID3D12Device* m_pd3dDevice;

	bool						m_bMsaa4xEnable = false;
	UINT						m_nMsaa4xQualityLevels = 0;

	static const UINT			m_nSwapChainBuffers = 2;
	UINT						m_nSwapChainBufferIndex;

	ID3D12Resource* m_ppd3dSwapChainBackBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	UINT						m_nRtvDescriptorIncrementSize;

	ID3D12Resource* m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;
	UINT						m_nDsvDescriptorIncrementSize;

	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	ID3D12CommandQueue* m_pd3dCommandQueue;
	ID3D12GraphicsCommandList* m_pd3dCommandList;

	ID3D12Fence* m_pd3dFence;
	UINT64						m_nFenceValues[m_nSwapChainBuffers];
	HANDLE						m_hFenceEvent;

#ifdef _DEBUG
	ID3D12Debug* m_pd3dDebugController;
#endif

	CGameTimer					m_GameTimer;

	CScene* m_pScene;
	CPlayer* m_pPlayer;
	CCamera* m_pCamera;


	POINT						m_ptOldCursorPos;

	_TCHAR						m_pszFrameRate[70];

	//std::unique_ptr<CNetwork> network_manager;
	int send_timing;
	float fps;
};

