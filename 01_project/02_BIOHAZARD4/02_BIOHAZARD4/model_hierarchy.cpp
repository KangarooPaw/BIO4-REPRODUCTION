//=============================================================================
//
// ���f���̊K�w�\���̏��� [model_hierarchy.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "model_hierarchy.h"
#include "bullet.h"

//=============================================================================
// �C���N�������g
//=============================================================================
CModelhierarchy::CModelhierarchy(int nPriority) :CScene3d(nPriority)
{
	for (int nCount = 0; nCount < 14; nCount++)
	{
		m_Model[nCount].m_pMeshParts = NULL;
		m_Model[nCount].m_pBuffMatParts = NULL;
		m_Model[nCount].m_nNumMatParts = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
}

//=============================================================================
// �f�N�������g
//=============================================================================
CModelhierarchy::~CModelhierarchy()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CModelhierarchy::Init(void)
{

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModelhierarchy::Uninit(void)
{
	
}

//=============================================================================
// �X�V����
//=============================================================================
void CModelhierarchy::Update(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModelhierarchy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.x, m_rot.y, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&m_Model[nCount].m_mtxWorldParts);

		//�����𔽓]
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.x, m_rot.y, m_rot.z);
		D3DXMatrixMultiply(&m_Model[nCount].m_mtxWorldParts, &m_Model[nCount].m_mtxWorldParts, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_Model[nCount].m_mtxWorldParts, &m_Model[nCount].m_mtxWorldParts, &mtxTrans);
		
		//�}�e���A���f�[�^�ւ̃|�C���^���擾����
		pMat = (D3DXMATERIAL*)m_Model[nCount].m_pBuffMatParts->GetBufferPointer();

		D3DXMATRIX mtxParent;
		if (m_Model[nCount].m_nldxModelParent == -1) {
			mtxParent = m_mtxWorld;
		}
		else {
			mtxParent = m_Model[m_Model[nCount].m_nldxModelParent].m_mtxWorldParts;
		}

		//���f���p�[�c�ɐe�̃}�g���b�N�X���|�����킹�邱�ƂŁA�ʒu���]��e�ɒǏ]������
		D3DXMatrixMultiply(&m_Model[nCount].m_mtxWorldParts, &m_Model[nCount].m_mtxWorldParts, &mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A�����擾����
		pDevice->GetMaterial(&matDef);

		for (int nCntMat = 0; nCntMat < (int)m_Model[nCount].m_nNumMatParts; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

			//���f���p�[�c�̕`��
			m_Model[nCount].m_pMeshParts->DrawSubset(nCntMat);
		}
		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// ���f���̃e�N�X�`���ݒ�
//=============================================================================
void CModelhierarchy::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat, int nldxModelParent)
{
	// ���b�V���A�}�e���A�����̃|�C���^�A�}�e���A�����̐��A�e���f���̃C���f�b�N�X�̃o�C���h
	m_Model[m_nNumModel].m_pMeshParts= pMesh;
	m_Model[m_nNumModel].m_pBuffMatParts = pBuffMat;
	m_Model[m_nNumModel].m_nNumMatParts = nNumMat;
	m_Model[m_nNumModel].m_nldxModelParent = nldxModelParent;

	// ���f���̃p�[�c�����Z
	m_nNumModel++;
}

//=============================================================================
// ���f���̏ꏊ�A�p�x�ݒ�
//=============================================================================
void CModelhierarchy::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
}