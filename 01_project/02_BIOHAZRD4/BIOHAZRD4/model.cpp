#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"

LPD3DXMESH CModel::m_pMesh = NULL;
LPD3DXBUFFER CModel::m_pBuffMat = NULL;
DWORD CModel::m_nNumMat = 0;

CModel::CModel()
{

}

CModel::~CModel()
{

}

CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CModel *pModel;
	pModel = new CModel;
	pModel->m_pos = pos;
	pModel->m_rot = rot;
	pModel->m_size = size;
	pModel->Init();
	return pModel;
}

HRESULT CModel::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("data/MODEL/playermodel_test001.x", 
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

void CModel::Unload(void)
{
}

HRESULT CModel::Init(void)
{	
	CScene3d::SetPosition(m_pos);
	CScene3d::SetRotation(m_rot);
	CScene3d::SetSize(m_size);
	CScene3d::Init();

	return S_OK;
}

void CModel::Uninit(void)
{
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	CScene3d::Uninit();
}

void CModel::Update(void)
{

}

void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
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
