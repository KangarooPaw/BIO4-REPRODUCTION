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
#include "joystick.h"
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
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputJoystick *CManager::m_pInputJoystick = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CModel *CManager::m_pModel = NULL;
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
	//クラス生成と初期化	
	//レンダラー
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, TRUE);
	//キーボード
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);
	//ゲームパッド
	m_pInputJoystick = new CInputJoystick;
	m_pInputJoystick->Init(hInstance, hWnd);
	//デバッグ
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
	//カメラ
	m_pCamera = CCamera::Create();
	//ライト
	m_pLight = CLight::Create();

	//テクスチャの読み込み
	LoadAll();
	//ポリゴン生成
	CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR3(40.0f, 0.0f, -40.0f),0);
	CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f, 20.0f), D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 0.0f, -20.0f), 0);
	m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();
	//テクスチャの破棄
	UnloadAll();
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
	//ゲームパッドの終了
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
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
	m_pInputJoystick->Update();
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

//=============================================================================
//テクスチャの読み込みまとめ
//=============================================================================
void CManager::LoadAll(void)
{
	CPlayer::Load();
	CPolygon::Load();
	CModel::Load();
}

//=============================================================================
//テクスチャの破棄まとめ
//=============================================================================
void CManager::UnloadAll(void)
{
	CModel::Unload();
	CPolygon::Unload();
	CPlayer::Unload();
}

//=============================================================================
// 受け渡し処理
//=============================================================================
//レンダラー
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;	
}

//キーボード
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//ゲームパッド
CInputJoystick * CManager::GetInputJoystick(void)
{
	return m_pInputJoystick;
}

//カメラ
CCamera * CManager::GetCamera(void)
{
	return m_pCamera;
}

//ライト
CLight * CManager::GetLight(void)
{
	return m_pLight;
}

//プレイヤー
CPlayer *CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//モデル
CModel * CManager::GetModel(void)
{
	return m_pModel;
}

//デバッグ
CDebugProc * CManager::GetDebug(void)
{
	return m_pDebugProc;
}

