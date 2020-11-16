//****************************************************************************************************
// �ؔ��j��G�t�F�N�g
// boxeffect.cpp
// Author : �ѐ�ї���
//****************************************************************************************************

//****************************************************************************************************
//�C���N���[�h�t�@�C��
//****************************************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "boxeffect.h"
#include "box.h"
#include "circleparticle.h"

//****************************************************************************************************
//�}�N����`
//****************************************************************************************************
#define SHARD_VALUE 20				//�ؕЂ̗�
#define SHARD_SPEED 0.5f			//�ؕЂ̔�юU�鑬��
#define SHARD_UP_VALUE 1.5f		//�ؕЂ̏�ɏオ���
#define SMOKE_ANIM_PATTERN 25	//���̃A�j���[�V�����p�^�[��
#define SMOKE_ANIM_COUNT 1		//���̃t���[�����ōX�V
#define SMOKE_SIZE 60.0f				//���T�C�Y
#define FALL_SPEED 0.08f				//�����X�s�[�h

//****************************************************************************************************
//�ÓI�����o�ϐ��錾
//****************************************************************************************************
LPDIRECT3DTEXTURE9 CBoxEffect::m_pTexture[TYPE_MAX] = {};

//****************************************************************************************************
//�R���X�g���N�^
//****************************************************************************************************
CBoxEffect::CBoxEffect(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_nPatternAnim = 0;
	m_nCounterAnim = 0;
	m_nLife = EFFECT_LIFE;
}

//****************************************************************************************************
//�f�X�g���N�^
//****************************************************************************************************
CBoxEffect::~CBoxEffect()
{
}

//****************************************************************************************************
//����
//****************************************************************************************************
CBoxEffect * CBoxEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TYPE type)
{
	//CReticle�|�C���^
	CBoxEffect *pBoxEffect;

	//�������m��
	pBoxEffect = new CBoxEffect(OBJTYPE_BOX);

	//�^�C�v
	pBoxEffect->m_type = type;

	//������
	pBoxEffect->Init(pos, size, rot, col);

	//�ړ���
	pBoxEffect->m_move = move;

	//�|�C���^��Ԃ�
	return pBoxEffect;
}

//****************************************************************************************************
// �e�N�X�`���ǂݍ���
//****************************************************************************************************
HRESULT CBoxEffect::Load(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wood_shard.png", &m_pTexture[TYPE_SHARD]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/smoke03.png", &m_pTexture[TYPE_SMOKE]);

	return S_OK;
}
//****************************************************************************************************
//�e�N�X�`���j��
//****************************************************************************************************
void CBoxEffect::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			//�e�N�X�`��Release
			m_pTexture[nCount]->Release();

			//m_pTexture��NULL��
			m_pTexture[nCount] = NULL;
		}
	}
}
//****************************************************************************************************
//����������
//****************************************************************************************************
HRESULT CBoxEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	//���
	//�ʒu���W
	m_pos = pos;
	//�T�C�Y
	m_size = size;
	//����
	m_rot = rot;
	//�J���[
	m_col = col;

	//������
	CBillboard::Init();

	//�ʒu���W�ݒ�
	SetPosition(m_pos);

	//�T�C�Y�ݒ�
	SetSize(size);

	//�����ݒ�
	SetRotation(m_rot);

	//�J���[�ݒ�
	SetColor(m_col);

	//��
	if (m_type == TYPE_SMOKE)
	{
		//�e�N�X�`�����W�̃Z�b�g
		SetTexture(
			m_nPatternAnim * 0.04f,
			0.0f,
			m_nPatternAnim * 0.04f + 0.04f,
			1.0f);
	}

	//�e�N�X�`���󂯓n��
	BindTexture(m_pTexture[m_type]);

	return S_OK;
}

//****************************************************************************************************
//�I������
//****************************************************************************************************
void CBoxEffect::Uninit(void)
{
	//�I��
	CBillboard::Uninit();
}
//****************************************************************************************************
//�X�V����
//****************************************************************************************************
void CBoxEffect::Update(void)
{
	//�r���{�[�h�X�V
	CBillboard::Update();

	if (m_type == TYPE_SHARD)
	{
		m_move.y += -FALL_SPEED;
	}

	//�ʒu�X�V
	m_pos += m_move;
	//���C�t���Z
	m_nLife--;

	//�J���[�ݒ�
	SetColor(m_col);

	//�ʒu���W�ݒ�
	SetPosition(m_pos);

	//���̃e�N�X�`���A�j���[�V�����X�V
	if (m_type == TYPE_SMOKE)
	{
		m_nCounterAnim++;
		if (m_nCounterAnim > SMOKE_ANIM_COUNT)
		{
			m_nCounterAnim = 0;
			m_nPatternAnim++;
		}

		if (m_nPatternAnim >= SMOKE_ANIM_PATTERN)
		{
			CCircleParticle::CircleCreate(m_pos, D3DXVECTOR3(PARTICLE_CIRCLE_SIZE_X, PARTICLE_CIRCLE_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_CIRCLE, 7.5f);
			Uninit();
			return;
		}

		//�e�N�X�`�����W�̃Z�b�g
		SetTexture(
			m_nPatternAnim * 0.04f,
			0.0f,
			m_nPatternAnim * 0.04f + 0.04f,
			1.0f);

	}

	//���C�t�O�ŏ���
	if (m_nLife < 0)
	{
		Uninit();
		return;
	}

}
//****************************************************************************************************
//�`��
//****************************************************************************************************
void CBoxEffect::Draw(void)
{
	// �`��
	CBillboard::Draw();
}

void CBoxEffect::BreakBox(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{

	CBoxEffect::Create(D3DXVECTOR3(pos.x, pos.y + (BOX_SIZE / 2), pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SMOKE_SIZE, SMOKE_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_SMOKE);
	for (int nCount = 0; nCount < SHARD_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		CBoxEffect::Create(D3DXVECTOR3(pos.x, pos.y + (BOX_SIZE / 2), pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*SHARD_SPEED, sinf(D3DXToRadian(fRandRotY))*-(SHARD_SPEED + SHARD_UP_VALUE), cosf(D3DXToRadian(fRandRotZ))*SHARD_SPEED), D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), D3DXVECTOR3(fRandRot, fRandRotY, fRandRotZ), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_SHARD);
	}
}
