//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "player.h"
#include "keyboard.h"
#include "debug.h"

//=============================================================================
//スタティック変数初期化
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CDebugProc*CManager::m_pDebugProc;

//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{
	//レンダリングクラス生成	// 初期化処理	
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, TRUE);
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();

	//TEXTUREのロード
	CPlayer::Load();

	CPlayer::Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	CPlayer::Create(SCREEN_CENTER_X / 2, SCREEN_CENTER_Y);
	CPlayer::Create(SCREEN_CENTER_X + (SCREEN_CENTER_X / 2), SCREEN_CENTER_Y);
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CScene::	ReleaseAll();

	CPlayer::	Unload();

	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
	//キーボードの終了
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	//レンダラーの終了
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	m_pInputKeyboard->Update();
	m_pRenderer->Update();
}
//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

CPlayer *CManager::GetPlayer(void)
{
	return m_pPlayer;
}

CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;	
}

CDebugProc * CManager::GetDebug(void)
{
	return m_pDebugProc;
}

CInputKeyboard *CManager::GetInput(void)
{
	return m_pInputKeyboard;
}