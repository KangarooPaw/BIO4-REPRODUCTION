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

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CEnemy::m_pMesh = NULL;
LPD3DXBUFFER CEnemy::m_pBuffMat = NULL;
DWORD CEnemy::m_nNumMat = 0;

//----------------------------------------
//インクリメント
//----------------------------------------
CEnemy::CEnemy(int nPriority) :CModel(nPriority)
{

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

}

//----------------------------------------
//描画処理
//----------------------------------------
void CEnemy::Draw(void)
{
	CModel::Draw();
}