//-----------------------------------------------------------
// �ؔ�
// box.cpp
// Author : �ѐ�ї���
//-----------------------------------------------------------

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "player.h"
#include "box.h"
#include "model.h"
#include "item.h"
#include "boxeffect.h"
#include "sound.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CBox::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CBox::m_pBuffMat[TYPE_MAX] = {};
DWORD CBox::m_nNumMat[TYPE_MAX] = {};
//D3DXMATRIX CItem::m_mtxWorld = {};	 // �s��v�Z�p
char* CBox::m_apFileName[TYPE_MAX] = { { "data/MODEL/OBJECT/box.x" },
{ "data/MODEL/OBJECT/box02.x" } };// ��
LPDIRECT3DTEXTURE9 CBox::m_pTexture[TYPE_MAX][50] = {};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CBox::CBox(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_pModel = NULL;
	m_mtxWorld = {};
	m_bHit = false;
}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CBox::~CBox()
{

}

//----------------------------------------
//��������
//----------------------------------------
CBox * CBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type)
{
	CBox *pItem;
	pItem = new CBox;
	pItem->m_type = type;
	pItem->Init();
	pItem->SetBox(pos, rot, size);

	return pItem;
}

//----------------------------------------
//���f���̓ǂݍ���
//----------------------------------------
HRESULT CBox::Load(void)
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
HRESULT CBox::LoadTexture(void)
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
void CBox::Unload(void)
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
HRESULT CBox::Init(void)
{
	// ���f���̐���
	m_pModel = CModel::Create();

	// ���f���̃o�C���h
	m_pModel->BindModel(m_pMesh[m_type], m_pBuffMat[m_type], m_nNumMat[m_type], -1);

	for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[m_type]; nCntMat++)
	{
		// �e�N�X�`���̃o�C���h
		m_pModel->BindTexture(m_pTexture[m_type][nCntMat], nCntMat);
	}

	//CScene3d::Init();

	////�Z�b�g
	//SetPosition(m_pos);
	//SetRotation(m_rot);
	//SetSize(m_size);
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CBox::Uninit(void)
{
	// ���f���N���X�̏I������
	m_pModel->Uninit();
	m_pModel = NULL;
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CBox::Update(void)
{
	/*CScene3d::Update();*/
	SetBox(m_pos, m_rot, m_size);
	CScene *pScene = NULL;

	do
	{
		pScene = GetScene(OBJTYPE_PLAYER);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BULLET)
			{
				// ���W�ƃT�C�Y�̎󂯎��
				D3DXVECTOR3 Getpos = ((CPlayer*)pScene)->GetPos();
				D3DXVECTOR3 Getsize = ((CPlayer*)pScene)->GetSize();

				// �����蔻��
				if (CollisionItem(m_pos, m_size, Getpos, Getsize) == true)
				{
					//// �A�C�e��������
					/*Uninit();
					return;*/
				}
			}
		}
	} while (pScene != NULL);
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CBox::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	m_pModel->SetWorldMatrix(m_mtxWorld);

	// ���f���N���X�̕`�揈��
	m_pModel->Draw();
}

//�󂳂ꂽ�Ƃ��̏���
bool CBox::HitBox(void)
{
	if (m_bHit == false)
	{
		//�T�E���h�̍Đ�
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_WOODEN_BOX);

		int nRand = rand() % 3;
		//�A�C�e������
		CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 5.0f, m_pos.z), D3DXVECTOR3(ITEM_ROT_X, 0.0f, 0.0f), D3DXVECTOR3(ITEM_SIZE, ITEM_SIZE, ITEM_SIZE), (CItem::TYPE)nRand);
		// ���f���̃o�C���h
		m_pModel->BindModel(m_pMesh[TYPE_BREAKED], m_pBuffMat[TYPE_BREAKED], m_nNumMat[TYPE_BREAKED], -1);

		m_pos.y = 0.0f;

		m_bHit = true;
		//�j��G�t�F�N�g
		CBoxEffect::BreakBox(m_pos, m_size, m_rot, D3DCOLOR_RGBA(255, 255, 255, 255));
		return true;//�������Ă��邱�Ƃ�Ԃ�
	}
	else
	{
		return false;//�����Ă��Ȃ�(���ɉ󂳂�Ă���)���Ƃ�Ԃ�
	}
}
//�����蔻��
bool CBox::CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2)
{
	bool bHit = false;  //�����������ǂ���

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pos1;          //�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pos1;       //�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //�Ԃ����鑤�̍ŏ��l

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	return bHit;    //�����������ǂ�����Ԃ�
}

void CBox::SetBox(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos; m_rot = rot; m_size = size;
	m_pModel->SetModel(m_pos, m_rot, m_size);
	SetObjType(OBJTYPE_BOX);
}