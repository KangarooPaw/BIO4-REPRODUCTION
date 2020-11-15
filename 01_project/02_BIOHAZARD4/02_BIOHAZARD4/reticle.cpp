//-----------------------------------------------------------
// Reticle
// reticle.cpp
// Author : �ǌ��@�i
//-----------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "reticle.h"
//-----------------------------------------------------------
//�ÓI�����o�ϐ��錾
//-----------------------------------------------------------
LPDIRECT3DTEXTURE9 CReticle::m_pTexture = NULL;
//-----------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------
CReticle::CReticle(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//-----------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------
CReticle::~CReticle()
{
}
//-----------------------------------------------------------
// ����
//-----------------------------------------------------------
CReticle * CReticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	// CReticle�|�C���^
	CReticle *pReticle;

	// �������m��
	pReticle = new CReticle(OBJTYPE_UI);

	// ������
	pReticle->Init(pos, size, rot, col);

	// �|�C���^��Ԃ�
	return pReticle;
}
//-----------------------------------------------------------
// �e�N�X�`���ǂݍ���
//-----------------------------------------------------------
HRESULT CReticle::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/reticle.png", &m_pTexture);

	return S_OK;
}
//-----------------------------------------------------------
// �e�N�X�`���j��
//-----------------------------------------------------------
void CReticle::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		// �e�N�X�`��Release
		m_pTexture->Release();

		// m_pTexture��NULL��
		m_pTexture = NULL;
	}
}
//-----------------------------------------------------------
// ������
//-----------------------------------------------------------
HRESULT CReticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	// ���
	// �ʒu���W
	m_pos = pos;
	// �T�C�Y
	m_size = size;
	// ����
	m_rot = rot;
	// �J���[
	m_col = col;

	// ������
	CBillboard::Init();

	// �ʒu���W�ݒ�
	SetPosition(m_pos);

	// �T�C�Y�ݒ�
	SetSize(m_size);

	// �����ݒ�
	SetRotation(m_rot);

	// �J���[�ݒ�
	SetColor(m_col);

	// �e�N�X�`���󂯓n��
	BindTexture(m_pTexture);

	return S_OK;
}
//-----------------------------------------------------------
// �I��
//-----------------------------------------------------------
void CReticle::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}
//-----------------------------------------------------------
// �X�V
//-----------------------------------------------------------
void CReticle::Update(void)
{
	// �X�V
	CBillboard::Update();

	// �ʒu���W
	D3DXVECTOR3 pos;

	// �����_�擾
	pos = CManager::GetCamera()->GetPosR();
	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	// L2�𗣂�����
	if (pInputJoystick->GetJoystickRelease(pInputJoystick->BUTTON_L2))
	{
		// �I��
		Uninit();
		return;
	}

	m_pos.x = pos.x;
	m_pos.y = pos.y + 10;
	m_pos.z = pos.z;
	// �J���[�ݒ�
	SetColor(m_col);

	// �ʒu���W�ݒ�
	SetPosition(m_pos);

}
//-----------------------------------------------------------
// �`��
//-----------------------------------------------------------
void CReticle::Draw(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�g�̌��ʂ𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �`��
	CBillboard::Draw();

	// ���C�g�̌��ʂ�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
