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
#include "particle.h"
#include "kira.h"

#define KIRA_VALUE 5//�ؕЂ̗�
#define KIRA_SPEED 2.5f//�ؕЂ̔�юU�鑬��
#define KIRA_UP_VALUE 5.5f//�ؕЂ̏�ɏオ���
#define KIRA_FALL_SPEED 0.5f //�����X�s�[�h
#define KIRA_RAND_RANGE 10 //�����_���z�u�̍L����
#define KIRA_ANIM_COUNT 5 //���̃t���[�����ōX�V
//-----------------------------------------------------------
//�ÓI�����o�ϐ��錾
//-----------------------------------------------------------
LPDIRECT3DTEXTURE9 CKira::m_pTexture[TYPE_MAX] = {};
//-----------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------
CKira::CKira(int nPriority) : CParticle(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_nPatternAnim = 0;
	m_nCounterAnim = 0;
	m_nLife = KIRA_LIFE;
}
//-----------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------
CKira::~CKira()
{
}
//-----------------------------------------------------------
// ����
//-----------------------------------------------------------
CKira * CKira::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TYPE type)
{
	// CReticle�|�C���^
	CKira *pBoxEffect;

	// �������m��
	pBoxEffect = new CKira(5);
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
HRESULT CKira::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/blood.png", &m_pTexture[TYPE_BLOOD]);

	return S_OK;
}
//-----------------------------------------------------------
// �e�N�X�`���j��
//-----------------------------------------------------------
void CKira::Unload(void)
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
HRESULT CKira::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
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
	CParticle::Init(pos, size, rot, col, TEX_TYPE_KIRA);

	//�e�N�X�`�����W�̃Z�b�g
	SetTexture(
		m_nPatternAnim * 0.25f,
		0.0f,
		m_nPatternAnim * 0.25f + 0.25f,
		1.0f);

	//// �e�N�X�`���󂯓n��
	//BindTexture(m_pTexture[m_type]);

	return S_OK;
}
//-----------------------------------------------------------
// �I��
//-----------------------------------------------------------
void CKira::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//-----------------------------------------------------------
// �X�V
//-----------------------------------------------------------
void CKira::Update(void)
{
	// �X�V
	CParticle::Update();

	/*m_move.y += -KIRA_FALL_SPEED;*/

	//�e�N�X�`���A�j���[�V�����X�V
		m_nCounterAnim++;
		if (m_nCounterAnim > KIRA_ANIM_COUNT)
		{
			m_nCounterAnim = 0;
			m_nPatternAnim++;
		}

		if (m_nPatternAnim >= 8)
		{
			Uninit();
			return;
		}

		//�e�N�X�`�����W�̃Z�b�g
		SetTexture(
			m_nPatternAnim * 0.25f,
			0.0f,
			m_nPatternAnim * 0.25f + 0.25f,
			1.0f);

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
void CKira::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// �`��
	CParticle::Draw();
	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//-----------------------------------------------------------
// �����Ԃ�����
//-----------------------------------------------------------
void CKira::EffectKira(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{

	int nRandSeed = 0;//�����_���V�[�h�l
	nRandSeed = rand() % 255;
	srand((unsigned int)time(NULL)*nRandSeed);

	for (int nCount = 0; nCount < KIRA_VALUE; nCount++)
	{
		float fRandPosX = float(rand() % KIRA_RAND_RANGE);
		float fRandPosY = float(rand() % KIRA_RAND_RANGE);
		float fRandPosZ = float(rand() % KIRA_RAND_RANGE);
		float fRandSize = float(rand() % KIRA_SIZE_X);
	
		CKira::Create(D3DXVECTOR3(pos.x + fRandPosX, pos.y + fRandPosY, pos.z + fRandPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_NONE);
	}
	for (int nCount = 0; nCount < KIRA_VALUE; nCount++)
	{
		float fRandPosX = float(rand() % KIRA_RAND_RANGE + -KIRA_RAND_RANGE);
		float fRandPosY = float(rand() % KIRA_RAND_RANGE + -KIRA_RAND_RANGE);
		float fRandPosZ = float(rand() % KIRA_RAND_RANGE + -KIRA_RAND_RANGE);
		float fRandSize = float(rand() % KIRA_SIZE_X);

		CKira::Create(D3DXVECTOR3(pos.x + fRandPosX, pos.y + fRandPosY, pos.z + fRandPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_NONE);
	}
}
