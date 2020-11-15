//--------------------------------------------------------------------
// �񕜃G�t�F�N�g
// heal.cpp
// Author : �ǌ� �i
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "heal.h"
//--------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------
CHeal::CHeal(int nPriority) : CParticle(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAddColor = 0.0f;
}
//--------------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------------
CHeal::~CHeal()
{
}
//--------------------------------------------------------------------
// ����
//--------------------------------------------------------------------
CHeal * CHeal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CHeal�N���X�̃|�C���^
	CHeal *pHeal;

	// �������m��
	pHeal = new CHeal(OBJTYPE_PARTICLE);

	// ������
	pHeal->Init(pos, size, rot, col, TexType);

	// CHeal�N���X�̃|�C���^��Ԃ�
	return pHeal;
}
//--------------------------------------------------------------------
// ������
//--------------------------------------------------------------------
HRESULT CHeal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CParticle�N���X��Init
	CParticle::Init(pos, size, rot, col, TexType);

	// �A���t�@�e�X�g�̐��l�ݒ�
	SetAlpha(100);

	// �J���[���Z�l��0.02f��
	m_fAddColor = 0.02f;

	m_move.y = 0.1f;
	return S_OK;
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CHeal::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// �I��
//--------------------------------------------------------------------
void CHeal::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �J���[�擾
	D3DXCOLOR col = GetColor();

	// �����Z
	col.a -= m_fAddColor;

	// �J���[�ݒ�
	SetColor(col);

	pos.y += m_move.y;

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
void CHeal::Draw(void)
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
//--------------------------------------------------------------------
// ��effect����
//--------------------------------------------------------------------
void CHeal::HealCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < 30; nCnt++)
	{
		float fPosX = float(rand() % (int)15.5f * 10 - (int)7.0f * 10);
		float fPosY = float(rand() % (int)15.5f * 10 - (int)7.0f * 10);
		float fPosZ = float(rand() % (int)15.5f * 10 - (int)7.0f * 10);
		fPosX = fPosX / 10;
		fPosY = fPosY / 10;
		fPosZ = fPosZ / 10;
		CHeal::Create(D3DXVECTOR3(pos.x + cosf(rot.y) + fPosX, pos.y + 40.0f + fPosY, pos.z + sinf(rot.y) + fPosZ),
			D3DXVECTOR3(3.0f, 3.0f, 0.0f),
			D3DXVECTOR3(cosf(rot.y), 0.0f, sinf(rot.y)),
			col,
			CParticle::TEX_TYPE_3);
	}
}
