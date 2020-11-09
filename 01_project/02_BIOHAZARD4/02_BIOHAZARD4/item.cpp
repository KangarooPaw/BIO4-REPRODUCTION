//****************************************
//���f������
//****************************************

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "player.h"
#include "item.h"
#include "model.h"

#define ROT_ADDSPEED 0.01f //�������Z
#define UPDOWN_SPEED 0.05f //�㉺�^���X�s�[�h

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CItem::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CItem::m_pBuffMat[TYPE_MAX] = {};
DWORD CItem::m_nNumMat[TYPE_MAX] = {};
//D3DXMATRIX CItem::m_mtxWorld = {};	 // �s��v�Z�p
char* CItem::m_apFileName[TYPE_MAX] = { { "data/MODEL/ITEM/habu.x" },
{ "data/MODEL/ITEM/supure.x" },
{ "data/MODEL/ITEM/ammo_box.x" } };// �}�b�v
LPDIRECT3DTEXTURE9 CItem::m_pTexture[TYPE_MAX][50] = {};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CItem::CItem(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(ITEM_ROT_X, 0.0f, ITEM_ROT_X);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_pModel = NULL;
	m_fRd = 0.0f;
	m_mtxWorld = {};
}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CItem::~CItem()
{

}

//----------------------------------------
//��������
//----------------------------------------
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type)
{
	CItem *pItem;
	pItem = new CItem;
	pItem->m_type = type;
	pItem->Init();
	pItem->SetItem(pos, rot, size);

	return pItem;
}

//----------------------------------------
//���f���̓ǂݍ���
//----------------------------------------
HRESULT CItem::Load(void)
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
HRESULT CItem::LoadTexture(void)
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
void CItem::Unload(void)
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
HRESULT CItem::Init(void)
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
void CItem::Uninit(void)
{
	// ���f���N���X�̏I������
	m_pModel->Uninit();
	m_pModel = NULL;
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CItem::Update(void)
{
	/*CScene3d::Update();*/

	m_pModel->Update();
	//��]
	m_rot.y += ROT_ADDSPEED;

	//�㉺�^��
	m_fRd += 0.1f;
	if (m_fRd >= 360)
	{
		m_fRd = 0;
	}
	m_pos.y += (UPDOWN_SPEED * sin(m_fRd));
	
	//���X�V
	SetItem(m_pos, m_rot, m_size);

	//�����蔻�菈��
	CScene *pScene = NULL;

	do
	{
		pScene = GetScene(OBJTYPE_PLAYER);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_PLAYER)
			{
				// ���W�ƃT�C�Y�̎󂯎��
				D3DXVECTOR3 Getpos = ((CPlayer*)pScene)->GetPos();
				D3DXVECTOR3 Getsize = ((CPlayer*)pScene)->GetSize();

				// �����蔻��
				if (CollisionItem(m_pos, m_size, Getpos, Getsize) == true)
				{
					//// �A�C�e��������
				/*	Uninit();
					return;*/
				}
			}
		}
	} while (pScene != NULL);


}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CItem::Draw(void)
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
//�����蔻��
bool CItem::CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2)
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

void CItem::SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos; m_rot = rot; m_size = size;
	m_pModel->SetModel(m_pos, m_rot, m_size);
	SetObjType(OBJTYPE_ITEM);
}