//****************************************
//���f������
//****************************************

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "map.h"
#include "model.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CMap::m_pMesh =NULL;
LPD3DXBUFFER CMap::m_pBuffMat = NULL;
DWORD CMap::m_nNumMat = NULL;
D3DXMATRIX CMap::m_mtxWorld = {};	 // �s��v�Z�p
char* CMap::m_apFileName = {"data/MODEL/MAP/map.x"};// �}�b�v
LPDIRECT3DTEXTURE9 CMap::m_pTexture[MAX_MATERIAL] = {};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CMap::CMap(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pModel = NULL;
}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CMap::~CMap()
{

}

//----------------------------------------
//��������
//----------------------------------------
CMap * CMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CMap *pMap;
	pMap = new CMap;
	pMap->Init();
	pMap->SetMap(pos, rot, size);
	return pMap;
}

//----------------------------------------
//���f���̓ǂݍ���
//----------------------------------------
HRESULT CMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_apFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_nNumMat,
			&m_pMesh
		);

		// �e�N�X�`���̓ǂݍ���
		LoadTexture();

	return E_NOTIMPL;
}

//----------------------------------------
//���f���̔j��
//----------------------------------------
void CMap::Unload(void)
{
		// ���b�V���̔j��
		if (m_pMesh != NULL)
		{
			m_pMesh->Release();
			m_pMesh = NULL;
		}

		// �}�e���A���̔j��
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
// �e�N�X�`���̓ǂݍ���
//----------------------------------------
HRESULT CMap::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �}�e���A���������o��
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// �g�p���Ă���e�N�X�`��������Γǂݍ���
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// �e�N�X�`���ǂݍ���
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat])))
			{
				return E_FAIL;
			}
		}
	}

	return E_NOTIMPL;
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CMap::Init(void)
{
		// ���f���̐���
		m_pModel = CModel::Create();

		// ���f���̃o�C���h
		m_pModel->BindModel(m_pMesh, m_pBuffMat, m_nNumMat, 0);

		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat; nCntMat++)
		{
			// �e�N�X�`���̃o�C���h
			m_pModel->BindTexture(m_pTexture[nCntMat], nCntMat);
		}
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CMap::Uninit(void)
{
		if (m_pModel != NULL)
		{
			// ���f���N���X�̏I������
			m_pModel->Uninit();
			m_pModel = NULL;
		}
		Release();
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CMap::Update(void)
{

}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CMap::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		//m_pModel[nCount]->SetWorldMatrix(m_mtxWorld[nCount]);
	
		// ���f���N���X�̕`�揈��
		m_pModel->Draw();

		//D3DXMATERIAL*pMat;
		//if (m_pBuffMat != NULL)
		//{
		//	//�}�e���A���f�[�^�ւ̃|�C���^���擾����
		//	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
		//}

		//for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		//{
		//	//�}�e���A���̐ݒ�
		//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		//	pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//	pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

		//	if (m_pMesh != NULL)
		//	{
		//		//���f���p�[�c�̕`��
		//		m_pMesh->DrawSubset(nCntMat);
		//	}
		//}

}

//----------------------------------------
//�����ݒ�
//----------------------------------------
void CMap::SetMap(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;				//�ꏊ
	m_rot = rot;				//�p�x
	m_size = size;				//�傫��
	SetObjType(OBJTYPE_NONE); //�I�u�W�F�N�g�^�C�v�̐ݒ�
}
