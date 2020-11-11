//--------------------------------------------------------------------
// CircleParticle
// circleparticle.cpp
// Author : �ǌ� �i
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "circleparticle.h"
//--------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------
CCircleParticle::CCircleParticle()
{
	m_ColorType = COLOR_NONE;
	m_fRadian = 0.0f;
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fAddColor = 0.0f;
}
//--------------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------------
CCircleParticle::~CCircleParticle()
{
}
//--------------------------------------------------------------------
// ����
//--------------------------------------------------------------------
CCircleParticle * CCircleParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength)
{
	// CCircleParticle�N���X�̃|�C���^
	CCircleParticle *pCircleParticle;

	// �������m��
	pCircleParticle = new CCircleParticle;

	// ������
	pCircleParticle->Init(pos, size, rot, col, TexType, fRadian, fLength);

	// CCircleParticle�N���X�̃|�C���^��Ԃ�
	return pCircleParticle;
}
//--------------------------------------------------------------------
// ������
//--------------------------------------------------------------------
HRESULT CCircleParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength)
{
	// CParticle�N���X��Init
	CParticle::Init(pos, size, rot, col, TexType);

	// �ʓx
	m_fRadian = fRadian;
	// ���a
	m_fLength = fLength;

	// �J���[���Z�l��0.01f��
	m_fAddColor = 0.05f;

	// �p�x0.01f
	m_fAngle = 0.01f;

	// �J���[�^�C�v
	m_ColorType = COLOR_ADD;

	// ���W�A���v�Z
	m_fRadian = m_fRadian * D3DX_PI * 2;

	return S_OK;
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CCircleParticle::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CCircleParticle::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �J���[�擾
	D3DXCOLOR col = GetColor();

	// ���W�A���Ɋp�x�����Z
	m_fRadian += m_fAngle;

	// ���W�����߂�
	pos.x = cosf(m_fRadian) * m_fLength;
	pos.z = sinf(m_fRadian) * m_fLength;

	if (m_ColorType != COLOR_NONE)
	{
		if (m_ColorType == COLOR_ADD)
		{
			// a�l���Z
			col.a += m_fAddColor;
			// a�l��1.0f�ȏ�̏ꍇ
			if (col.a >= PARTICLE_CIRCLE_COL_MAX)
			{
				col.a = PARTICLE_CIRCLE_COL_MAX;
				m_ColorType = COLOR_MIN;
			}
		}
		if (m_ColorType == COLOR_MIN)
		{
			// a�l���Z
			col.a -= m_fAddColor;
			// a�l��0.5�ȉ��̏ꍇ
			if (col.a <= PARTICLE_CIRCLE_COL_MIN)
			{
				col.a = PARTICLE_CIRCLE_COL_MIN;
				m_ColorType = COLOR_ADD;
			}
		}
	}
	// �J���[�ݒ�
	SetColor(col);

	// �ʒu���W�ݒ�
	SetPosition(pos);

	// ���l��0�ȉ��̏ꍇ
	if (col.a <= 0.0f)
	{
		// �I��
		Uninit();
		// ������ʂ�Ȃ��悤��
		return;
	}
}
//--------------------------------------------------------------------
// �`��
//--------------------------------------------------------------------
void CCircleParticle::Draw(void)
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