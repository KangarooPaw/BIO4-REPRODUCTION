//--------------------------------------------------------------------
// �}�Y���t���b�V��
// mazleflash.cpp
// Author : �ǌ� �i
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "mazleflash.h"
//--------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------
CMazleFlash::CMazleFlash(int nPriority) : CParticle(nPriority)
{
	m_fScale = 0.0f;
	m_fAddScale = 0.0f;
	m_fAddColor = 0.0f;
}
//--------------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------------
CMazleFlash::~CMazleFlash()
{
}
//--------------------------------------------------------------------
// ����
//--------------------------------------------------------------------
CMazleFlash * CMazleFlash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CMazleFlash�N���X�̃|�C���^
	CMazleFlash *pMazleFlash;

	// �������m��
	pMazleFlash = new CMazleFlash(OBJTYPE_PARTICLE);

	// ������
	pMazleFlash->Init(pos, size, rot, col, TexType);

	// CMazleFlash�N���X�̃|�C���^��Ԃ�
	return pMazleFlash;
}
//--------------------------------------------------------------------
// ������
//--------------------------------------------------------------------
HRESULT CMazleFlash::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CParticle�N���X��Init
	CParticle::Init(pos, size, rot, col, TexType);

	// �g�嗦��1,0f��
	m_fScale = 1.0f;

	// �g�嗦���Z�l��0.5f��
	m_fAddScale = 0.5f;

	// �J���[���Z�l��0.08f��
	m_fAddColor = 0.08f;

	return S_OK;
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CMazleFlash::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CMazleFlash::Update(void)
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
void CMazleFlash::Draw(void)
{
	// �`��
	CParticle::Draw();
}