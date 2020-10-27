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
#include "model.h"
#include "bullet.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CModel::m_pMesh = NULL;
LPD3DXBUFFER CModel::m_pBuffMat = NULL;
DWORD CModel::m_nNumMat = 0;

//----------------------------------------
//インクリメント
//----------------------------------------
CModel::CModel(int nPriority) :CScene3d(nPriority)
{

}

//----------------------------------------
//デクリメント
//----------------------------------------
CModel::~CModel()
{

}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CModel::Init(void)
{	
	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CModel::Uninit(void)
{
	CScene3d::Uninit();
}

//----------------------------------------
//更新処理
//----------------------------------------
void CModel::Update(void)
{
	
}

//----------------------------------------
//描画処理
//----------------------------------------
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.x, m_rot.y, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		m_pMesh->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);
}

//--------------------------------
//モデルのテクスチャ設定
//--------------------------------
void CModel::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat)
{
	m_pMesh = pMesh;
	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
}

//--------------------------------
//モデルの場所、角度設定
//--------------------------------
void CModel::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
}
