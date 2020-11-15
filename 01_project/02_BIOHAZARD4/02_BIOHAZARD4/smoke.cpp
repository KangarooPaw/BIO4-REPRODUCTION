//--------------------------------------------------------------------
// ��
// smoke.cpp
// Author : �ǌ� �i
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "smoke.h"
//--------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------
CSmoke::CSmoke()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fScale = 0.0f;
	m_fAddScale = 0.0f;
	m_fAddColor = 0.0f;
}
//--------------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------------
CSmoke::~CSmoke()
{
}
//--------------------------------------------------------------------
// ����
//--------------------------------------------------------------------
CSmoke * CSmoke::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CExplosion�N���X�̃|�C���^
	CSmoke *pSmoke;

	// �������m��
	pSmoke = new CSmoke;

	// ������
	pSmoke->Init(pos, size, rot, col, TexType, move);

	// CExplosion�N���X�̃|�C���^��Ԃ�
	return pSmoke;
}
//--------------------------------------------------------------------
// ������
//--------------------------------------------------------------------
HRESULT CSmoke::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CParticle�N���X��Init
	CParticle::Init(pos, size, rot, col, TexType);

	// move���
	m_move = move;

	// �g�嗦��1,0f��
	m_fScale = 1.0f;

	// �g�嗦���Z�l�� 0.9f��
	m_fAddScale = 0.9f;

	// �J���[���Z�l��0.006f��
	m_fAddColor = 0.006f;

	// m_move��0.5�|����
	m_move *= 0.5f;
	return S_OK;
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CSmoke::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CSmoke::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �J���[�擾
	D3DXCOLOR col = GetColor();

	// �g��k��
	m_fScale += m_fAddScale;

	// �g�嗦�ݒ�
	SetScale(m_fScale);

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
void CSmoke::Draw(void)
{
	// �`��
	CParticle::Draw();
}