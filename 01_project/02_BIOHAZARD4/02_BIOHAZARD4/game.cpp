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
#include "life.h"
#include "enemy.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "map.h"
#include "item.h"
#include "box.h"
#include "skybox.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame()
{
	m_nCount = 0;
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
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 100.0f, 20.0f));
	//CSkyBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 2000.0f));
	CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 200.0f));	
	CLife::Create(D3DXVECTOR3(1100.0f, 400.0f, 0.0f), D3DXVECTOR3(LIFE_SIZE_X, LIFE_SIZE_Y, 0.0f), 8.1f);
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z));
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z));

	//ボックス
	for (int nCountX = 1; nCountX < 5; nCountX++)
	{
		for (int nCountZ = 1; nCountZ < 5; nCountZ++)
		{
			CBox::Create(D3DXVECTOR3(100.0f + (nCountX * 50.0f), 20.0f, 100.0f + (nCountZ * 50.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
		}
	}

	//敵
	for (int nCountX = 1; nCountX < 2; nCountX++)
	{
		for (int nCountZ = 1; nCountZ < 5; nCountZ++)
		{
			CEnemy::Create(D3DXVECTOR3(200.0f + (nCountX * 50.0f), 0.0f, -100.0f + (nCountZ * 50.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z));
		}
	}
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