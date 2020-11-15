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
#include "sound.h"
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
#include "bullet_ui.h"
#include "key.h"
#include "gate.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CBulletUi *CGame::m_pBulletUi = NULL;
CBulletUi *CGame::m_pBulletHaveUi = NULL;
CKey *CGame::m_pKey  = NULL;
CGate *CGame::m_pGate = NULL;
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
	//randの初期化
	srand((unsigned)time(NULL));

	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	//カメラ
	CManager::CreateCamera();

	//ライト
	CManager::CreateLight();
	//ポリゴン生成
	CLife::Create(D3DXVECTOR3(1100.0f, 400.0f, 0.0f), D3DXVECTOR3(LIFE_SIZE_X, LIFE_SIZE_Y, 0.0f), 8.1f);
	m_pBulletHaveUi = CBulletUi::Create(D3DXVECTOR3(1150.0f, 595.0f, 0.0f), 30.0f, 50.0f, 10);
	m_pBulletUi = CBulletUi::Create(D3DXVECTOR3(1100.0f, 545.0f, 0.0f), 50.0f, 70.0f, 10);
	m_pKey = CKey::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), 70.0f, 90.0f);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 100.0f, 20.0f));
	CSkyBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 2000.0f));
	CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 200.0f));	
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);

	// 門生成
	m_pGate = m_pGate = CGate::Create(D3DXVECTOR3(-170.0f, 50.0f, 1060.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 20.0f));

	//ボックス
	for (int nCountX = 1; nCountX < 6; nCountX++)
	{
		for (int nCountZ = 1; nCountZ < 6; nCountZ++)
		{
			CBox::Create(D3DXVECTOR3(100.0f + (nCountX * 50.0f), 20.0f, 100.0f + (nCountZ * 50.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
		}
	}
	for (int nCnt = 0; nCnt < 20; nCnt++)
	{
		float fPosX = float(rand() % 1400 - 700);
		float fPosZ = float(rand() % 1400 - 700);
		CEnemy::Create(D3DXVECTOR3(fPosX, 0.0f, fPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	}
	////敵
	//for (int nCountX = 1; nCountX < 3; nCountX++)
	//{
	//	for (int nCountZ = 1; nCountZ < 3; nCountZ++)
	//	{
	//		CEnemy::Create(D3DXVECTOR3(-200.0f + (nCountX * 100.0f), 0.0f, -100.0f + (nCountZ * 100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	//		CEnemy::Create(D3DXVECTOR3(400.0f + (nCountX * 100.0f), 0.0f, -400.0f + (nCountZ * 100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	//		CEnemy::Create(D3DXVECTOR3(500.0f + (nCountX * 100.0f), 0.0f, 700.0f + (nCountZ * 100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	//		CEnemy::Create(D3DXVECTOR3(-700.0f + (nCountX * 100.0f), 0.0f, 600.0f + (nCountZ * 100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	//		CEnemy::Create(D3DXVECTOR3(-200.0f + (nCountX * 100.0f), 0.0f, 860.0f + (nCountZ * 100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	//	}
	//}
	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CGame::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);

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

CBulletUi * CGame::GetBulletUi(void)
{
	return m_pBulletUi;
}

CBulletUi * CGame::GetBulletHaveUi(void)
{
	return  m_pBulletHaveUi;
}

CKey * CGame::GetKey(void)
{
	return m_pKey;
}
