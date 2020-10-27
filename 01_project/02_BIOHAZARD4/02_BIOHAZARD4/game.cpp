//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
//#include "time.h"
//#include "sound.h"
//#include "ui.h"
#include "mode.h"
#include "player.h"
#include "enemy.h"
#include"polygon.h"
#include "camera.h"
#include "light.h"
#include "scene.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame()
{
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CGame::Init(void)
{
	//カメラ
	CManager::CreateCamera();

	//ライト
	CManager::CreateLight();

	//ポリゴン生成
	CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 0.0f, -40.0f), 0);
	CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f, 20.0f), D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 0.0f, -20.0f), 0);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 100.0f));

	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 100.0f));
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 100.0f));

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CGame::Uninit(void)
{
	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CGame::Update(void)
{
	//bool bEnemy = false;
	//CScene *pEnemy = NULL;
	//do
	//{
	//	pEnemy = CScene::GetScene(CScene::OBJTYPE_ENEMY);
	//	if (pEnemy != NULL)
	//	{
	//		bEnemy = true;
	//	}
	//} while (pEnemy != NULL);

	if (CScene::GetUpdateStop() == false)
	{
		if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
		{ //Enterキー または Bボタンを押したとき
			//フェードの生成
			CManager::CreateFade(CManager::MODE_RESULT);
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CGame::Draw(void)
{
}

//*****************************************************************************
//プレイヤーの取得
//*****************************************************************************
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}