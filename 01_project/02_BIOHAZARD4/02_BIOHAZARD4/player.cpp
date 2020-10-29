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

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CPlayer::m_pMesh[MAX_PLAYER_PARTS] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[MAX_PLAYER_PARTS] = {};
DWORD CPlayer::m_nNumMat[MAX_PLAYER_PARTS] = {};
CPlayer::MODELPARENT CPlayer::m_modelParent[MAX_PLAYER_PARTS] = {
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

//----------------------------------------
//�C���N�������g
//----------------------------------------
CPlayer::CPlayer(int nPriority) :CModelhierarchy(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	pPlayer->SetPlayer(pos, rot, size);
	pPlayer->Init();
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
		D3DXLoadMeshFromX(m_modelParent[nCount].pFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCount],
			NULL,
			&m_nNumMat[nCount],
			&m_pMesh[nCount]
		);
	}

	return S_OK;
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
	}
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CPlayer::Init(void)
{
	m_pMotion = CMotion::Create();
	m_pMotion->Load(LOAD_PLAYER_TEXT);
	m_pMotion->LoadMotion(MOTION_PLAYER_TEXT);

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		m_modelParent[nCount].nIndex = m_pMotion->GetIndex(nCount);
		m_modelParent[nCount].nParents = m_pMotion->GetParents(nCount);
		m_modelParent[nCount].pos = m_pMotion->GetPos(nCount);
		m_modelParent[nCount].rot = m_pMotion->GetRot(nCount);

		// ���f���q�G�����L�[�N���X�̃��f���̃p�[�c���Ƃ̐ݒ�
		CModelhierarchy::BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_modelParent[nCount].nParents);

		SetModelParts(m_modelParent[nCount].pos, m_modelParent[nCount].rot, nCount);
	}
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CPlayer::Uninit(void)
{
	// ���f���q�G�����L�[�N���X�̏I������
	CModelhierarchy::Uninit();
	m_pMotion = NULL;
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CPlayer::Update(void)
{
	// ���[�V�����̍X�V����
	m_pMotion->UpdatePlayerMotion();

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
		m_modelParent[nCount].pos = m_pMotion->GetPos(nCount);
		m_modelParent[nCount].rot = m_pMotion->GetRot(nCount);
	}

	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}

	if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) == false)
	{
		//--------------------------
		//�ړ�
		//--------------------------
		if (pStick.lX <= -500)
		{
			m_rot.y -= D3DXToRadian(1);
		}
		//���X�e�B�b�N���E�ɓ|��
		if (pStick.lX >= 500)
		{
			m_rot.y += D3DXToRadian(1);
		}
		//���X�e�B�b�N��O�ɓ|��	
		if (pStick.lY <= -500)
		{
			m_pMotion->SetMotion(CMotion::MOTION_RUN);
			m_pos.x += -sinf(m_rot.y)*1.0f;
			m_pos.z += -cosf(m_rot.y)*1.0f;
		}
		//���X�e�B�b�N�����ɓ|��
		if (pStick.lY >= 500)
		{
			m_pos.x += sinf(m_rot.y)*1.0f;
			m_pos.z += cosf(m_rot.y)*1.0f;
			//A�{�^���������Ĕ��]
			if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_A))
			{
					m_rot.y += D3DXToRadian(180);
			}
		}
	}
	else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2))
	{
		m_pMotion->SetMotion(CMotion::MOTION_HOLDGUN);
		// X�{�^������������e�𔭎�
		if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_X))
		{
			CBullet::Create(D3DXVECTOR3(m_pos.x + cosf(m_rot.y), m_pos.y + 20.0f, m_pos.z + sinf(m_rot.y)), D3DXVECTOR3(20.0f, 0.0f, 20.0f),
				D3DXVECTOR3(-sinf(m_rot.y)*2.0f, 0, -cosf(m_rot.y)*2.0f), 100, 10, CBullet::BULLETTYPE_PLAYER);
			m_pMotion->SetMotion(CMotion::MOTION_SHOT);
		}
	}
	// X�{�^������������e�𔭎�
	if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_X))
	{
		m_pMotion->SetMotion(CMotion::MOTION_SLASH);
	}

	// ���W�A��]�A�T�C�Y�̃Z�b�g
	SetModel(m_pos, m_rot, m_size);

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// ���f���̃p�[�c���Ƃ̃Z�b�g
		SetModelParts(m_modelParent[nCount].pos, m_modelParent[nCount].rot, nCount);
	}
	// X�{�^������������e�𔭎�
	if (pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_X))
	{
		CBullet::Create(D3DXVECTOR3(m_pos.x + cosf(m_rot.x), m_pos.y + 20.0f, m_pos.z + sinf(m_rot.x)), D3DXVECTOR3(20.0f, 0.0f, 20.0f),
			D3DXVECTOR3(-sinf(m_rot.x)*2.0f, 0, -cosf(m_rot.x)*2.0f), 100, 10, CBullet::BULLETTYPE_PLAYER);
	}
	// ���f���q�G�����L�[�N���X�̍X�V����
	//CModelhierarchy::Update();
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CPlayer::Draw(void)
{
	// ���f���q�G�����L�[�N���X�̏I������
	CModelhierarchy::Draw();
}

//----------------------------------------
//�����ݒ�
//----------------------------------------
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;				//�ꏊ
	m_rot = rot;				//�p�x
	m_size = size;				//�傫��
	SetModel(pos, rot, size);			//���f���̐ݒ�
	SetObjType(OBJTYPE_PLAYER); //�I�u�W�F�N�g�^�C�v�̐ݒ�
}
