//--------------------------------------------------------------------
// ����
// explosion.cpp
// Author : �ǌ� �i
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "explosion.h"
//--------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------
CExplosion::CExplosion()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fScale = 0.0f;
	m_fAddScale = 0.0f;
	m_fAddColor = 0.0f;
	m_nCount = 0;
}
//--------------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------------
CExplosion::~CExplosion()
{
}
//--------------------------------------------------------------------
// ����
//--------------------------------------------------------------------
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CExplosion�N���X�̃|�C���^
	CExplosion *pExplosion;

	// �������m��
	pExplosion = new CExplosion;

	// ������
	pExplosion->Init(pos, size, rot, col, TexType, move);

	// CExplosion�N���X�̃|�C���^��Ԃ�
	return pExplosion;
}
//--------------------------------------------------------------------
// ������
//--------------------------------------------------------------------
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CParticle�N���X��Init
	CParticle::Init(pos, size, rot, col, TexType);

	// move���
	m_move = move;

	// �g�嗦��1,0f��
	m_fScale = 1.0f;

	// �g�嗦���Z�l��8.5f��
	m_fAddScale = 8.5f;

	// �J���[���Z�l��0.02f��
	m_fAddColor = 0.02f;

	// m_move��0.5�|����
	m_move *= 0.5f;

	return S_OK;
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CExplosion::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CExplosion::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �J���[�擾
	D3DXCOLOR col = GetColor();

	// �g��k��
	m_fScale += m_fAddScale;

	// �C���N�������g
	m_nCount++;

	// �J�E���g��5�ȏ�̏ꍇ
	if (m_nCount >= 10)
	{
		// Scale�̉��Z�l��1.5f��
		m_fAddScale = 0.5f;
	}
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
void CExplosion::Draw(void)
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