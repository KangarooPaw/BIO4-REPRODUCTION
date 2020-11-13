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
#include "enemy.h"
#include "motion.h"
#include "model.h"
#include "player.h"
#include "game.h"
#include "bullet.h"
#include "item.h"
#include "gate.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CEnemy::m_pMesh[MAX_ENEMY_PARTS] = {};
LPD3DXBUFFER CEnemy::m_pBuffMat[MAX_ENEMY_PARTS] = {};
DWORD CEnemy::m_nNumMat[MAX_ENEMY_PARTS] = {};
D3DXMATRIX CEnemy::m_mtxWorld[MAX_ENEMY_PARTS] = {};	 // 行列計算用
int CEnemy::m_nldxModelParent[MAX_ENEMY_PARTS] = {};	 // 親モデルのインデックス
char* CEnemy::m_apFileName[MAX_ENEMY_PARTS] = {
	{ "data/MODEL/ENEMY/body.x" },			// 上半身
	{ "data/MODEL/ENEMY/bodyUnder.x" },	// 下半身
	{ "data/MODEL/ENEMY/head.x" },			// 頭
	{ "data/MODEL/ENEMY/legMomoLeft.x" },	// 左もも
	{ "data/MODEL/ENEMY/legLeft.x" },		// 左足
	{ "data/MODEL/ENEMY/legMomoRight.x" }, // 右もも
	{ "data/MODEL/ENEMY/legRight.x" },		// 右足
	{ "data/MODEL/ENEMY/upArmLeft.x" },    // 左上腕
	{ "data/MODEL/ENEMY/downArmLeft.x" },  // 左前腕
	{ "data/MODEL/ENEMY/handLeft.x" },	    // 左手
	{ "data/MODEL/ENEMY/upArmRight.x" },   // 右上腕
	{ "data/MODEL/ENEMY/downArmRight.x" }, // 右前腕
	{ "data/MODEL/ENEMY/handRight.x" },    // 右手
};
bool CEnemy::m_bChase = false;
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_ENEMY_PARTS][MAX_MATERIAL] = {};

//----------------------------------------
//インクリメント
//----------------------------------------
CEnemy::CEnemy(int nPriority) :CScene(nPriority)
{
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nEnemyLife = 30;
	m_nCntFrame = 0;
	m_nDamageCnt = 0;
	m_nCntAttack = 0;
	m_bHit = false;
	m_bAttack = false;
}

//----------------------------------------
//デクリメント
//----------------------------------------
CEnemy::~CEnemy()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
    CEnemy *pEnemy;
    pEnemy = new CEnemy;
    pEnemy->SetEnemy(pos, rot, size);
    pEnemy->Init();
    return pEnemy;
}

//----------------------------------------
//モデルの読み込み
//----------------------------------------
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
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
void CEnemy::Unload(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
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
HRESULT CEnemy::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
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
HRESULT CEnemy::Init(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	// モーションの生成
	m_pMotion = CMotion::Create();

	// モーションの読み込み
    m_pMotion->Load(LOAD_ENEMY_TEXT);
    m_pMotion->LoadMotion(MOTION_ENEMY_TEXT);

	// モーションの初期設定
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);

	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
	{
		// モデルの生成
		m_pModel[nCount] = CModel::Create();

		// ペアレントの受け取り
		m_nldxModelParent[nCount] = m_pMotion->GetParents(nCount);

		// モデルのパーツごとの座標と回転を受け取る
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);

		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// テクスチャのバインド
			m_pModel[nCount]->BindTexture(m_pTexture[nCount][nCntMat], nCntMat);
		}

		// モデルのバインド
		m_pModel[nCount]->BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_nldxModelParent[nCount]);
	}

	// 座標、回転、サイズのセット
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);

    m_bChase = false;
    return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CEnemy::Uninit(void)
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

	Release();
}

//----------------------------------------
//更新処理
//----------------------------------------
void CEnemy::Update(void)
{
	// 門が開くかを取得
	bool bOpenGate = CGame::GetGate()->GetOpen();
	//bOpenGateがfalseの場合
	if (bOpenGate == false)
	{
		// モーションの更新処理
		m_pMotion->UpdateMotion();
		if (CGame::GetPlayer != NULL)
		{
			//プレイヤーの場所の取得
			D3DXVECTOR3 pPlayerPos = CGame::GetPlayer()->GetPos();

			if (m_bHit == false)
			{
				//モーションセット(走る)
				m_pMotion->SetMotion(CMotion::MOTION_RUN);
			}
			//ダメージモーション
			if (m_bHit == true)
			{
				m_nDamageCnt++;
				if (m_nDamageCnt % 20 == 0)
				{
					m_bHit = false;
				}
			}
			//チェイス中でないとき
			if (m_bChase == false)
			{
				//向いている方向に進む
				m_pos.x += -sinf(m_rot.y)*0.4f;
				m_pos.z += -cosf(m_rot.y)*0.4f;

				//2秒に1回90度回転
				m_nCntFrame++;
				if (m_nCntFrame % 120 == 0)
				{
					m_rot.y += D3DXToRadian(90);
				}
				//近づいたら追いかける
				if (m_pos.x - pPlayerPos.x >= -50 && m_pos.x - pPlayerPos.x <= 50 &&
					m_pos.z - pPlayerPos.z >= -50 && m_pos.z - pPlayerPos.z <= 50)
				{
					m_bChase = true;
				}
			}
			//チェイス中かつ攻撃中でないとき
			else if (m_bAttack == false)
			{
				//方向の計算
				float angle = (float)atan2(pPlayerPos.x - m_pos.x, pPlayerPos.z - m_pos.z);
				m_rot.y = angle - D3DXToRadian(180);
				//向いている方向に進む
				m_pos.x += -sinf(m_rot.y)*0.4f;
				m_pos.z += -cosf(m_rot.y)*0.4f;

				if (m_pos.x - pPlayerPos.x >= -20 && m_pos.x - pPlayerPos.x <= 20 &&
					m_pos.z - pPlayerPos.z >= -20 && m_pos.z - pPlayerPos.z <= 20)
				{
					//攻撃判定
					m_bAttack = true;
				}
			}
			//チェイス中かつ攻撃中の時
			else
			{
				//2秒で攻撃
				m_nCntAttack++;
				if (m_nCntAttack % 120 == false)
				{
					//攻撃の判定
					CBullet::Create(
						D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z),
						D3DXVECTOR3(10.0f, 0.0f, 10.0f),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						5,
						10,
						CBullet::BULLETTYPE_ENEMY);
					m_bAttack = false;
				}
			}
		}

		for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
		{
			// モデルのパーツごとのモーションの座標と回転を受け取る
			m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
		}

		// 座標、回転、サイズのセット(親のモデルだけ動かすため)
		m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);
	}
}

//----------------------------------------
//描画処理
//----------------------------------------
void CEnemy::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
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
//ヒット処理
//----------------------------------------
void CEnemy::HitBullet(int nDamage)
{
	if (m_bHit == false)
	{
		//ダメージモーション
		m_pMotion->SetMotion(CMotion::MOTION_DAMAGE);
		m_bHit = true;
		m_nEnemyLife -= nDamage;
	}
	if (m_nEnemyLife <= 0)
	{
		CItem::DropItem(m_pos, CItem::TYPE_KEY);
		Uninit();
	}
}

//----------------------------------------
//チェイス判定処理
//----------------------------------------
void CEnemy::SetChase(bool bChase)
{
	m_bChase = bChase;
}

//----------------------------------------
//各種設定
//----------------------------------------
void CEnemy::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_rot = rot; 
	m_size = size;
	SetObjType(OBJTYPE_ENEMY);
}
