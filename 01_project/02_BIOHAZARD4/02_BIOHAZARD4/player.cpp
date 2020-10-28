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
	{ "data/MODEL/PLAYER/legLeft.x" },		// ����
	{ "data/MODEL/PLAYER/legMomoLeft.x" },	// ������
	{ "data/MODEL/PLAYER/legRight.x" },		// �E��
	{ "data/MODEL/PLAYER/legMomoRight.x" }, // �E����
	{ "data/MODEL/PLAYER/upArmLeft.x" },    // ����r
	{ "data/MODEL/PLAYER/downArmLeft.x" },   // ���O�r
	{ "data/MODEL/PLAYER/handLeft.x" },	    // ����
	{ "data/MODEL/PLAYER/upArmRight.x" },    // �E��r
	{ "data/MODEL/PLAYER/downArmRight.x" }, // �E�O�r
	{ "data/MODEL/PLAYER/handRight.x" },    // �E��
};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CPlayer::CPlayer(int nPriority) :CModelhierarchy(nPriority)
{

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
	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		CModelhierarchy::BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], nCount - 1);
	}

	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CPlayer::Uninit(void)
{
	CModelhierarchy::Uninit();
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CPlayer::Update(void)
{
	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	// X�{�^������������e�𔭎�
	if (pInputJoystick->GetJoystickTrigger(CInputJoystick::BUTTON_X))
	{
		CBullet::Create(D3DXVECTOR3(m_pos.x + cosf(m_rot.x), m_pos.y + 20.0f, m_pos.z + sinf(m_rot.x)), D3DXVECTOR3(20.0f, 0.0f, 20.0f),
			D3DXVECTOR3(-sinf(m_rot.x)*2.0f, 0, -cosf(m_rot.x)*2.0f), 100, 10, CBullet::BULLETTYPE_PLAYER);
	}
	//--------------------------
	//�ړ�
	//--------------------------
	if (pStick.lX <= -500)
	{
		m_rot.x -= D3DXToRadian(1);
	}
	//���X�e�B�b�N���E�ɓ|��
	if (pStick.lX >= 500)
	{
		m_rot.x += D3DXToRadian(1);
	}
	//���X�e�B�b�N��O�ɓ|��	
	if (pStick.lY <= -500)
	{
		m_pos.x += -sin(m_rot.x)*1.0f;
		m_pos.z += -cos(m_rot.x)*1.0f;
	}
	//���X�e�B�b�N�����ɓ|��
	if (pStick.lY >= 500)
	{
		m_pos.x += sin(m_rot.x)*1.0f;
		m_pos.z += cos(m_rot.x)*1.0f;
	}
	SetModel(m_pos, m_rot);
	CModelhierarchy::Update();
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CPlayer::Draw(void)
{
	CModelhierarchy::Draw();
}

//----------------------------------------
//�����ݒ�
//----------------------------------------
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;//�ꏊ
	m_rot = rot;//�p�x
	m_size = size;//�傫��
	SetModel(pos, rot);//���f���̐ݒ�
	SetObjType(OBJTYPE_PLAYER);//�I�u�W�F�N�g�^�C�v�̐ݒ�
}
