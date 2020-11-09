//-----------------------------------------------------------
// �����Ԃ��G�t�F�N�g
// blood.cpp
// Author : �ѐ�ї���
//-----------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "blood.h"

#define BLOOD_VALUE 50//�ؕЂ̗�
#define BLOOD_SPEED 2.5f//�ؕЂ̔�юU�鑬��
#define BLOOD_UP_VALUE 5.5f//�ؕЂ̏�ɏオ���
#define BLOOD_FALL_SPEED 0.5f //�����X�s�[�h
//-----------------------------------------------------------
//�ÓI�����o�ϐ��錾
//-----------------------------------------------------------
LPDIRECT3DTEXTURE9 CBlood::m_pTexture[TYPE_MAX] = {};
//-----------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------
CBlood::CBlood(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_nPatternAnim = 0;
	m_nCounterAnim = 0;
	m_nLife = BLOOD_LIFE;
}
//-----------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------
CBlood::~CBlood()
{
}
//-----------------------------------------------------------
// ����
//-----------------------------------------------------------
CBlood * CBlood::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TYPE type)
{
	// CReticle�|�C���^
	CBlood *pBoxEffect;

	// �������m��
	pBoxEffect = new CBlood(5);
	//�^�C�v
	pBoxEffect->m_type = type;
	// ������
	pBoxEffect->Init(pos, size, rot, col);
	//�ړ���
	pBoxEffect->m_move = move;

	// �|�C���^��Ԃ�
	return pBoxEffect;
}
//-----------------------------------------------------------
// �e�N�X�`���ǂݍ���
//-----------------------------------------------------------
HRESULT CBlood::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/blood.png", &m_pTexture[TYPE_SHARD]);

	return S_OK;
}
//-----------------------------------------------------------
// �e�N�X�`���j��
//-----------------------------------------------------------
void CBlood::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			// �e�N�X�`��Release
			m_pTexture[nCount]->Release();

			// m_pTexture��NULL��
			m_pTexture[nCount] = NULL;
		}
	}
}
//-----------------------------------------------------------
// ������
//-----------------------------------------------------------
HRESULT CBlood::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
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
	SetSize(size);

	// �����ݒ�
	SetRotation(m_rot);

	// �J���[�ݒ�
	SetColor(m_col);

	// �e�N�X�`���󂯓n��
	BindTexture(m_pTexture[m_type]);

	return S_OK;
}
//-----------------------------------------------------------
// �I��
//-----------------------------------------------------------
void CBlood::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}
//-----------------------------------------------------------
// �X�V
//-----------------------------------------------------------
void CBlood::Update(void)
{
	// �X�V
	CBillboard::Update();

	m_move.y += -BLOOD_FALL_SPEED;


	//�ʒu�X�V
	m_pos += m_move;
	//���C�t���Z
	m_nLife--;

	// �J���[�ݒ�
	SetColor(m_col);

	// �ʒu���W�ݒ�
	SetPosition(m_pos);

	//���C�t�O�ŏ���
	if (m_nLife < 0)
	{
		Uninit();
		return;
	}

}
//-----------------------------------------------------------
// �`��
//-----------------------------------------------------------
void CBlood::Draw(void)
{
	// �`��
	CBillboard::Draw();
}
//-----------------------------------------------------------
// �����Ԃ�����
//-----------------------------------------------------------
void CBlood::BloodSplash(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	for (int nCount = 0; nCount < BLOOD_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360 + -360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		float fRandSize = float(rand() % SPLACH_BLOOD_SIZE_X);
		float fRandSpeed = float(rand() % int(BLOOD_SPEED * 10));//�\�{�ɂ��ă����_���ɂ���
		//���̒l�̔{���ɖ߂�
		fRandSpeed = fRandSpeed / 10;
		CBlood::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*fRandSpeed, sinf(D3DXToRadian(fRandRot))*-(fRandSpeed + BLOOD_UP_VALUE), sinf(D3DXToRadian(fRandRot))*fRandSpeed), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_SHARD);
	}
	for (int nCount = 0; nCount < BLOOD_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360 + -360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		float fRandSize = float(rand() % SPLACH_BLOOD_SIZE_X);
		float fRandSpeed = float(rand() % int(BLOOD_SPEED * 10));//�\�{�ɂ��ă����_���ɂ���
																 //���̒l�̔{���ɖ߂�
		fRandSpeed = (fRandSpeed / 10) / 2;
		CBlood::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*fRandSpeed, sinf(D3DXToRadian(fRandRot))*-(fRandSpeed + BLOOD_UP_VALUE), sinf(D3DXToRadian(fRandRot))*fRandSpeed), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_SHARD);
	}
}
