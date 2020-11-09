//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author:�ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "box.h"
#include "ui.h"
#include "camera.h"
#include "blood.h"


//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9	CBullet::m_pTexture = NULL;

//=============================================================================
// �o���b�g�N���X�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority) :CScene3d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���݂̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //�傫��
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getsize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = BULLETTYPE_PLAYER;	//���
	m_nLife = 0;			//����
	m_nDamage = 0;      //�_���[�W
}

//=============================================================================
// �o���b�g�N���X�̃f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �o���b�g�N���X�̃C���X�^���X����
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nLife, int nDamage, BULLETTYPE type)
{
	CBullet *pBullet;
	pBullet = new CBullet;

	// �e�̃Z�b�g
	pBullet->SetBullet(pos, size, move, nLife, nDamage, type);
	pBullet->Init();

	return pBullet;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		"PolygonTexture1.png",								// �t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CBullet::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//�o���b�g�N���X�̏���������
//=============================================================================
HRESULT CBullet::Init(void)
{	
	CScene3d::BindTexture(m_pTexture);
	CScene3d::Init();
	return S_OK;
}

//=============================================================================
// �o���b�g�N���X�̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene3d::Uninit();
}

//=============================================================================
//�o���b�g�N���X�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	
	//�ړ��ʂ𔽉f������
	m_pos += m_move;

	//�e�̎˒������߂�
	m_nLife--;

	CScene *pScene = NULL;

	do
	{
		pScene = GetScene(OBJTYPE_ENEMY);
		if (pScene != NULL)
		{	
			if (m_type==BULLETTYPE_PLAYER)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// ���W�ƃT�C�Y�̎󂯎��
					m_Getpos = ((CEnemy*)pScene)->GetPos();
					m_Getsize = ((CEnemy*)pScene)->GetSize();

					// �����蔻��
					if (CollisionBullet(m_pos, m_size, m_Getpos, m_Getsize) == true)
					{
						// �G������
						((CEnemy*)pScene)->HitBullet(m_nDamage);

						// �e������
						Uninit();
						return;
					}
				}
			}
		}
	} while (pScene != NULL);

	do//�v���C���[�̓����蔻��
	{
		pScene = GetScene(OBJTYPE_PLAYER);
		if (pScene != NULL)
		{
			if (m_type == BULLETTYPE_ENEMY)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					m_Getpos = ((CPlayer*)pScene)->GetPos();
					m_Getsize = ((CPlayer*)pScene)->GetSize();
					CBlood::BloodSplash(m_pos, D3DXVECTOR3(SPLACH_BLOOD_SIZE_X, SPLACH_BLOOD_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 0, 0, 255));
					// �����蔻��
					if (CollisionBullet(m_pos, m_size, m_Getpos, m_Getsize) == true)
					{
						// �G������
						((CPlayer*)pScene)->HitDamage(m_nDamage);

						// �e������
						Uninit();
						return;
					}
				}
			}
		}
	} while (pScene != NULL);

	do//���̓����蔻��
	{
		pScene = GetScene(OBJTYPE_BOX);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOX)
			{
				// ���W�ƃT�C�Y�̎󂯎��
				m_Getpos = ((CBox*)pScene)->GetPos();
				m_Getsize = ((CBox*)pScene)->GetSize();

				// �����蔻��
				if (CollisionBullet(m_pos, m_size, m_Getpos, m_Getsize) == true)
				{
					// ����j�󂷂�
					bool bHit = ((CBox*)pScene)->HitBox();
					//�j�󂵂�������i���łɔj�󂳂�Ă�����̂͊ђʂ���j
					if (bHit == true)
					{
						// �e������
						Uninit();
						return;
					}
				}
				else if (m_nLife <= 0)
				{ // ���C�t���Ȃ��Ȃ��������
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	if (m_nLife <= 0)
	{ // ���C�t���Ȃ��Ȃ��������
		Uninit();
		return;
	}

	// ���W�̃Z�b�g
	SetPosition(m_pos);
	CScene3d::Update();
}

//=============================================================================
//�o���b�g�N���X�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene3d::Draw();
}

//=============================================================================
//�o���b�g�N���X�̃^�C�v��n������
//=============================================================================
CBullet::BULLETTYPE CBullet::GetBulletType(void)
{
	return m_type;
}

//=====================================================
// �o���b�g�N���X�̓����蔻��̐ݒ�
//=====================================================
bool CBullet::CollisionBullet(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2)
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