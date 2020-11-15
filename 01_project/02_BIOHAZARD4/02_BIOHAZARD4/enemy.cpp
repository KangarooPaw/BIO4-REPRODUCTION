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
#include "motion.h"
#include "model.h"
#include "player.h"
#include "game.h"
#include "bullet.h"
#include "item.h"
#include "map.h"
#include "gate.h"
#include "sound.h"
#include "blood.h"
#include "collision.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CEnemy::m_pMesh[MAX_ENEMY_PARTS] = {};
LPD3DXBUFFER CEnemy::m_pBuffMat[MAX_ENEMY_PARTS] = {};
DWORD CEnemy::m_nNumMat[MAX_ENEMY_PARTS] = {};
D3DXMATRIX CEnemy::m_mtxWorld[MAX_ENEMY_PARTS] = {};	 // �s��v�Z�p
int CEnemy::m_nldxModelParent[MAX_ENEMY_PARTS] = {};	 // �e���f���̃C���f�b�N�X
char* CEnemy::m_apFileName[MAX_ENEMY_PARTS] = {
	{ "data/MODEL/ENEMY/body.x" },			// �㔼�g
	{ "data/MODEL/ENEMY/bodyUnder.x" },	// �����g
	{ "data/MODEL/ENEMY/head.x" },			// ��
	{ "data/MODEL/ENEMY/legMomoLeft.x" },	// ������
	{ "data/MODEL/ENEMY/legLeft.x" },		// ����
	{ "data/MODEL/ENEMY/legMomoRight.x" }, // �E����
	{ "data/MODEL/ENEMY/legRight.x" },		// �E��
	{ "data/MODEL/ENEMY/upArmLeft.x" },    // ����r
	{ "data/MODEL/ENEMY/downArmLeft.x" },  // ���O�r
	{ "data/MODEL/ENEMY/handLeft.x" },	    // ����
	{ "data/MODEL/ENEMY/upArmRight.x" },   // �E��r
	{ "data/MODEL/ENEMY/downArmRight.x" }, // �E�O�r
	{ "data/MODEL/ENEMY/handRight.x" },    // �E��
};
bool CEnemy::m_bChase = false;
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_ENEMY_PARTS][MAX_MATERIAL] = {};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CEnemy::CEnemy(int nPriority) :CScene(nPriority)
{
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getsize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nEnemyLife = 30;
	m_nCntFrame = 0;
	m_nDamageCnt = 0;
	m_nCntAttack = 0;
	m_bHit = false;
	m_bAttack = false;
	m_EnemyState = ENEMYSTATE_NOMAL;
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
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState)

{
    CEnemy *pEnemy;
    pEnemy = new CEnemy;
    pEnemy->SetEnemy(pos, rot, size, EnemyState);
    pEnemy->Init();
    return pEnemy;
}

//----------------------------------------
//���f���̓ǂݍ���
//----------------------------------------
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
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

	// �e�N�X�`���̓ǂݍ���
	LoadTexture();

	return E_NOTIMPL;
}

//----------------------------------------
//���f���̔j��
//----------------------------------------
void CEnemy::Unload(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
	{
		// ���b�V���̔j��
		if (m_pMesh[nCount] != NULL)
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

		if (m_nNumMat[nCount] != NULL)
		{
			m_nNumMat[nCount] = NULL;
		}
	}
}


//----------------------------------------
// �e�N�X�`���̓ǂݍ���
//----------------------------------------
HRESULT CEnemy::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
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

	return E_NOTIMPL;
}


//----------------------------------------
//����������
//----------------------------------------
HRESULT CEnemy::Init(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[�V�����̐���
	m_pMotion = CMotion::Create();

	// ���[�V�����̓ǂݍ���
    m_pMotion->Load(LOAD_ENEMY_TEXT);
    m_pMotion->LoadMotion(MOTION_ENEMY_TEXT);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);

	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
	{
		// ���f���̐���
		m_pModel[nCount] = CModel::Create();

		// �y�A�����g�̎󂯎��
		m_nldxModelParent[nCount] = m_pMotion->GetParents(nCount);

		// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);

		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// �e�N�X�`���̃o�C���h
			m_pModel[nCount]->BindTexture(m_pTexture[nCount][nCntMat], nCntMat);
		}

		// ���f���̃o�C���h
		m_pModel[nCount]->BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_nldxModelParent[nCount]);
	}

	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);

    m_bChase = false;
    return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CEnemy::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
	{
		if (m_pModel[nCount] != NULL)
		{
			// ���f���N���X�̏I������
			m_pModel[nCount]->Uninit();
			m_pModel[nCount] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{
		// ���[�V�����N���X�̏I������
		m_pMotion->Uninit();
		m_pMotion = NULL;
	}

	Release();
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CEnemy::Update(void)
{
	// �傪�J�������擾
	bool bOpenGate = CGame::GetGate()->GetOpen();

	CScene *m_pScene;
	OBJTYPE m_objType;
	BOOL m_bRayHit = false;
	float m_fDistanceEnemy = 0.0f;
	D3DXVECTOR3 m_vexStart, m_vexDirection;
	float m_fRadius = -45.0f;

	//bOpenGate��false�̏ꍇ
	if (bOpenGate == false)
	// �G�̏��
	switch (m_EnemyState)
	{
	case ENEMYSTATE_NOMAL:
		// ���[�V�����̍X�V����
		m_pMotion->UpdateMotion();
		if (CGame::GetPlayer != NULL)
		{
			//�v���C���[�̏ꏊ�̎擾
			D3DXVECTOR3 pPlayerPos = CGame::GetPlayer()->GetPos();

			if (m_bHit == false)
			{
				//���[�V�����Z�b�g(����)
				m_pMotion->SetMotion(CMotion::MOTION_RUN);
			}
			//�_���[�W���[�V����
			if (m_bHit == true)
			{
				m_nDamageCnt++;
				if (m_nDamageCnt % 20 == 0)
				{
					m_bHit = false;
				}
			}
			//�`�F�C�X���łȂ��Ƃ�
			if (m_bChase == false)
			{
				//�����Ă�������ɐi��
				m_pos.x += -sinf(m_rot.y)*0.4f;
				m_pos.z += -cosf(m_rot.y)*0.4f;

				//2�b��1��90�x��]
				m_nCntFrame++;
				if (m_nCntFrame % 120 == 0)
				{
					m_rot.y += D3DXToRadian(90);
				}
				//�߂Â�����ǂ�������
				if (m_pos.x - pPlayerPos.x >= -50 && m_pos.x - pPlayerPos.x <= 50 &&
					m_pos.z - pPlayerPos.z >= -50 && m_pos.z - pPlayerPos.z <= 50)
				{
					m_bChase = true;
				}
			}
			//�`�F�C�X�����U�����łȂ��Ƃ�
			else if (m_bAttack == false)
			{
				//�����̌v�Z
				float angle = (float)atan2(pPlayerPos.x - m_pos.x, pPlayerPos.z - m_pos.z);
				m_rot.y = angle - D3DXToRadian(180);
				//�����Ă�������ɐi��
				m_pos.x += -sinf(m_rot.y)*0.4f;
				m_pos.z += -cosf(m_rot.y)*0.4f;

				if (m_pos.x - pPlayerPos.x >= -20 && m_pos.x - pPlayerPos.x <= 20 &&
					m_pos.z - pPlayerPos.z >= -20 && m_pos.z - pPlayerPos.z <= 20)
				{
					//�U������
					m_bAttack = true;
				}
			}
			//�`�F�C�X�����U�����̎�
			else
			{
				//2�b�ōU��
				m_nCntAttack++;
				if (m_nCntAttack % 120 == false)
				{
					//�U���̔���
					CBullet::Create(
						D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z),
						D3DXVECTOR3(20.0f, 0.0f, 20.0f),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						5,
						10,
						CBullet::BULLETTYPE_ENEMY);
					m_pMotion->SetMotion(CMotion::MOTION_SHOT);
					m_bAttack = false;
				}
			}
		}
		// �����Ȃ����̂ɑ΂��Ẵ��C
		m_pScene = NULL;
		do
		{
			m_pScene = GetScene(OBJTYPE_NONE);
			if (m_pScene != NULL)
			{
				m_objType = m_pScene->GetObjType();
				if (m_objType == OBJTYPE_NONE)
				{
					for (int nCount = 0; nCount < 3; nCount++)
					{
						// �n�߂���W
						m_vexStart = m_pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f);

						// ���C���o���p�x
						m_vexDirection = D3DXVECTOR3(0.0f, m_fRadius + (nCount * 45.0f), 0.0f);

						D3DXIntersect(((CMap*)m_pScene)->GetMapMesh(), &m_vexStart, &D3DXVECTOR3(sinf(m_vexDirection.y), 0.0f, cosf(m_vexDirection.y)),
							&m_bRayHit, NULL, NULL, NULL, &m_fDistanceEnemy, NULL, NULL);

						if (m_bRayHit == true)
						{
							// �͈͂�菬����������
							if (m_fDistanceEnemy < 15.0f)
							{
								// �߂�
								m_pos -= (D3DXVECTOR3(sinf(m_vexDirection.y), 0.0f, cosf(m_vexDirection.y)));

								for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
								{
									// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
									m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
								}

								// ���W�A��]�A�T�C�Y�̃Z�b�g
								m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);

								return;
							}
						}
					}
				}
			}
		} while (m_pScene != NULL);

		// �G���m�̓����蔻��
		EnemyCollision();

		for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
		{
			// ���f���̃p�[�c���Ƃ̃��[�V�����̍��W�Ɖ�]���󂯎��
			m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
		}

		// ���W�A��]�A�T�C�Y�̃Z�b�g(�e�̃��f����������������)
		m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);
		break;

	case ENEMYSTATE_ITEM:
		// ���W�A��]�A�T�C�Y�̃Z�b�g(�e�̃��f����������������)
		m_pModel[0]->SetModel(m_pos, m_rot + D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f), m_size);
		break;

	default:
		break;
	}
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CEnemy::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
	{
		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld[nCount]);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		//m_pModel[nCount]->SetWorldMatrix(m_mtxWorld[nCount]);

		// �e�̃��f���p�[�c�ȊO�̃y�A�����g���Z�b�g
		if (m_nldxModelParent[nCount] != -1)
		{
			m_pModel[nCount]->SetParent(m_pModel[m_nldxModelParent[nCount]]);
		}

		// ���f���N���X�̕`�揈��
		m_pModel[nCount]->Draw();
	}
}

//----------------------------------------
//�q�b�g����
//----------------------------------------
void CEnemy::HitBullet(int nDamage,int nType)
{
	if (m_EnemyState == ENEMYSTATE_NOMAL)
	{
		if (m_bHit == false)
		{
			CBlood::BloodSplash(m_pos, D3DXVECTOR3(SPLACH_BLOOD_SIZE_X, SPLACH_BLOOD_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));
			//�_���[�W���[�V����
			m_pMotion->SetMotion(CMotion::MOTION_DAMAGE);
			m_bHit = true;
			m_nEnemyLife -= nDamage;
		}
		if (m_nEnemyLife <= 0)
		{
			//�T�E���h�̍Đ�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ZOMBIE_DEATH);

			if (int nRand = rand() % 3 == 1)
			{
				CItem::DropItem(m_pos, CItem::TYPE_KEY);
			}
			if (nType == 0)// �w�b�h�V���b�g
			{
				Create(m_pos, m_rot, m_size, ENEMYSTATE_ITEM);
			}
			Uninit();
		}
		else
		{
			//�T�E���h�̍Đ�
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ZOMBIE_DAMAGE);
		}
	}
}

void CEnemy::EnemyCollision(void)
{
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
				m_Getpos = ((CEnemy*)pScene)->GetPos();
				m_Getrot = ((CEnemy*)pScene)->GetRot();
				m_Getsize = ((CEnemy*)pScene)->GetSize();

				float c = sqrtf(m_size.x * m_size.x + m_Getsize.x * m_Getsize.x);
				float fAngle = atan2f(m_pos.x - m_Getpos.x, m_pos.z - m_Getpos.z);

				if (m_Getpos != m_pos)
				{
					// �����蔻��
					if (CCollision::SphereCollision(m_pos, m_size.x, m_Getpos, m_Getsize.x) == true)
					{
						// �߂�
						m_pos += (D3DXVECTOR3(cosf(fAngle), 0.0f, sinf(fAngle)));

					}
				}
			}
		}
	} while (pScene != NULL);

}

//----------------------------------------
//�`�F�C�X���菈��
//----------------------------------------
void CEnemy::SetChase(bool bChase)
{
	m_bChase = bChase;
}

//----------------------------------------
//�e��ݒ�
//----------------------------------------
void CEnemy::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, ENEMYSTATE EnemyState)
{
	m_pos = pos;
	m_rot = rot; 
	m_size = size;
	m_EnemyState = EnemyState;
	SetObjType(OBJTYPE_ENEMY);
}

//=============================================================================
// ���W�̃Z�b�g
//=============================================================================
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ��]�̃Z�b�g
//=============================================================================
void CEnemy::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}