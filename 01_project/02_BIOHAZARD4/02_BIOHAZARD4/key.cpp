//=============================================================================
//
// ���C�t���� [life.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "key.h"
#include <cmath>
#include "fade.h"
#include "game.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKey::CKey(int nPriority) : CScene(nPriority)
{
	memset(m_apKeyUi, 0, sizeof(m_apKeyUi));
	m_nKey = 0;
	m_fSizeWidth = 0;
	m_fSizeHeight = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKey::~CKey()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CKey::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	for (int nCntNum = 0; nCntNum < MAX_KEY; nCntNum++)
	{
		m_apKeyUi[nCntNum] = CKeyUi::Create(D3DXVECTOR3(m_pos.x + (m_fSizeWidth * nCntNum), m_pos.y, 0.0f), m_fSizeWidth, m_fSizeHeight);
	}
	SetKeyUi(m_nKey);
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CKey::Uninit(void)
{
	for (int nCntNum = 0; nCntNum < MAX_KEY; nCntNum++)
	{
		if (m_apKeyUi[nCntNum] != NULL)
		{
			m_apKeyUi[nCntNum]->Uninit();
			delete m_apKeyUi[nCntNum];
			m_apKeyUi[nCntNum] = NULL;
		}
	}

	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CKey::Update(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void CKey::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_KEY; nCntNum++)
	{
		if (m_apKeyUi[nCntNum] != NULL)
		{
			m_apKeyUi[nCntNum]->Draw();
		}
	}
}
//=============================================================================
// ��������
//=============================================================================
CKey * CKey::Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight)
{
	CKey *pKey = NULL;


		if (pKey == NULL)
		{
			pKey = new CKey;
			pKey->m_pos = pos;
			pKey->m_fSizeWidth = fSizeWidth;
			pKey->m_fSizeHeight = fSizeHeight;
			pKey->Init();
		}


	return pKey;
}
//=============================================================================
// ���C�t�̃Z�b�g����
//=============================================================================
void CKey::SetKeyUi(int nLife)
{
	m_nKey = nLife;

	if (m_nKey <= MAX_KEY)
	{
		for (int nCntStar = m_nKey; nCntStar < MAX_KEY; nCntStar++)
		{
			m_apKeyUi[nCntStar]->SetKey(CKeyUi::TYPE_NOGLOW);//���C�t�̐��ȍ~�̐����Â�����
		}
		for (int nCntStar = 0; nCntStar < m_nKey; nCntStar++) //���C�t�̐��܂ł̐������点��
		{
			m_apKeyUi[nCntStar]->SetKey(CKeyUi::TYPE_GLOW);
		}

	}
}