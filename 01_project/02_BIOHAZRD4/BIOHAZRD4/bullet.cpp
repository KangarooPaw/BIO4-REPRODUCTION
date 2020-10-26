//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author:�ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"

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
	CScene3d::Init();
	CScene3d::BindTexture(m_pTexture);

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
	CScene3d::Update();

	m_pos = GetPosition();

	//�ړ��ʂ𔽉f������
	m_pos += m_move;

	//�e�̎˒������߂�
	m_nLife--;

	// ���W�̃Z�b�g
	SetPosition(m_pos);

	CScene *pScene = NULL;
	do
	{
		pScene = GetScene(OBJTYPE_ENEMY);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_ENEMY)
			{
				// ���W�ƃT�C�Y�̎󂯎��
				m_Getpos = ((CScene3d*)pScene)->GetPosition();
				m_Getsize = ((CScene3d*)pScene)->GetSize();

				// �����蔻��
				if (CollisionBullet(m_pos, m_size, m_Getpos, m_Getsize) == true)
				{
					// �e������
					Uninit();

					// �G������
					((CEnemy*)pScene)->Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	// ���C�t���Ȃ��Ȃ��������
	if (m_nLife <= 0)
	{
		Uninit();
	}
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