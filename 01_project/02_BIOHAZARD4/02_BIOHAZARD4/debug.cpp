//--------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debug.h"

//--------------------------------
//�ÓI�����o�ϐ�
//--------------------------------
LPD3DXFONT CDebugProc::m_pFont =NULL;
char CDebugProc::m_astr[1024] = {};

//--------------------------------
//�R���X�g���N�^
//--------------------------------
CDebugProc::CDebugProc()
{
}

//--------------------------------
//�f�X�g���N�^
//--------------------------------
CDebugProc::~CDebugProc()
{
}

//--------------------------------
//����������
//--------------------------------
void CDebugProc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//--------------------------------
//�I������
//--------------------------------
void CDebugProc::Uninit(void)
{
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//--------------------------------
//�`��
//--------------------------------
void CDebugProc::Print(char * fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	vprintf(fmt, va_arg(list, char *));
	va_end(list);
}

//--------------------------------
//�`�揈��
//--------------------------------
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, m_astr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
