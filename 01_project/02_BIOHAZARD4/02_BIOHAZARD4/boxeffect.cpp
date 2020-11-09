//-----------------------------------------------------------
// �ؔ��j��G�t�F�N�g
// boxeffect.cpp
// Author : �ѐ�ї���
//-----------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "boxeffect.h"
#include "box.h"

#define SHARD_VALUE 20//�ؕЂ̗�
#define SHARD_SPEED 1.5f//�ؕЂ̔�юU�鑬��
#define SHARD_UP_VALUE 1.5f//�ؕЂ̏�ɏオ���
#define FALL_SPEED 0.08f //�����X�s�[�h
//-----------------------------------------------------------
//�ÓI�����o�ϐ��錾
//-----------------------------------------------------------
LPDIRECT3DTEXTURE9 CBoxEffect::m_pTexture = NULL;
//-----------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------
CBoxEffect::CBoxEffect(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = EFFECT_LIFE;
}
//-----------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------
CBoxEffect::~CBoxEffect()
{
}
//-----------------------------------------------------------
// ����
//-----------------------------------------------------------
CBoxEffect * CBoxEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	// CReticle�|�C���^
	CBoxEffect *pBoxEffect;

	// �������m��
	pBoxEffect = new CBoxEffect(5);
	
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
HRESULT CBoxEffect::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	 //�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wood_shard.png", &m_pTexture);

	return S_OK;
}
//-----------------------------------------------------------
// �e�N�X�`���j��
//-----------------------------------------------------------
void CBoxEffect::Unload(void)
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
HRESULT CBoxEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
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
	BindTexture(m_pTexture);

	return S_OK;
}
//-----------------------------------------------------------
// �I��
//-----------------------------------------------------------
void CBoxEffect::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}
//-----------------------------------------------------------
// �X�V
//-----------------------------------------------------------
void CBoxEffect::Update(void)
{
	// �X�V
	CBillboard::Update();

	m_move.y += -FALL_SPEED;
	//�ʒu�X�V
	m_pos += m_move;
	//���C�t���Z
	m_nLife--;

	if (m_nLife < 0)
	{
		Uninit();
		return;
	}

	// �J���[�ݒ�
	SetColor(m_col);

	// �ʒu���W�ݒ�
	SetPosition(m_pos);

}
//-----------------------------------------------------------
// �`��
//-----------------------------------------------------------
void CBoxEffect::Draw(void)
{
	// �`��
	CBillboard::Draw();
}

void CBoxEffect::BreakBox(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	for (int nCount = 0; nCount < SHARD_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		CBoxEffect::Create(D3DXVECTOR3(pos.x,pos.y + (BOX_SIZE / 2),pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*SHARD_SPEED, sinf(D3DXToRadian(fRandRot))*-(SHARD_SPEED + SHARD_UP_VALUE), sinf(D3DXToRadian(fRandRot))*SHARD_SPEED), D3DXVECTOR3(EFFECT_SIZE_X,EFFECT_SIZE_Y,0.0f), D3DXVECTOR3(fRandRot, fRandRotY, fRandRotZ), D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}