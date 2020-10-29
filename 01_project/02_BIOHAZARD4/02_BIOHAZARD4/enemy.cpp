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
#include "game.h"
#include "enemy.h"
#include "player.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CEnemy::m_pMesh = NULL;
LPD3DXBUFFER CEnemy::m_pBuffMat = NULL;
DWORD CEnemy::m_nNumMat = 0;
bool  CEnemy::m_bChase = false;

//----------------------------------------
//インクリメント
//----------------------------------------
CEnemy::CEnemy(int nPriority) :CModel(nPriority)
{
	m_fPlayerDirection = 0.0f;
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

	D3DXLoadMeshFromX("data/MODEL/enemymodel_test001.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	);

	return E_NOTIMPL;
}

//----------------------------------------
//モデルの破棄
//----------------------------------------
void CEnemy::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	if (m_nNumMat != NULL)
	{
		m_nNumMat = NULL;
	}
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CEnemy::Init(void)
{
	CModel::BindModel(m_pMesh, m_pBuffMat, m_nNumMat);
	m_bChase = false;
	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CEnemy::Uninit(void)
{
	CModel::Uninit();
}

//----------------------------------------
//更新処理
//----------------------------------------
void CEnemy::Update(void)
{			
	//プレイヤーの場所の取得
	D3DXVECTOR3 pPlayerPos = CGame::GetPlayer()->GetPos();	
	//シーンの取得
	CScene *pScene = NULL;
	//プレイヤーの方向を計算
	m_fPlayerDirection = (float)atan2((pPlayerPos.z - m_pos.z ), (pPlayerPos.x - m_pos.x));
	if (m_bChase == false)
	{
		do
		{
			pScene = GetScene(OBJTYPE_PLAYER);
			if (pScene != NULL)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					//プレイヤーが近づいたら追いかける
					if (m_pos.x - pPlayerPos.x  >= -50 &&  m_pos.x - pPlayerPos.x <= 50 &&
						m_pos.z - pPlayerPos.z  >= -50 &&  m_pos.z - pPlayerPos.z <= 50)
					{	
						m_bChase = true;
					}
				}
			}
		} while (pScene == NULL);
	}
	else
	{
		//プレイヤーの方向に向く
		m_rot.x = sinf(m_fPlayerDirection);
		//向いている方向に進む
		m_pos.x += (float)sinf(m_rot.x)*0.5f;
		m_pos.z += (float)cosf(m_rot.x)*0.5f;
	}
	SetModel(m_pos, m_rot);
	//CModelhierarchy::Update();
}

//----------------------------------------
//描画処理
//----------------------------------------
void CEnemy::Draw(void)
{
	CModel::Draw();
}