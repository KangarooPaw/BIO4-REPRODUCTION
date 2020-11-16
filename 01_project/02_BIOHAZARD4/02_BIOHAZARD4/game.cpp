//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//****************************************************************************************************
//インクルードファイル
//****************************************************************************************************
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "sound.h"
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

//****************************************************************************************************
//静的メンバ変数
//****************************************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CBulletUi *CGame::m_pBulletUi = NULL;
CBulletUi *CGame::m_pBulletHaveUi = NULL;
CKey *CGame::m_pKey  = NULL;
CGate *CGame::m_pGate = NULL;

//****************************************************************************************************
//コンストラクタ
//****************************************************************************************************
CGame::CGame()
{
	m_nCount = 0;
	m_EnemyCount = 0;
}

//****************************************************************************************************
//デストラクタ
//****************************************************************************************************
CGame::~CGame()
{
}

//****************************************************************************************************
//初期化処理
//****************************************************************************************************
HRESULT CGame::Init(void)
{
	//randの初期化
	srand((unsigned)time(NULL));

	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	//カメラ生成
	CManager::CreateCamera();

	//ライト生成
	CManager::CreateLight();

	//UI生成
	CLife::Create(D3DXVECTOR3(1100.0f, 400.0f, 0.0f), D3DXVECTOR3(LIFE_SIZE_X, LIFE_SIZE_Y, 0.0f), 8.1f);
	m_pBulletHaveUi = CBulletUi::Create(D3DXVECTOR3(1150.0f, 595.0f, 0.0f), 30.0f, 50.0f, 10);
	m_pBulletUi = CBulletUi::Create(D3DXVECTOR3(1100.0f, 545.0f, 0.0f), 50.0f, 70.0f, 10);
	m_pKey = CKey::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), 70.0f, 90.0f);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 100.0f, 20.0f));

	//オブジェクト生成
	CSkyBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 1000.0f, 2000.0f));
	CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 200.0f));
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);

	//門生成
	m_pGate = CGate::Create(D3DXVECTOR3(-146.0f, 50.0f, 827.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 20.0f));

	//敵生成
	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		float fPosX = float(rand() % 700 - 300);
		float fPosZ = float(rand() % 700 - 300);
		CEnemy::Create(D3DXVECTOR3(fPosX, 0.0f, fPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	}

	//木箱生成(場所ごと)
	CBox::Create(D3DXVECTOR3(760.0f, 30.0f, -3.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(700.0f, 30.0f, -35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(622.0f, 30.0f, -60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);

	CBox::Create(D3DXVECTOR3(615.0f, 30.0f, 445.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(600.0f, 30.0f, 510.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(555.0f, 30.0f, 580.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);

	CBox::Create(D3DXVECTOR3(560.0f, 30.0f, 320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(630.0f, 30.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);

	CBox::Create(D3DXVECTOR3(-600.0f, 30.0f, 560.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(-600.0f, 30.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);

	CBox::Create(D3DXVECTOR3(-660.0f, 15.0f, -35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(-600.0f, 15.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);

	CBox::Create(D3DXVECTOR3(-360.0f, 25.0f, -290.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(-440.0f, 25.0f, -385.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(-500.0f, 25.0f, -340.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);

	CBox::Create(D3DXVECTOR3(45.0f, 25.0f, -570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(5.0f, 25.0f, -690.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(-100.0f, 25.0f, -660.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);

	CBox::Create(D3DXVECTOR3(350.0f, 20.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(375.0f, 20.0f, 230.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(290.0f, 20.0f, 290.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);
	CBox::Create(D3DXVECTOR3(310.0f, 20.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE), CBox::TYPE_NORMAL);

	return S_OK;
}

//****************************************************************************************************
//終了処理
//****************************************************************************************************
void CGame::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//****************************************************************************************************
//更新処理
//****************************************************************************************************
void CGame::Update(void)
{
	m_EnemyCount++;
	if (m_EnemyCount == 300)
	{
		m_EnemyCount = 0;
		float fPosX = float(rand() % 700 - 300);
		float fPosZ = float(rand() % 700 - 300);
		CEnemy::Create(D3DXVECTOR3(fPosX, 0.0f, fPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z), CEnemy::ENEMYSTATE_NOMAL);
	}
}

//****************************************************************************************************
//描画処理
//****************************************************************************************************
void CGame::Draw(void)
{
}

//****************************************************************************************************
//プレイヤー情報の取得
//****************************************************************************************************
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//****************************************************************************************************
//弾UI情報の取得
//****************************************************************************************************
CBulletUi * CGame::GetBulletUi(void)
{
	return m_pBulletUi;
}

//****************************************************************************************************
//弾の数情報の取得
//****************************************************************************************************
CBulletUi * CGame::GetBulletHaveUi(void)
{
	return  m_pBulletHaveUi;
}

//****************************************************************************************************
//鍵情報の取得
//****************************************************************************************************
CKey * CGame::GetKey(void)
{
	return m_pKey;
}
