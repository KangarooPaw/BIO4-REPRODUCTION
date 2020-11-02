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
#include "model.h"
#include "bullet.h"

//----------------------------------------
//�C���N�������g
//----------------------------------------
CModel::CModel()
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = NULL;
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
	m_nldxModelParent = 0;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pParent = NULL;
}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CModel::~CModel()
{

}

//=============================================================================
// ���[�V�����N���X�̃C���X�^���X����
//=============================================================================
CModel * CModel::Create()
{
	CModel *pModel;
	pModel = new CModel;
	pModel->Init();
	return pModel;
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CModel::Init()
{
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CModel::Uninit(void)
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = NULL;

	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));

	m_pParent = NULL;
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CModel::Update(void)
{

}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CModel::Draw(void)
{
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//D3DXMATRIX mtxRot, mtxTrans;
	//D3DMATERIAL9 matDef;
	//D3DXMATERIAL*pMat;
	//D3DXMatrixIdentity(&m_mtxWorld);
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//pDevice->GetMaterial(&matDef);
	//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	//{
	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//	m_pMesh->DrawSubset(nCntMat);
	//}
	//pDevice->SetMaterial(&matDef);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x , m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pBuffMat != NULL)
	{
		//�}�e���A���f�[�^�ւ̃|�C���^���擾����
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	}

	D3DXMATRIX mtxParent;
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD2, &mtxParent);
	}

	//���f���p�[�c�ɐe�̃}�g���b�N�X���|�����킹�邱�ƂŁA�ʒu���]��e�ɒǏ]������
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, m_pTexture);

		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		if (m_pMesh != NULL)
		{
			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}


//=============================================================================
// ���f���̃e�N�X�`���ݒ�
//=============================================================================
void CModel::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat, int nldxModelParent, LPDIRECT3DTEXTURE9 Texture)
{
	// ���b�V���A�}�e���A�����̃|�C���^�A�}�e���A�����̐��A�e���f���̃C���f�b�N�X�̃o�C���h�A�e�N�X�`���̏��
	m_pMesh = pMesh;
	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_nldxModelParent = nldxModelParent;
	m_pTexture = Texture;
}

//=============================================================================
// ���f���̏ꏊ�A�p�x�ݒ�
//=============================================================================
void CModel::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
}

//=============================================================================
// ���f���̃y�A�����g�̏��̎󂯎��
//=============================================================================
void CModel::SetParent(CModel *cmodel)
{
	// �|�C���^�̎󂯎��
	m_pParent = cmodel;
}

//=============================================================================
// ���f����
//=============================================================================
void CModel::SetWorldMatrix(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}
