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
LPD3DXMESH CPlayer::m_pMesh = NULL;
LPD3DXBUFFER CPlayer::m_pBuffMat = NULL;
DWORD CPlayer::m_nNumMat = 0;

//----------------------------------------
//�C���N�������g
//----------------------------------------
CPlayer::CPlayer(int nPriority) :CModel(nPriority)
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

	D3DXLoadMeshFromX("data/MODEL/playermodel_test001.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	);

	return S_OK;
}

//----------------------------------------
//���f���̔j��
//----------------------------------------
void CPlayer::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CPlayer::Init(void)
{
	CModel::BindModel(m_pMesh, m_pBuffMat, m_nNumMat);
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CPlayer::Uninit(void)
{
	CModel::Uninit();
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
	if (pInputJoystick->GetJoystickTrigger(0))
	{
		CBullet::Create(D3DXVECTOR3(m_pos.x+ cosf(m_rot.x), m_pos.y+20.0f, m_pos.z+ sinf(m_rot.x) ), D3DXVECTOR3(20.0f, 0.0f, 20.0f),
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
	CModel::Update();
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CPlayer::Draw(void)
{
	CModel::Draw();
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
