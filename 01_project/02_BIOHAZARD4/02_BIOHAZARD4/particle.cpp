//-----------------------------------------------------------
// Particle
// particle.cpp
// Author : �ǌ��@�i
//-----------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
//-----------------------------------------------------------
//�ÓI�����o�ϐ��錾
//-----------------------------------------------------------
LPDIRECT3DTEXTURE9 CParticle::m_pTexture[TEX_TYPE_MAX] = {};
//-----------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------
CParticle::CParticle(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//-----------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------
CParticle::~CParticle()
{
}
//----------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//----------------------------------------------------------
HRESULT CParticle::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/particle001.png", &m_pTexture[TEX_TYPE_1]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/particle002.png", &m_pTexture[TEX_TYPE_2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/blood.png", &m_pTexture[TEX_TYPE_BLOOD]);
	return S_OK;
}
//----------------------------------------------------------
// �e�N�X�`���̔j��
//----------------------------------------------------------
void CParticle::Unload(void)
{
	// �e�N�X�`����ޕ��J��Ԃ�
	for (int nCnt = 0; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			// �e�N�X�`��Release
			m_pTexture[nCnt]->Release();

			// m_pTexture��NULL��
			m_pTexture[nCnt] = NULL;
		}
	}
}
//-----------------------------------------------------------
// ������
//-----------------------------------------------------------
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE TexType)
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

	// �e�N�X�`���^�C�v
	m_TexType = TexType;

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
	BindTexture(m_pTexture[m_TexType]);

	return S_OK;
}
//-----------------------------------------------------------
// �I��
//-----------------------------------------------------------
void CParticle::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}
//-----------------------------------------------------------
// �X�V
//-----------------------------------------------------------
void CParticle::Update(void)
{
	// �X�V
	CBillboard::Update();

}
//-----------------------------------------------------------
// �`��
//-----------------------------------------------------------
void CParticle::Draw(void)
{
	// �`��
	CBillboard::Draw();

}