//****************************************
//���f������
//****************************************

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "enemy.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CEnemy::m_pMesh = NULL;
LPD3DXBUFFER CEnemy::m_pBuffMat = NULL;
DWORD CEnemy::m_nNumMat = 0;

//----------------------------------------
//�C���N�������g
//----------------------------------------
CEnemy::CEnemy(int nPriority) :CModel(nPriority)
{

}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CEnemy::~CEnemy()
{

}

//----------------------------------------
//��������
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
//���f���̓ǂݍ���
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
//���f���̔j��
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
//����������
//----------------------------------------
HRESULT CEnemy::Init(void)
{
	CModel::BindModel(m_pMesh, m_pBuffMat, m_nNumMat);
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CEnemy::Uninit(void)
{
	CModel::Uninit();
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CEnemy::Update(void)
{

}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CEnemy::Draw(void)
{
	CModel::Draw();
}