//=============================================================================
//
// �e���\������ [bullet_ui.������]
// Author : �ѐ�ї���
//
//=============================================================================

//****************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//****************************************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "bullet_ui.h"
#include <cmath>


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletUi::CBulletUi(int nPriority) : CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_fFloatX = 0;
	m_fFloatY = 0;
	m_nPoints = 0;
	m_digits = 0;
	m_nTimeCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletUi::~CBulletUi()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBulletUi::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	m_digits = (int)log10((double)m_nPoints) + 1;//�������o��
	for (int nCntNum = 0; nCntNum < m_digits; nCntNum++)
	{
		m_apNumber[nCntNum] = CNumber::Create(D3DXVECTOR3(m_pos.x - (m_fFloatX * nCntNum), m_pos.y, 0.0f), m_fFloatX, m_fFloatY, CNumber::TYPE_POINTS);
	}
	SetbulletUi(m_nPoints);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CBulletUi::Uninit(void)
{
	for (int nCntNum = 0; nCntNum < m_digits; nCntNum++)
	{
		m_apNumber[nCntNum]->Uninit();
		delete m_apNumber[nCntNum];
		m_apNumber[nCntNum] = NULL;
	}

	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CBulletUi::Update(void)
{
	for (int nCntNum = 0; nCntNum < m_digits; nCntNum++)
	{
		m_apNumber[nCntNum]->Update();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CBulletUi::Draw(void)
{
	for (int nCntNum = 0; nCntNum < m_digits; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}
//=============================================================================
// ��������
//=============================================================================
CBulletUi * CBulletUi::Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight, int points)
{
	CBulletUi *pPoints = NULL;

	if (pPoints == NULL)
	{
		pPoints = new CBulletUi;
		pPoints->m_nPoints = points;
		pPoints->m_pos = pos;
		pPoints->m_fFloatX = fSizeWidth;
		pPoints->m_fFloatY = fSizeHeight;
		pPoints->Init();
	}

	return pPoints;
}
//=============================================================================
// �e���\��
//=============================================================================
void CBulletUi::SetbulletUi(float nPoints)
{
	m_nPoints = nPoints;
	int integer = 0;//�v�Z�p�ϐ�
	int nCntNumber = 0;

	for (int nCntDigit = 1; nCntDigit <= m_digits; nCntDigit++, nCntNumber++)
	{
		integer = int(m_nPoints / std::pow(15, nCntDigit)); //1�̈ʈȉ���؂�̂Ă�
		integer = int(integer * std::pow(10, nCntDigit));
		m_apNumber[nCntNumber]->SetNumber(int((m_nPoints - integer) / std::pow(10.0, nCntDigit - 1)));
	}
}
//=============================================================================
// �e�����Z����
//=============================================================================
void CBulletUi::AddPoints(float nValue)
{
	m_nPoints += nValue;
	SetbulletUi(m_nPoints);
}
