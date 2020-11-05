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
#include "player.h"
#include "bullet.h"
#include "motion.h"
#include "model.h"
#include "reticle.h"
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
	{ "data/MODEL/PLAYER/upArmLeft.x" },    // 左上腕
	{ "data/MODEL/PLAYER/downArmLeft.x" },  // 左前腕
	{ "data/MODEL/PLAYER/handLeft.x" },	    // 左手
	{ "data/MODEL/PLAYER/upArmRight.x" },   // 右上腕
	{ "data/MODEL/PLAYER/downArmRight.x" }, // 右前腕
	{ "data/MODEL/PLAYER/handRight.x" },    // 右手
};
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[MAX_PLAYER_PARTS][MAX_MATERIAL] = {};

//----------------------------------------
//インクリメント
//----------------------------------------
CPlayer::CPlayer(int nPriority) :CScene(nPriority)
{
	//プレイヤー
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//弾
	m_bulletRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_bulletRotX = 0;
	m_bulletRotY = 0;
	//モーション
	m_nMotionCnt = 0;
	m_nTurnCnt = 0;	
	m_bMotion = false;
	m_bTurn = false;

	m_pMotion = NULL;
	memset(m_pModel, NULL, sizeof(m_pModel));
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
	//テクスチャの読み込み
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
	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// モデルクラスの終了処理
		m_pModel[nCount]->Uninit();
		m_pModel[nCount] = NULL;
	}

	// モーションクラスの終了処理
	m_pMotion->Uninit();
	m_pMotion = NULL;
}

//----------------------------------------
//更新処理
//----------------------------------------
void CPlayer::Update(void)
{
	// モーションの更新処理
	m_pMotion->UpdateMotion();

	//キーボードの取得処理
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//コントローラーの取得処理
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}

	//ナイフモーション中なら
	if (m_bMotion == true)
	{
		//ナイフモーション中なら
		if (m_bMotion == true)
		{
			m_nMotionCnt++;
			//60フレームでリセット
			if (m_nMotionCnt == 60)
			{
				m_bMotion = false;
				m_nMotionCnt = 0;
			}
		}
	}

	//ターン中なら
	if (m_bTurn == true)
	{
		m_rot.y += D3DXToRadian(3);
		m_nTurnCnt++;
		//ターンの終了
		if (m_nTurnCnt == 60)
		{
			m_bTurn = false;
			m_nTurnCnt = 0;
		}
	}
	//ターンしてないなら
	else if (m_bTurn == false)
	{
		//LB/LTを押していないなら
		if ((pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1) == false && pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) == false))
		{
			//通常モーション
			m_pMotion->SetMotion(CMotion::MOTION_IDLE);
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
				//走るモーション
				m_pMotion->SetMotion(CMotion::MOTION_RUN);
				m_pos.x += -sinf(m_rot.y)*1.0f;
				m_pos.z += -cosf(m_rot.y)*1.0f;
			}
			//左スティックを後ろに倒す
			if (pStick.lY >= 500)
			{
				//戻るモーション
				m_pMotion->SetMotion(CMotion::MOTION_BACK);
				m_pos.x += sinf(m_rot.y)*0.5f;
				m_pos.z += cosf(m_rot.y)*0.5f;
				//Aボタンを押して反転
				if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_A))
				{
					m_bTurn = true;
				}
			}

			//弾の角度をプレイヤーの角度と同じにする
			m_bulletRot = m_rot;

			//弾の角度変更数のカウントのリセット
			m_bulletRotX = 0;
			m_bulletRotY = 0;
		}
		//LBを押している場合
		else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1))
		{
			if (m_bMotion == false)
			{
				//ナイフを構えるモーション
				m_pMotion->SetMotion(CMotion::MOTION_HOLDKNIFE);
				m_bMotion = true;
			}

			//右スティックを左に倒す
			if (pStick.lRx <= -500)
			{
				m_bulletRot.y -= D3DXToRadian(1);
				m_bulletRotY--;
				if (m_bulletRotY <= MIN_BULLET_ROT_Y)
				{
					m_bulletRot.y += D3DXToRadian(1);
					m_bulletRotY = MIN_BULLET_ROT_Y;
				}
			}
			//右スティックを右に倒す
			if (pStick.lRx >= 500)
			{
				m_bulletRot.y += D3DXToRadian(1);
				m_bulletRotY++;
				if (m_bulletRotY >= MAX_BULLET_ROT_Y)
				{
					m_bulletRot.y -= D3DXToRadian(1);
					m_bulletRotY = MAX_BULLET_ROT_Y;
				}
			}
			//右スティックを上に倒す
			if (pStick.lRy <= -500)
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
			if (pStick.lRy >= 500)
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
				if (m_bMotion == true)
				{
					//ナイフを振るモーション			
					m_pMotion->SetMotion(CMotion::MOTION_SLASH);
					//弾の生成
					CBullet::Create(
						D3DXVECTOR3(m_pos.x + cosf(m_bulletRot.y) - 25.0f, m_pos.y + 20.0f, m_pos.z + sinf(m_bulletRot.y) - 25.0f),
						D3DXVECTOR3(5.0f, 0.0f, 5.0f),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						5,
						10,
						CBullet::BULLETTYPE_PLAYER);
				}
			}
		}
		//LTを押している場合
		else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2))
		{
			//銃を構えるモーション
			m_pMotion->SetMotion(CMotion::MOTION_HOLDGUN);
			CReticle::Create(m_pos, D3DXVECTOR3(RETICLE_SIZE_X / 2, RETICLE_SIZE_Y / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			//右スティックを左に倒す
			if (pStick.lRx <= -500)
			{
				m_bulletRot.y -= D3DXToRadian(1);
				m_bulletRotY--;
				if (m_bulletRotY <= MIN_BULLET_ROT_Y)
				{
					m_bulletRot.y += D3DXToRadian(1);
					m_bulletRotY = MIN_BULLET_ROT_Y;
				}
			}
			//右スティックを右に倒す
			if (pStick.lRx >= 500)
			{
				m_bulletRot.y += D3DXToRadian(1);
				m_bulletRotY++;
				if (m_bulletRotY >= MAX_BULLET_ROT_Y)
				{
					m_bulletRot.y -= D3DXToRadian(1);
					m_bulletRotY = MAX_BULLET_ROT_Y;
				}
			}
			//右スティックを上に倒す
			if (pStick.lRy <= -500)
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
			if (pStick.lRy >= 500)
			{
				m_bulletRot.x -= D3DXToRadian(1);
				m_bulletRotX--;
				if (m_bulletRotX <= MIN_BULLET_ROT_X)
				{
					m_bulletRot.x += D3DXToRadian(1);
					m_bulletRotX = MIN_BULLET_ROT_X;
				}
			}

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
			}
		}
	}

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// モデルのパーツごとの座標と回転を受け取る
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// 座標、回転、サイズのセット
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);
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

		// ワールドマトリックスの設定
		//m_pModel[nCount]->SetWorldMatrix(m_mtxWorld[nCount]);

		// 親のモデルパーツ以外のペアレントをセット
		if (m_nldxModelParent[nCount] != -1)
		{
			m_pModel[nCount]->SetParent(m_pModel[m_nldxModelParent[nCount]]);
		}

		// モデルクラスの描画処理
		m_pModel[nCount]->Draw();
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
