//--------------------------------------------------------------------
// Smoke
// smoke.cpp
// Author : �ǌ� �i
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "spark.h"
//--------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------
CSpark::CSpark()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAddColor = 0.0f;
	m_nCount = 0;
}
//--------------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------------
CSpark::~CSpark()
{
}
//--------------------------------------------------------------------
// ����
//--------------------------------------------------------------------
CSpark * CSpark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CExplosion�N���X�̃|�C���^
	CSpark *pSmoke;

	// �������m��
	pSmoke = new CSpark;

	// ������
	pSmoke->Init(pos, size, rot, col, TexType, move);

	// CExplosion�N���X�̃|�C���^��Ԃ�
	return pSmoke;
}
//--------------------------------------------------------------------
// ������
//--------------------------------------------------------------------
HRESULT CSpark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CParticle�N���X��Init
	CParticle::Init(pos, size, rot, col, TexType);

	// move���
	m_move = move;

	// �J���[���Z�l��0.005f��
	m_fAddColor = 0.005f;

	return S_OK;
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CSpark::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CSpark::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �J���[�擾
	D3DXCOLOR col = GetColor();

	// �C���N�������g
	m_nCount++;

	// �J�E���g��2�ȏ�̏ꍇ
	if (m_nCount >= 2)
	{
		// Scale�̉��Z�l��1.5f��
		m_move.y -= 0.015f;
	}

	// �����Z
	col.a -= m_fAddColor;

	// �J���[�ݒ�
	SetColor(col);

	// �ʒu�X�V
	pos.x += m_move.x;
	pos.y += m_move.y;
	pos.z += m_move.z;

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
void CSpark::Draw(void)
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