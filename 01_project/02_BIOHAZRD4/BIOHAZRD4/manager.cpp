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
#include "keyboard.h"
#include "scene.h"
#include "scene2d.h"
#include "scene3d.h"
#include "camera.h"
#include "player.h"
#include "model.h"
#include "polygon.h"
#include "debug.h"
#include "light.h"

//=============================================================================
//スタティック変数初期化
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;

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

	m_pCamera = CCamera::Create();
	m_pLight = CLight::Create();
	//TEXTUREのロード
	CPlayer::Load();
	CPolygon::Load();
	CModel::Load();

	//CPlayer::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));
	//CPlayer::Create(D3DXVECTOR3((SCREEN_CENTER_X / 2), SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));
	//CPlayer::Create(D3DXVECTOR3(SCREEN_CENTER_X + (SCREEN_CENTER_X / 2), SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));
	CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR3(40.0f, 0.0f, -40.0f),0);
	CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f, 20.0f), D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 0.0f, -20.0f), 0);
	CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.f, 0.0f, -20.0f));
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CScene::	ReleaseAll();

	CModel::	Unload();
	CPolygon::	Unload();
	CPlayer::	Unload();

	//デバッグの終了
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
	//ライトの終了
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	//カメラの終了
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
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
	m_pCamera->Update();
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

CCamera * CManager::GetCamera(void)
{
	return m_pCamera;
}

CLight * CManager::GetLight(void)
{
	return m_pLight;
}

CDebugProc * CManager::GetDebug(void)
{
	return m_pDebugProc;
}

CInputKeyboard *CManager::GetInput(void)
{
	return m_pInputKeyboard;
}