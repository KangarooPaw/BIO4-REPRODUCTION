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
LPDIRECT3DTEXTURE9 CParticle::m_pTexture[TYPE_MAX] = {};
//-----------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------
CParticle::CParticle(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Type = TYPE_NONE;
	m_TexType = TEX_TYPE_NONE;
	m_ColorType = COLOR_NONE;
	m_fRadian = 0.0f;
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fScale = 0.0f;
	m_fAddScale = 0.0f;
	m_fAddColor = 0.0f;
	m_nCount = 0;
}
//-----------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------
CParticle::~CParticle()
{
}
//-----------------------------------------------------------
// ����
//-----------------------------------------------------------
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, float fRadian, float fLength, TYPE Type, TEX_TYPE TexType)
{
	// CParticle�|�C���^
	CParticle *pParticle;

	// �������m��
	pParticle = new CParticle(7);

	//������
	pParticle->Init(pos, size, rot, col, move, fRadian, fLength, Type, TexType);

	// �|�C���^��Ԃ�
	return pParticle;
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
	return S_OK;
}
//----------------------------------------------------------
// �e�N�X�`���̔j��
//----------------------------------------------------------
void CParticle::Unload(void)
{
	// 3��J��Ԃ�
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
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, float fRadian, float fLength, TYPE Type, TEX_TYPE TexType)
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
	// �ړ���
	m_move = move;
	// �ʓx
	m_fRadian = fRadian;
	// ���a
	m_fLength = fLength;
	// �^�C�v�ݒ�
	m_Type = Type;
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

	// �g�嗦��1,0f��
	m_fScale = 1.0f;

	// �^�C�v�������̏ꍇ
	if (m_Type == TYPE_EXPLOSION)
	{
		// �g�嗦���Z�l��1.5f��
		m_fAddScale = 8.5f;

		// �J���[���Z�l��0.02f��
		m_fAddColor = 0.02f;
	}
	// �^�C�v���ΉԂ̏ꍇ
	if (m_Type == TYPE_SPARK)
	{
		// �g�嗦���Z�l��0.0f��
		m_fAddScale = 0.0f;

		// �J���[���Z�l��0.002f��
		m_fAddColor = 0.005f;
	}

	// �^�C�v�����̏ꍇ
	if (m_Type == TYPE_SMOKE)
	{
		// �g�嗦���Z�l�� 0.9f��
		m_fAddScale = 0.9f;

		// �J���[���Z�l��0.006f��
		m_fAddColor = 0.006f;
	}

	// TypeHit�̏ꍇ
	if (m_Type == TYPE_HIT)
	{
		// �g����Z�l0.0f��
		m_fAddScale = 0.0f;

		// �J���[���Z�l��0.006f��
		m_fAddColor = 0.1f;
	}

	// �^�C�v���}�Y���t���b�V���̏ꍇ
	if (m_Type == TYPE_MAZLE_FLASH)
	{
		// �g�嗦���Z�l��0.5f��
		m_fAddScale = 0.5f;

		// �J���[���Z�l��0.08f��
		m_fAddColor = 0.08f;
	}
	// 
	if (m_Type == TYPE_CIRCLE)
	{
		// �g�嗦���Z�l��0.0f��
		m_fAddScale = 0.0f;

		// �J���[���Z�l��0.01f��
		m_fAddColor = 0.05f;

		m_fAngle = 0.01f;

		// �J���[�^�C�v
		m_ColorType = COLOR_ADD;

		m_fRadian = m_fRadian * D3DX_PI * 2;

	}
	// �^�C�v���ΉԂłȂ��ꍇ
	if (m_Type != TYPE_SPARK)
	{
		// m_move��0.5�|����
		m_move *= 0.5f;
	}
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

	// �g��k��
	m_fScale += m_fAddScale;

	if (m_Type != TYPE_CIRCLE)
	{
		// �����Z
		m_col.a -= m_fAddColor;
	}


	// �^�C�v��Explosion�̏ꍇ
	if (m_Type == TYPE_EXPLOSION)
	{
		// �C���N�������g
		m_nCount++;
		// �J�E���g��5�ȏ�̏ꍇ
		if (m_nCount >= 10)
		{
			// Scale�̉��Z�l��1.5f��
			m_fAddScale = 0.5f;
		}
	}
	// �^�C�v��SPARK�̏ꍇ
	if (m_Type == TYPE_SPARK)
	{
		// �C���N�������g
		m_nCount++;
		// �J�E���g��5�ȏ�̏ꍇ
		if (m_nCount >= 2)
		{
			// Scale�̉��Z�l��1.5f��
			m_move.y -= 0.015f;
		}
	}
	// �^�C�v��CIRCLE�̏ꍇ
	if (m_Type == TYPE_CIRCLE)
	{
		m_fRadian += m_fAngle;

		// ���W�����߂�
		m_pos.x = /*m_pos.x +*/ cosf(m_fRadian) * m_fLength;
		m_pos.z = /*m_pos.z +*/ sinf(m_fRadian) * m_fLength;

		if (m_ColorType != COLOR_NONE)
		{
			if (m_ColorType == COLOR_ADD)
			{
				// a�l���Z
				m_col.a += m_fAddColor;
				// a�l��1.0f�ȏ�̏ꍇ
				if (m_col.a >= PARTICLE_CIRCLE_COL_MAX)
				{
					m_col.a = PARTICLE_CIRCLE_COL_MAX;
					m_ColorType = COLOR_MIN;
				}
			}
			if (m_ColorType == COLOR_MIN)
			{
				// a�l���Z
				m_col.a -= m_fAddColor;
				// a�l��0.5�ȉ��̏ꍇ
				if (m_col.a <= PARTICLE_CIRCLE_COL_MIN)
				{
					m_col.a = PARTICLE_CIRCLE_COL_MIN;
					m_ColorType = COLOR_ADD;
				}
			}
		}
	}
	// �J���[�ݒ�
	SetColor(m_col);

	// �g�嗦�ݒ�
	SetScale(m_fScale);

	// �ʒu�X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	// �ʒu���W�ݒ�
	SetPosition(m_pos);

	// ���l��0�ȉ��̏ꍇ
	if (m_col.a < 0.0f)
	{
		// �I��
		Uninit();
		// ������ʂ�Ȃ��悤��
		return;
	}
}
//-----------------------------------------------------------
// �`��
//-----------------------------------------------------------
void CParticle::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �^�C�v��EXPLOSION�̏ꍇ
	if (m_Type == TYPE_EXPLOSION || m_Type == TYPE_SPARK || m_Type == TYPE_CIRCLE)
	{
		// ���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// �`��
	CBillboard::Draw();

	// �^�C�v�������̏ꍇ
	if (m_Type == TYPE_EXPLOSION || m_Type == TYPE_SPARK || m_Type == TYPE_CIRCLE)
	{
		// ���ɖ߂�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}