//----------------------------------------------------------------
// ButtonUI
// button_ui.cpp
// Author : �ǌ� �i
//----------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "button_ui.h"
//----------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//----------------------------------------------------------------
LPDIRECT3DTEXTURE9 CButton_UI::m_apTexture[TYPE_MAX] = {};

bool CButton_UI::m_bUse = true;
//----------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------
CButton_UI::CButton_UI(int nPriority) : CScene2D(nPriority)
{
	m_Type = TYPE_NONE;
	m_bUse = true;
}
//----------------------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------------------
CButton_UI::~CButton_UI()
{
}
//----------------------------------------------------------------
// ����
//----------------------------------------------------------------
CButton_UI * CButton_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	// CButton_UI�̃|�C���^
	CButton_UI *pButton_UI;
	// �������m��
	pButton_UI = new CButton_UI(OBJTYPE_UI);
	// ����������
	pButton_UI->Init(pos, size, nType);
	return pButton_UI;
}
//----------------------------------------------------------------
// �e�N�X�`���ǂݍ���
//----------------------------------------------------------------
HRESULT CButton_UI::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pickupUI.png", &m_apTexture[TYPE_PICKUP]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/turn.png", &m_apTexture[TYPE_SPIN]);

	return S_OK;
}
//----------------------------------------------------------------
// �e�N�X�`���j��
//----------------------------------------------------------------
void CButton_UI::Unload(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			// �e�N�X�`��Release
			m_apTexture[nCnt]->Release();

			// m_pTexture��NULL��
			m_apTexture[nCnt] = NULL;
		}
	}
}
//----------------------------------------------------------------
// ������
//----------------------------------------------------------------
HRESULT CButton_UI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	// �^�C�v���
	m_Type = nType;
	// ������
	CScene2D::Init();
	// �ʒu���W�ݒ�
	SetPosition(pos);
	// �T�C�Y�ݒ�
	SetSize(size);
	// �����̐ݒ�
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// �F�ݒ�
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	// �e�N�X�`���󂯓n��
	BindTexture(m_apTexture[m_Type]);

	return S_OK;
}
//----------------------------------------------------------------
// �I��
//----------------------------------------------------------------
void CButton_UI::Uninit(void)
{
	// �I��
	CScene2D::Uninit();
}
//----------------------------------------------------------------
// �X�V
//----------------------------------------------------------------
void CButton_UI::Update(void)
{
	// �X�V
	CScene2D::Update();
	// m_bUse��false�̏ꍇ
	if (m_bUse == false)
	{
		// �I��
		Uninit();
		return;
	}
}
//----------------------------------------------------------------
// �`��
//----------------------------------------------------------------
void CButton_UI::Draw(void)
{
	// �`��
	CScene2D::Draw();
}
//----------------------------------------------------------------
// �g�p����
//----------------------------------------------------------------
void CButton_UI::SetbUse(bool bUse)
{
	// ������
	m_bUse = bUse;
}