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
#include "player.h"
#include "bullet.h"
#include "motion.h"
#include "model.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CPlayer::m_pMesh[MAX_PLAYER_PARTS] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[MAX_PLAYER_PARTS] = {};
DWORD CPlayer::m_nNumMat[MAX_PLAYER_PARTS] = {};
D3DXMATRIX CPlayer::m_mtxWorld[MAX_PLAYER_PARTS] = {};	 // �s��v�Z�p
int CPlayer::m_nldxModelParent[MAX_PLAYER_PARTS] = {};	 // �e���f���̃C���f�b�N�X
char* CPlayer::m_apFileName[MAX_PLAYER_PARTS] = {
	{ "data/MODEL/PLAYER/body.x" },			// �㔼�g
	{ "data/MODEL/PLAYER/bodyUnder.x" },	// �����g
	{ "data/MODEL/PLAYER/head.x" },			// ��
	{ "data/MODEL/PLAYER/legMomoLeft.x" },	// ������
	{ "data/MODEL/PLAYER/legLeft.x" },		// ����
	{ "data/MODEL/PLAYER/legMomoRight.x" }, // �E����
	{ "data/MODEL/PLAYER/legRight.x" },		// �E��
	{ "data/MODEL/PLAYER/upArmLeft.x" },    // ����r
	{ "data/MODEL/PLAYER/downArmLeft.x" },  // ���O�r
	{ "data/MODEL/PLAYER/handLeft.x" },	    // ����
	{ "data/MODEL/PLAYER/upArmRight.x" },   // �E��r
	{ "data/MODEL/PLAYER/downArmRight.x" }, // �E�O�r
	{ "data/MODEL/PLAYER/handRight.x" },    // �E��
};
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[MAX_PLAYER_PARTS] = {};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CPlayer::CPlayer(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bMotion = false;
	m_bTurn = false;
	m_nTurnCnt = 0;
	m_pMotion = NULL;
	memset(m_pModel, NULL, sizeof(m_pModel));
	memset(m_pTexture, NULL, sizeof(m_pTexture));
}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CPlayer::~CPlayer()
{

}

//----------------------------------------
//��������
//----------------------------------------
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetPlayer(pos, rot, size);
	return pPlayer;
}

//----------------------------------------
//���f���̓ǂݍ���
//----------------------------------------
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
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

		D3DXCreateTextureFromFile(pDevice,
			m_apFileName[nCount],
			&m_pTexture[nCount]);
	}

	return E_NOTIMPL;
}

//----------------------------------------
//���f���̔j��
//----------------------------------------
void CPlayer::Unload(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
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
//����������
//----------------------------------------
HRESULT CPlayer::Init(void)
{
	// ���[�V�����̐���
	m_pMotion = CMotion::Create();

	// ���[�V�����̓ǂݍ���
	m_pMotion->Load(LOAD_PLAYER_TEXT);
	m_pMotion->LoadMotion(MOTION_PLAYER_TEXT);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// ���f���̐���
		m_pModel[nCount] = CModel::Create();

		// �y�A�����g�̎󂯎��
		m_nldxModelParent[nCount] = m_pMotion->GetParents(nCount);

		// ���f���̃o�C���h
		m_pModel[nCount]->BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_nldxModelParent[nCount], m_pTexture[nCount]);

		// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);

	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CPlayer::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// ���f���N���X�̏I������
		m_pModel[nCount]->Uninit();
		m_pModel[nCount] = NULL;
	}

	// ���[�V�����N���X�̏I������
	m_pMotion->Uninit();
	m_pMotion = NULL;
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CPlayer::Update(void)
{
	// ���[�V�����̍X�V����
	m_pMotion->UpdateMotion();

	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();

	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}

	//�i�C�t���[�V�������Ȃ�
	if (m_bMotion == true)
	{
		//�i�C�t���[�V�������Ȃ�
		if (m_bMotion == true)
		{
			m_nMotionCnt++;
			//70�t���[���Ń��Z�b�g
			if (m_nMotionCnt == 60)
			{
				m_bMotion = false;
				m_nMotionCnt = 0;
			}
		}
	}
	//�^�[�����Ȃ�
	else if (m_bTurn == true)
	{
		m_rot.y += D3DXToRadian(3);
		m_nTurnCnt++;
		//�^�[���̏I��
		if (m_nTurnCnt == 60)
		{
			m_bTurn = false;
			m_nTurnCnt = 0;
		}
	}
	else if (m_bTurn == false && m_bMotion == false)
	{
		if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1) == false && pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) == false)
		{
			//�ʏ탂�[�V����
			m_pMotion->SetMotion(CMotion::MOTION_IDLE);
			//--------------------------
			//�ړ�
			//--------------------------
			if (pStick.lX <= -500)
			{
				m_rot.y -= D3DXToRadian(2);
			}							
			//���X�e�B�b�N���E�ɓ|��	
			if (pStick.lX >= 500)		
			{							
				m_rot.y += D3DXToRadian(2);
			}
			//���X�e�B�b�N��O�ɓ|��	
			if (pStick.lY <= -500)
			{
				//���郂�[�V����
				m_pMotion->SetMotion(CMotion::MOTION_RUN);
				m_pos.x += -sinf(m_rot.y)*1.0f;
				m_pos.z += -cosf(m_rot.y)*1.0f;
			}
			//���X�e�B�b�N�����ɓ|��
			if (pStick.lY >= 500)
			{
				m_pMotion->SetMotion(CMotion::MOTION_BACK);
				m_pos.x += sinf(m_rot.y)*0.5f;
				m_pos.z += cosf(m_rot.y)*0.5f;
				//A�{�^���������Ĕ��]
				if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_A))
				{
					m_bTurn = true;
				}
			}
		}
		//LB�������Ă���ꍇ
		else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1))
		{
			if (m_bMotion == false)
			{
				//�i�C�t���\���郂�[�V����
				m_pMotion->SetMotion(CMotion::MOTION_HOLDKNIFE);
				m_bMotion = true;
			}
			// X�{�^������������i�C�t��U��
			if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_R2))
			{
				if (m_bMotion == true)
				{
					//�i�C�t��U�郂�[�V����			
					m_pMotion->SetMotion(CMotion::MOTION_SLASH);
					//�e�̐���
					CBullet::Create(
						D3DXVECTOR3(m_pos.x + cosf(m_rot.y) - 10.0f, m_pos.y + 20.0f, m_pos.z + sinf(m_rot.y) - 10.0f),
						D3DXVECTOR3(5.0f, 0.0f, 5.0f),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),
						15,
						10,
						CBullet::BULLETTYPE_PLAYER);
				}
			}
		}
		//LT�������Ă���ꍇ
		else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2))
		{
			//�e���\���郂�[�V����
			m_pMotion->SetMotion(CMotion::MOTION_HOLDGUN);

			// X�{�^������������e�𔭎�
			if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_R2))
			{
				//�e�̐���
				CBullet::Create(
					D3DXVECTOR3(m_pos.x + cosf(m_rot.y), m_pos.y + 20.0f, m_pos.z + sinf(m_rot.y)),
					D3DXVECTOR3(5.0f, 0.0f, 5.0f),
					D3DXVECTOR3(-sinf(m_rot.y)*5.0f, 0, -cosf(m_rot.y)*5.0f),
					100,
					10,
					CBullet::BULLETTYPE_PLAYER);
				//�ˌ����[�V����
				m_pMotion->SetMotion(CMotion::MOTION_SHOT);
			}
		}
	}
	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
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
//�����ݒ�
//----------------------------------------
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;				//�ꏊ
	m_rot = rot;				//�p�x
	m_size = size;				//�傫��
	SetObjType(OBJTYPE_PLAYER); //�I�u�W�F�N�g�^�C�v�̐ݒ�
}
