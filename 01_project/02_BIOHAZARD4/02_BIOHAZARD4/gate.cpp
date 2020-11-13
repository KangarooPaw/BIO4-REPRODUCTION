//-----------------------------------------------------------
// ��
// gate.cpp
// Author : �ǌ��@�i
//-----------------------------------------------------------

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "player.h"
#include "model.h"
#include "gate.h"
#include "game.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CGate::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CGate::m_pBuffMat[TYPE_MAX] = {};
DWORD CGate::m_nNumMat[TYPE_MAX] = {};
char* CGate::m_apFileName[TYPE_MAX] = { { "data/MODEL/MAP/x/gate_left.x" },
{ "data/MODEL/MAP/x/gate_right.x" } };// ��
LPDIRECT3DTEXTURE9 CGate::m_pTexture[TYPE_MAX][50] = {};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CGate::CGate(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(m_pModel, 0, sizeof(m_pModel));
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
	m_bOpen = false;
	m_bmove = false;
	m_nCount = 0;
}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CGate::~CGate()
{

}

//----------------------------------------
//��������
//----------------------------------------
CGate * CGate::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CGate *pGate;
	pGate = new CGate(OBJTYPE_GATE);
	pGate->SetGate(pos, rot, size);
	pGate->Init();

	return pGate;
}

//----------------------------------------
//���f���̓ǂݍ���
//----------------------------------------
HRESULT CGate::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// X�t�@�C���̓ǂݍ���
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
	LoadTexture();
	return S_OK;
}
//----------------------------------------
// �e�N�X�`���̓ǂݍ���
//----------------------------------------
HRESULT CGate::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// �}�e���A���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[nCount]->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// �g�p���Ă���e�N�X�`��������Γǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// �e�N�X�`���ǂݍ���
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

	return S_OK;
}
//----------------------------------------
//���f���̔j��
//----------------------------------------
void CGate::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// ���b�V���̔j��
		if (m_pMesh != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}

		// �}�e���A���̔j��
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}

		if (m_nNumMat != NULL)
		{
			m_nNumMat[nCount] = NULL;
		}
	}
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CGate::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// ���f���̐���
		m_pModel[nCnt] = CModel::Create();

		// ���f���̃o�C���h
		m_pModel[nCnt]->BindModel(m_pMesh[nCnt], m_pBuffMat[nCnt], m_nNumMat[nCnt], -1);

		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[nCnt]; nCntMat++)
		{
			// �e�N�X�`���̃o�C���h
			m_pModel[nCnt]->BindTexture(m_pTexture[nCnt][nCntMat], nCntMat);
		}
	}

	m_pModel[TYPE_LEFT]->SetModel(D3DXVECTOR3(m_pos.x - 142, m_pos.y, m_pos.x), m_rot, m_size);
	m_pModel[TYPE_RIGHT]->SetModel(D3DXVECTOR3(m_pos.x + 142, m_pos.y, m_pos.x), -m_rot, m_size);
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CGate::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// ���f���N���X�̏I������
		m_pModel[nCnt]->Uninit();
		m_pModel[nCnt] = NULL;
	}
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CGate::Update(void)
{
	// �v���C���[���J�M�������Ă��邩���擾
	bool bPlayerHasKey = CGame::GetPlayer()->GetHasKeyAll();
	// �v���C���[���J�M�������Ă���ꍇ
	if (bPlayerHasKey == true)
	{
		if (m_bmove == false)
		{
			// m_bOpen��true��
			m_bOpen = true;
			// m_bOpen��true�̏ꍇ
			if (m_bOpen == true)
			{
				// �J�E���g�C���N�������g
				m_nCount++;
				// m_nCount��60�ȏ�̏ꍇ
				if (m_nCount >= 60)
				{
					// �J�E���g��2
					if (m_nCount % 2 == 0)
					{
						// rot.y��0.5f�����Z
						m_rot.y += D3DXToRadian(0.5f);
					}
				}
				// rot.y��60�ȏ�̏ꍇ
				if (m_rot.y >= D3DXToRadian(60.0f))
				{
					// m_bOpen��false��
					m_bOpen = false;
					// m_bOpen��true��
					m_bmove = true;
				}
			}
		}

	}
	// ���f���̍X�V
	m_pModel[TYPE_LEFT]->SetModel(D3DXVECTOR3(m_pos.x - 142, m_pos.y, m_pos.x), m_rot, m_size);
	m_pModel[TYPE_RIGHT]->SetModel(D3DXVECTOR3(m_pos.x + 142, m_pos.y, m_pos.x), -m_rot, m_size);
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CGate::Draw(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�̌��ʂ𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// TYPE_MAX����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld[nCnt]);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCnt], &m_mtxWorld[nCnt], &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCnt], &m_mtxWorld[nCnt], &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		m_pModel[nCnt]->SetWorldMatrix(m_mtxWorld[nCnt]);

		// ���f���N���X�̕`�揈��
		m_pModel[nCnt]->Draw();
	}
	// ���C�g�̌��ʂ�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CGate::SetGate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// ���f���̏�����
	m_pos = pos; m_rot = rot; m_size = size;
	// �I�u�W�F�N�g��ݒ�
	SetObjType(OBJTYPE_GATE);
}