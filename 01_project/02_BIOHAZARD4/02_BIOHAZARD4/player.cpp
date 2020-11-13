//****************************************
//モデル処理
//****************************************

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "motion.h"
#include "model.h"
#include "reticle.h"
#include "life.h"
#include "item.h"
#include "heal.h"
#include "bullet_ui.h"
#include "key.h"
#include "gate.h"

#define ADD_BULLET 10 //弾薬箱の玉取得数
//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CPlayer::m_pMesh[MAX_PLAYER_PARTS] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[MAX_PLAYER_PARTS] = {};
DWORD CPlayer::m_nNumMat[MAX_PLAYER_PARTS] = {};
D3DXMATRIX CPlayer::m_mtxWorld[MAX_PLAYER_PARTS] = {};	 // 行列計算用
int CPlayer::m_nldxModelParent[MAX_PLAYER_PARTS] = {};	 // 親モデルのインデックス
char* CPlayer::m_apFileName[MAX_PLAYER_PARTS] = {
	{ "data/MODEL/PLAYER/body.x" },			// 上半身
	{ "data/MODEL/PLAYER/bodyUnder.x" },	// 下半身
	{ "data/MODEL/PLAYER/head.x" },			// 頭
	{ "data/MODEL/PLAYER/legMomoLeft.x" },	// 左もも
	{ "data/MODEL/PLAYER/legLeft.x" },		// 左足
	{ "data/MODEL/PLAYER/legMomoRight.x" }, // 右もも
	{ "data/MODEL/PLAYER/legRight.x" },		// 右足
	{ "data/MODEL/PLAYER/upArmLeft.x" },	// 左上腕
	{ "data/MODEL/PLAYER/downArmLeft.x" },  // 左前腕
	{ "data/MODEL/PLAYER/handLeft.x" },		// 左手
	{ "data/MODEL/PLAYER/upArmRight.x" },   // 右上腕
	{ "data/MODEL/PLAYER/downArmRight.x" }, // 右前腕
	{ "data/MODEL/PLAYER/handRight.x" },	// 右手
	{ "data/MODEL/PLAYER/gun.x" },			// 銃
	{ "data/MODEL/PLAYER/knife.x" },		// ナイフ
};
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[MAX_PLAYER_PARTS][MAX_MATERIAL] = {};

bool CPlayer::m_bDeath = false;
bool CPlayer::m_bHasKeyAll = false;

//----------------------------------------
//インクリメント
//----------------------------------------
CPlayer::CPlayer(int nPriority) :CScene(nPriority)
{
	//プレイヤー
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角度
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//サイズ
	//弾
	m_bulletRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_bulletRotX = 0;
	m_bulletRotY = 0;
	//残弾初期化
	m_nMagazineBullet = MAX_MAGAZINE_BULLET;
	m_nHaveBullet = 10;
	//鍵初期化
	m_nKey = 0;
	//ナイフモーション
	m_nKnifeMotionCnt = 0;
	m_bKnifeMotion = false;
	//ダメージモーション
	m_nDamageMotionCnt = 0;	
	m_bDamageMotion = false;
	//死亡モーション
	m_nDeathMotionCnt = 0;
	m_bDeathMotion = false;	
	//死亡フラグ
	m_bDeath = false;
	// 全てのカギを持っているか
	m_bHasKeyAll = false;
	//ターンモーション
	m_nTurnCnt = 0;	
	m_bTurn = false;
	//レティクルの生成判定
	m_bReticle = false;
	//モーションポインタ
	m_pMotion = NULL;
	//モデルポインタ
	memset(m_pModel, NULL, sizeof(m_pModel));
	m_bDeath = false;
}

//----------------------------------------
//デクリメント
//----------------------------------------
CPlayer::~CPlayer()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetPlayer(pos, rot, size);
	return pPlayer;
}

//----------------------------------------
//モデルの読み込み
//----------------------------------------
HRESULT CPlayer::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFileName[nCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCount],
			NULL,
			&m_nNumMat[nCount],
			&m_pMesh[nCount]
		);
	}

	// テクスチャの読み込み
	LoadTexture();

	return E_NOTIMPL;
}

//----------------------------------------
//モデルの破棄
//----------------------------------------
void CPlayer::Unload(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// メッシュの破棄
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}

		// マテリアルの破棄
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}

		if (m_nNumMat[nCount] != NULL)
		{
			m_nNumMat[nCount] = NULL;
		}
	}
}

//----------------------------------------
// テクスチャの読み込み
//----------------------------------------
HRESULT CPlayer::LoadTexture(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// マテリアル情報を取り出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[nCount]->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// 使用しているテクスチャがあれば読み込む
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// テクスチャ読み込み
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_pTexture[nCount][nCntMat])))
				{
					return E_FAIL;
				}
			}
		}
	}

	return E_NOTIMPL;
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CPlayer::Init(void)
{
	// モーションの生成
	m_pMotion = CMotion::Create();

	// モーションの読み込み
	m_pMotion->Load(LOAD_PLAYER_TEXT);
	m_pMotion->LoadMotion(MOTION_PLAYER_TEXT);

	// モーションの初期設定
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// モデルの生成
		m_pModel[nCount] = CModel::Create();

		// ペアレントの受け取り
		m_nldxModelParent[nCount] = m_pMotion->GetParents(nCount);

		// モデルのバインド
		m_pModel[nCount]->BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_nldxModelParent[nCount]);

		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// テクスチャのバインド
			m_pModel[nCount]->BindTexture(m_pTexture[nCount][nCntMat], nCntMat);
		}

		// モデルのパーツごとの座標と回転を受け取る
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// 座標、回転、サイズのセット
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);

	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CPlayer::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
	{
		if (m_pModel[nCount] != NULL)
		{
			// モデルクラスの終了処理
			m_pModel[nCount]->Uninit();
			m_pModel[nCount] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{
		// モーションクラスの終了処理
		m_pMotion->Uninit();
		m_pMotion = NULL;
	}

	//フェードの生成
	CManager::CreateFade(CManager::MODE_GAMEOVER);
	//リリース
	Release();
}

//----------------------------------------
//更新処理
//----------------------------------------
void CPlayer::Update(void)
{
	// 門が開くかを取得
	bool bOpenGate = CGame::GetGate()->GetOpen();
	// bOpenGateがfalseの場合
	if (bOpenGate == false)
	{
		// モーションの更新処理
		m_pMotion->UpdateMotion();

		//キーボードの取得処理
		CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

		//残弾数UI取得
		CBulletUi *pBulletUi = CGame::GetBulletUi();
		//所持弾数UI取得
		CBulletUi *pHaveBulletUi = CGame::GetBulletHaveUi();
		//key取得
		CKey *pHaveKey = CGame::GetKey();

		if (pBulletUi != NULL)
		{
			if (m_nMagazineBullet >= 0)
			{
				pBulletUi->SetbulletUi(m_nMagazineBullet);
			}
		}
		if (pHaveBulletUi != NULL)
		{
			if (m_nMagazineBullet >= 0)
			{
				pHaveBulletUi->SetbulletUi(m_nHaveBullet);
			}
		}
		if (pHaveKey != NULL)
		{
			if (m_nKey >= 0)
			{
				pHaveKey->SetKeyUi(m_nKey);
				// 鍵を3個持っている場合
				if (m_nKey == MAX_KEY)
				{
					// m_bHasKeyAllをtrueに
					m_bHasKeyAll = true;
				}
			}
		}

		if (m_bDeath == false)
		{
			//ナイフモーション中なら
			if (m_bKnifeMotion == true)
			{
				m_nKnifeMotionCnt++;
				//45フレームでリセット
				if (m_nKnifeMotionCnt % 45 == 0)
				{
					m_bKnifeMotion = false;
					m_nKnifeMotionCnt = 0;
				}
			}
			//ダメージモーション中なら
			if (m_bDamageMotion == true)
			{
				m_nDamageMotionCnt++;
				//60フレームでリセット
				if (m_nDamageMotionCnt % 60 == 0)
				{
					m_bDamageMotion = false;
					m_nDamageMotionCnt = 0;
				}
			}
			//ターン中なら
			if (m_bTurn == true)
			{
				m_rot.y += D3DXToRadian(6);
				m_nTurnCnt++;
				//ターンの終了
				if (m_nTurnCnt == 30)
				{
					m_bTurn = false;
					m_nTurnCnt = 0;
					//弾の角度設定
					m_bulletRot = m_rot;
				}
			}
			//ターンしてないなら
			else if (m_bTurn == false)
			{
				GamePad();
			}
			for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
			{
				// モデルのパーツごとの座標と回転を受け取る
				m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
			}

			// 座標、回転、サイズのセット
			m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);
		}
		else if (m_bDeath == true)
		{
			if (m_bDeathMotion == false)
			{
				m_pMotion->SetMotion(CMotion::MOTION_DEATH);
				m_bDeathMotion = true;
			}
			//死亡モーション中なら
			if (m_bDeathMotion == true)
			{
				m_nDeathMotionCnt++;
				//120フレームでリセット
				if (m_nDeathMotionCnt % 120 == 0)
				{
					m_bDeathMotion = false;
					m_nDeathMotionCnt = 0;
					Uninit();
				}
			}
		}
	}
}

//----------------------------------------
//描画処理
//----------------------------------------
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&m_mtxWorld[nCount]);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxTrans);

		// 親のモデルパーツ以外のペアレントをセット
		if (m_nldxModelParent[nCount] != -1)
		{
			m_pModel[nCount]->SetParent(m_pModel[m_nldxModelParent[nCount]]);
		}

		// モデルクラスの描画処理
		m_pModel[nCount]->Draw();
	}
}

void CPlayer::GamePad(void)
{
	//コントローラーの取得処理
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}

	//LB/LTを押していないなら
	if ((pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1) == false && pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) == false))
	{
		//ダメージモーション中でないなら
		if (m_bDamageMotion == false)
		{
			//通常モーション
			m_pMotion->SetMotion(CMotion::MOTION_IDLE);
		}

		//--------------------------
		//移動
		//--------------------------
		//左スティックを左に倒す
		if (pStick.lX <= -500)
		{
			m_rot.y -= D3DXToRadian(2);
		}
		//左スティックを右に倒す
		if (pStick.lX >= 500)
		{
			m_rot.y += D3DXToRadian(2);
		}
		//左スティックを前に倒す
		if (pStick.lY <= -500)
		{
			//ダメージモーション中でないなら
			if (m_bDamageMotion == false)
			{
				//走るモーション
				m_pMotion->SetMotion(CMotion::MOTION_RUN);
			}
			m_pos.x += -sinf(m_rot.y)*1.0f;
			m_pos.z += -cosf(m_rot.y)*1.0f;
		}
		//左スティックを後ろに倒す
		if (pStick.lY >= 500)
		{
			//ダメージモーション中でないなら
			if (m_bDamageMotion == false)
			{
				//戻るモーション
				m_pMotion->SetMotion(CMotion::MOTION_BACK);
			}
			m_pos.x += sinf(m_rot.y)*0.5f;
			m_pos.z += cosf(m_rot.y)*0.5f;
			//Aボタンを押して反転
			if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_A))
			{
				m_bTurn = true;
			}
		}
		//アイテムを取得する
		if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_X))
		{
			PickUpItem();
		}
		//弾の角度をプレイヤーの角度と同じにする
		m_bulletRot = m_rot;
		//弾の角度変更数のカウントのリセット
		m_bulletRotX = 0;
		m_bulletRotY = 0;
		//レティクルのリセット
		m_bReticle = false;
	}
	//LBを押している場合
	else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1) && m_bDamageMotion == false)
	{
		if (m_bKnifeMotion == false)
		{
			//ナイフを構えるモーション
			m_pMotion->SetMotion(CMotion::MOTION_HOLDKNIFE);
			m_bKnifeMotion = true;
		}

		//右スティックを左に倒す
		if (pStick.lRx <= -500 || pStick.lZ <= -500)
		{
			m_bulletRot.y -= D3DXToRadian(1);
			m_rot.y -= D3DXToRadian(1);
			m_bulletRotY--;
			if (m_bulletRotY <= MIN_BULLET_ROT_Y)
			{
				m_bulletRot.y += D3DXToRadian(1);
				m_rot.y += D3DXToRadian(1);
				m_bulletRotY = MIN_BULLET_ROT_Y;
			}
		}
		//右スティックを右に倒す
		if (pStick.lRx >= 500 || pStick.lZ >= 500)
		{
			m_bulletRot.y += D3DXToRadian(1);
			m_rot.y += D3DXToRadian(1);
			m_bulletRotY++;
			if (m_bulletRotY >= MAX_BULLET_ROT_Y)
			{
				m_bulletRot.y -= D3DXToRadian(1);
				m_rot.y -= D3DXToRadian(1);
				m_bulletRotY = MAX_BULLET_ROT_Y;
			}
		}
		//右スティックを上に倒す
		if (pStick.lRy <= -500 || pStick.lRz <= -500)
		{
			m_bulletRot.x += D3DXToRadian(1);
			m_bulletRotX++;
			if (m_bulletRotX >= MAX_BULLET_ROT_X)
			{
				m_bulletRot.x -= D3DXToRadian(1);
				m_bulletRotX = MAX_BULLET_ROT_X;

			}
		}
		//右スティックを下に倒す
		if (pStick.lRy >= 500 || pStick.lRz >= 500)
		{
			m_bulletRot.x -= D3DXToRadian(1);
			m_bulletRotX--;
			if (m_bulletRotX <= MIN_BULLET_ROT_X)
			{
				m_bulletRot.x += D3DXToRadian(1);
				m_bulletRotX = MIN_BULLET_ROT_X;
			}
		}

		// Xボタンを押したらナイフを振る
		if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_R2))
		{
			if (m_bKnifeMotion == true)
			{
				//ナイフを振るモーション			
				m_pMotion->SetMotion(CMotion::MOTION_SLASH);

				//弾の生成
				CBullet::Create(
					D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z),
					D3DXVECTOR3(15.0f, 0.0f, 15.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					5,
					10,
					CBullet::BULLETTYPE_PLAYER);
			}
		}
	}
	//LTを押している場合
	else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) && m_bDamageMotion == false)
	{
		//銃を構えるモーション
		m_pMotion->SetMotion(CMotion::MOTION_HOLDGUN);

		//レティクルが生成されていなければ
		if (m_bReticle == false)
		{
			//レティクルの生成
			CReticle::Create(m_pos, D3DXVECTOR3(RETICLE_SIZE_X / 2, RETICLE_SIZE_Y / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			m_bReticle = true;
		}

		//右スティックを左に倒す
		if (pStick.lRx <= -500 || pStick.lZ <= -500)
		{
			//プレイヤーの角度
			m_rot.y -= D3DXToRadian(1);
			//弾の角度
			m_bulletRot.y -= D3DXToRadian(1);
			m_bulletRotY--;
			//弾の角度制限
			if (m_bulletRotY <= MIN_BULLET_ROT_Y)
			{
				//進めたものを戻す
				m_rot.y += D3DXToRadian(1);
				m_bulletRot.y += D3DXToRadian(1);
				m_bulletRotY = MIN_BULLET_ROT_Y;
			}
		}
		//右スティックを右に倒す
		if (pStick.lRx >= 500 || pStick.lZ >= 500)
		{
			//プレイヤーの角度
			m_rot.y += D3DXToRadian(1);
			//弾の角度
			m_bulletRot.y += D3DXToRadian(1);
			m_bulletRotY++;
			//弾の角度制限
			if (m_bulletRotY >= MAX_BULLET_ROT_Y)
			{
				//進めたものを戻す
				m_bulletRot.y -= D3DXToRadian(1);
				m_rot.y -= D3DXToRadian(1);
				m_bulletRotY = MAX_BULLET_ROT_Y;
			}
		}
		//右スティックを上に倒す
		if (pStick.lRy <= -500 || pStick.lRz <= -500)
		{
			//弾の角度
			m_bulletRot.x += D3DXToRadian(1);
			m_bulletRotX++;
			//弾の角度制限
			if (m_bulletRotX >= MAX_BULLET_ROT_X)
			{
				//進めたものを戻す
				m_bulletRot.x -= D3DXToRadian(1);
				m_bulletRotX = MAX_BULLET_ROT_X;

			}
		}
		//右スティックを下に倒す
		if (pStick.lRy >= 500 || pStick.lRz >= 500)
		{
			//弾の角度
			m_bulletRot.x -= D3DXToRadian(1);
			m_bulletRotX--;
			//弾の角度制限
			if (m_bulletRotX <= MIN_BULLET_ROT_X)
			{
				//進めたものを戻す
				m_bulletRot.x += D3DXToRadian(1);
				m_bulletRotX = MIN_BULLET_ROT_X;
			}
		}
		//残弾数が0以上なら
		if (m_nMagazineBullet > 0)
		{
			// Xボタンを押したら弾を発射
			if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_R2))
			{
				//弾の生成
				CBullet::Create(
					D3DXVECTOR3(m_pos.x + cosf(m_rot.y), m_pos.y + 20.0f, m_pos.z + sinf(m_rot.y)),
					D3DXVECTOR3(5.0f, 0.0f, 5.0f),
					D3DXVECTOR3(-sinf(m_bulletRot.y)*5.0f, sinf(m_bulletRot.x), -cosf(m_bulletRot.y)*5.0f),
					100,
					10,
					CBullet::BULLETTYPE_PLAYER);
				//射撃モーション
				m_pMotion->SetMotion(CMotion::MOTION_SHOT);
				CEnemy::SetChase(true);
				m_nMagazineBullet--;
			}
		}
		//リロード
		if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_A))
		{
			for(m_nMagazineBullet;m_nMagazineBullet <= MAX_MAGAZINE_BULLET;m_nMagazineBullet++)
			{
				m_nHaveBullet--;
				if (m_nHaveBullet <= 0)
				{
					m_nHaveBullet = 0;
					return;
				}
			}
		}
	}
}

//----------------------------------------
//初期設定
//----------------------------------------
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;				//場所
	m_rot = rot;				//角度
	m_size = size;				//大きさ
	SetObjType(OBJTYPE_PLAYER); //オブジェクトタイプの設定
}

//----------------------------------------
//プレイヤーがダメージを受けたら
//----------------------------------------
void CPlayer::HitDamage(int nDamage)
{
	if (m_bDamageMotion == false)
	{	//ダメージモーション
		m_pMotion->SetMotion(CMotion::MOTION_DAMAGE);
		m_bDamageMotion = true;
		//体力減少
		CLife::LifeDecrement(nDamage);
	}
}

//----------------------------------------
//アイテムの取得処理
//----------------------------------------
void CPlayer::PickUpItem(void)
{
	//当たり判定処理
	CScene *pScene = NULL;
	do
	{
		pScene = GetScene(OBJTYPE_ITEM);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ITEM)
			{
				// 座標とサイズの受け取り
				D3DXVECTOR3 ItemPos = ((CItem*)pScene)->GetPos();
				D3DXVECTOR3 ItemSize = ((CItem*)pScene)->GetSize();
				int ItemType = ((CItem*)pScene)->GetType();

				// 当たり判定
				if (CollisionItem(m_pos, m_size, ItemPos, ItemSize) == true)
				{
					switch (ItemType)
					{
					case CItem::TYPE_HERB:
						CHeal::HealCreate(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
						CLife::LifeIncrement(20);
						break;
					case CItem::TYPE_SPRAY:
						CHeal::HealCreate(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
						CLife::LifeIncrement(100);
						break;
					case CItem::TYPE_AMMO:
						m_nHaveBullet += ADD_BULLET;
						break;
					case CItem::TYPE_KEY:
						if (m_nKey <= MAX_KEY)
						{
							m_nKey++;
						}
						break;
					default:
						break;
					}
					((CItem*)pScene)->Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);
}

//----------------------------------------
//死亡フラグ
//----------------------------------------
void CPlayer::DeathFlag(void)
{
	m_bDeath = true;
}

//----------------------------------------
//コリジョン判定
//----------------------------------------
bool CPlayer::CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2)
{
	bool bHit = false;  //当たったかどうか

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pos1;       //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	return bHit;    //当たったかどうかを返す
}
