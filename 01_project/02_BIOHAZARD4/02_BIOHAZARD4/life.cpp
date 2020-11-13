//---------------------------------------------------
// Life
// Life.cpp
// Author:	�ǌ� �i
//---------------------------------------------------

//---------------------------------------------------
//�C���N���[�h�t�@�C��
//---------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "keyboard.h"
#include "life.h"
#include "player.h"

//--------------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
int CLife::m_nDamageCnt = 0;
bool CLife::m_bHit = false;
bool CLife::m_bHerb = false;
//--------------------------------------------------
//�R���X�g���N�^
//--------------------------------------------------
CLife::CLife(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_col = D3DCOLOR((0.0f, 0.0f, 0.0f, 0.0f));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Fade = FADE_NONE;
	m_State = STATE_NONE;
	m_fRadian = 0.0f;
	m_fLengh = 0.0f;
	m_nCnt = 0;
}

//--------------------------------------------------
//�f�X�g���N�^
//--------------------------------------------------
CLife::~CLife()
{

}

//--------------------------------------------------
//�����֐�
//--------------------------------------------------
CLife * CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float Length)
{
	//CPolygon�N���X�̃|�C���^
	CLife * pLife;

	//�������m��
	pLife = new CLife;

	// pos���
	pLife->m_pos = pos;
	// �T�C�Y���
	pLife->m_size = size;
	// ���a���
	pLife->m_fLengh = Length;

	//������
	pLife->Init();

	//CPolygon�̃|�C���^��Ԃ�
	return pLife;
}

//----------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//----------------------------------------------------------
HRESULT CLife::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/tezyo.png", &m_pTexture);
	return S_OK;
}

//----------------------------------------------------------
// �e�N�X�`���̔j��
//----------------------------------------------------------
void CLife::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		// �e�N�X�`��Release
		m_pTexture->Release();

		// m_pTexture��NULL��
		m_pTexture = NULL;
	}
}

//--------------------------------------------------
//������
//--------------------------------------------------
HRESULT CLife::Init(void)
{
	// �J���[
	m_col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	// �p�x
	float fAngle = 0.01f;

	m_pScene2D = new CScene2D(5);
	// ������
	m_pScene2D->Init();
	// �T�C�Y�ݒ�
	m_pScene2D->SetSize(D3DXVECTOR3(440.0f, 440.0f, 0.0f));
	// �J���[�ݒ�
	m_pScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	// �����̐ݒ�
	m_pScene2D->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// �ʒu�ݒ�
	m_pScene2D->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y + 128, m_pos.z));
	// �e�N�X�`���󂯓n��
	m_pScene2D->BindTexture(m_pTexture);

	// 100��J��Ԃ�
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		// �������m��
		m_apScene2D[nCnt] = new CScene2D(5);
		// ������
		m_apScene2D[nCnt]->Init();
		// �T�C�Y�ݒ�
		m_apScene2D[nCnt]->SetSize(m_size);
		// �J���[�ݒ�
		m_apScene2D[nCnt]->SetColor(m_col);
		// �����̐ݒ�
		m_apScene2D[nCnt]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(3.6f * nCnt)));
		// �Ǔx
		m_fRadian = (float)nCnt / MAX_LIFE;
		m_fRadian = m_fRadian * D3DX_PI * 2 + fAngle;
		// ���W�����߂�
		m_pos.x = m_pos.x - cosf(m_fRadian) * m_fLengh;
		m_pos.y = m_pos.y + sinf(m_fRadian) * m_fLengh;
		// �ʒu�ݒ�
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(m_pos));
	}
	//�_��
	m_Fade = FADE_OUT;
	//�΂ɐݒ�
	m_State = STATE_GREEN;

	return S_OK;
}

//--------------------------------------------------
//�I��
//--------------------------------------------------
void CLife::Uninit(void)
{
	//�j��
	Release();
}

//--------------------------------------------------
//�X�V
//--------------------------------------------------
void CLife::Update(void)
{
	//100��J��Ԃ�
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		//�X�V
		m_apScene2D[nCnt]->Update();
		if (nCnt >= m_nCnt)
		{
			//�J���[�ݒ�
			m_apScene2D[nCnt]->SetColor(m_col);
		}
	}
	if (m_Fade != FADE_NONE)
	{
		//�t�F�[�h�C��
		if (m_Fade == FADE_IN)
		{
			//�΂̏ꍇ
			if (m_State == STATE_GREEN)
			{
				//g�l�����Z
				m_col.r = 0.0f;
				m_col.g += FADE_RATE;
				//��ʂ������Ȃ�����
				if (m_col.g >= 1.0f)
				{
					//�t�F�[�h�I������
					m_col.g = 1.0f;
					m_Fade = FADE_OUT;
				}
			}
			//���F�̏ꍇ
			if (m_State == STATE_YELLOW)
			{
				m_col.r = 1.0f;
				m_col.g = 1.0f;
				m_col.r += FADE_RATE;
				//g�l�����Z
				m_col.g += FADE_RATE;
				//��ʂ������Ȃ�����
				if (m_col.g >= 1.0f && m_col.r >= 1.0f)
				{
					//�t�F�[�h�I������
					m_col.r = 1.0f;
					m_col.g = 1.0f;
					m_Fade = FADE_OUT;
				}
			}
			//�Ԃ̏ꍇ
			if (m_State == STATE_RED)
			{
				m_col.g = 0.0f;
				//g�l�����Z
				m_col.r += FADE_RATE;
				//��ʂ������Ȃ�����
				if (m_col.r >= 1.0f)
				{
					//�t�F�[�h�I������
					m_col.r = 1.0f;
					m_Fade = FADE_OUT;
				}
			}
		}
		//�t�F�[�h�A�E�g
		if (m_Fade == FADE_OUT)
		{
			//�΂̏ꍇ
			if (m_State == STATE_GREEN)
			{
				m_col.r = 0.0f;
				//g�l�����Z
				m_col.g -= FADE_RATE;
				//��ʂ̓���
				if (m_col.g <= 0.5f)
				{
					//�t�F�[�h�����؂�ւ�
					m_col.g = 0.5f;
					//���[�h�ݒ�
					m_Fade = FADE_IN;
				}
			}
			//�΂̏ꍇ
			if (m_State == STATE_YELLOW)
			{
				//g�l�����Z
				m_col.r -= FADE_RATE;
				m_col.g -= FADE_RATE;
				//��ʂ̓���
				if (m_col.g <= 0.5f || m_col.r <= 0.5f)
				{
					//col�ݒ�
					m_col.r = 0.5f;
					m_col.g = 0.5f;
					//�t�F�[�h�����؂�ւ�
					m_Fade = FADE_IN;
				}
			}
			//�΂̏ꍇ
			if (m_State == STATE_RED)
			{
				m_col.g = 0.0f;
				//r�l�����Z
				m_col.r -= FADE_RATE;
				//��ʂ̓���
				if (m_col.r <= 0.5f)
				{
					//�t�F�[�h�����؂�ւ�
					m_col.r = 0.5f;
					//���[�h�ݒ�
					m_Fade = FADE_IN;
				}
			}
		}
	}

	//�J�E���g��0�ȏ�̏ꍇ
	if (m_nCnt > 0 && m_nCnt < 100)
	{
		if (m_State == STATE_GREEN)
		{
			//�J���[�ݒ�
			m_apScene2D[m_nCnt]->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		if (m_State == STATE_YELLOW)
		{
			//�J���[�ݒ�
			m_apScene2D[m_nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
		if (m_State == STATE_RED)
		{
			//�J���[�ݒ�
			m_apScene2D[m_nCnt]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	//100���Ⴂ�ꍇ
	if (m_nCnt < MAX_LIFE && m_nCnt >= 0)
	{
		//�J���[�ݒ�
		m_apScene2D[m_nCnt]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	//�_���[�W���󂯂Ă���Ȃ�
	if (m_bHit == true)
	{
		//�̗͌���
		m_nCnt++;
		m_nDamageCnt--;
		//�_���[�W�����炵����
		if (m_nDamageCnt == 0)
		{
			m_bHit = false;
		}
	}

	if (m_bHerb == true)
	{
		if (m_nCnt != 0)
		{
			//�̗͑���
			m_nCnt--;
		}
		m_nDamageCnt--;
		//�_���[�W���񕜂��邩�S�񕜂�����
		if (m_nDamageCnt == 0)
		{
			m_bHerb = false;
			m_nDamageCnt = 0;
		}

	}
	//�J�E���g��50���Ⴂ�ꍇ
	if (m_nCnt < 50)
	{
		//State��Green��
		m_State = STATE_GREEN;
	}
	//�J�E���g��50�ȏォ��80���Ⴂ�ꍇ
	if (m_nCnt >= 50 && m_nCnt < 80)
	{
		//State��Yellow��
		m_State = STATE_YELLOW;
	}
	//�J�E���g��80�ȏ�̏ꍇ
	if (m_nCnt >= 80)
	{
		//State��Red��
		m_State = STATE_RED;
	}
	//�J�E���g���ő�̗͂ɒB�����ꍇ
	if (m_nCnt >= MAX_LIFE)
	{
		CPlayer::DeathFlag();
	}
}

//--------------------------------------------------
//�`��
//--------------------------------------------------
void CLife::Draw(void)
{

}

//--------------------------------------------------
//�̗͂̌�������
//--------------------------------------------------
void CLife::LifeDecrement(int nDamage)
{
	m_nDamageCnt = nDamage;
	m_bHit = true;
}

//--------------------------------------------------
//�̗͂̑�������
//--------------------------------------------------
void CLife::LifeIncrement(int nDamage)
{
	m_nDamageCnt = nDamage;
	m_bHerb = true;
}
