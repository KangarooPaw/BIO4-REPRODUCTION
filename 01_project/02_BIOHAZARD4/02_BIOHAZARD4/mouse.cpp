#include "main.h"
#include "mouse.h"

CInputMouse::MSTATE CInputMouse::m_MState = {};

HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pInputDevice, NULL)))
	{
		return E_FAIL;
	}

	m_pInputDevice->SetDataFormat(&c_dfDIMouse2); //ϳ��p���ް��E̫�ϯĐݒ�
	m_pInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // ��Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j�i���Βl��DIPROPAXISMODE_REL�j
	m_pInputDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	SetRect(&m_MState.moveRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // �}�E�X�J�[�\���̓����͈�
	m_MState.x = m_MState.moveRect.left; // �}�E�X�J�[�\���̂w���W��������
	m_MState.y = m_MState.moveRect.top; // �}�E�X�J�[�\���̂x���W��������
	m_MState.moveAdd = 1; // �}�E�X�J�[�\���̈ړ��ʂ�ݒ�

	m_pInputDevice->Acquire();
	return S_OK;
}

/******************************************************************************
* �֐��� : UninitMouse
*
* ���� : void
* �߂�l : �Ȃ�
* ���� : �I������
*******************************************************************************/
void CInputMouse::Uninit(void)
{
	if (m_pInputDevice != NULL)
	{
		m_pInputDevice->Unacquire();
		m_pInputDevice = NULL;
	}

	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}


/******************************************************************************
* �֐��� : UpdateMouse
*
* ���� : void
* �߂�l : �Ȃ�
* ���� : �X�V����
*******************************************************************************/
void CInputMouse::Update(void)
{
	m_dIMouseState.rgbButtons[0] = 0;

	m_pInputDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_dIMouseState);
	m_pInputDevice->Acquire();

	m_MState.x += (m_dIMouseState.lX * m_MState.moveAdd);
	m_MState.y += (m_dIMouseState.lY * m_MState.moveAdd);
	if (m_MState.x < m_MState.moveRect.left) m_MState.x = m_MState.moveRect.left;
	if (m_MState.x > m_MState.moveRect.right - m_MState.imgWidth) m_MState.x = m_MState.moveRect.right - m_MState.imgWidth;
	if (m_MState.y < m_MState.moveRect.top) m_MState.y = m_MState.moveRect.top;
	if (m_MState.y > m_MState.moveRect.bottom - m_MState.imgHeight) m_MState.y = m_MState.moveRect.bottom - m_MState.imgHeight;
	(m_dIMouseState.rgbButtons[0] & 0x80) ? m_MState.lButton = true : m_MState.lButton = false;
	(m_dIMouseState.rgbButtons[1] & 0x80) ? m_MState.rButton = true : m_MState.rButton = false;
	(m_dIMouseState.rgbButtons[2] & 0x80) ? m_MState.cButton = true : m_MState.cButton = false;
}

bool CInputMouse::GetMouseTriggerLeft(void)
{
	/* �O�Ɏ擾�������̃}�E�X�̏�� */
	static bool prevState[sizeof(m_dIMouseState.rgbButtons) / sizeof(m_dIMouseState.rgbButtons[0])];
	/* ���̃}�E�X�̏�� */
	bool current = m_MState.lButton;
	/* �O�̏�Ԃ�false�ŁA���̏�Ԃ�true�Ȃ�΁A�N���b�N�����u�ԂƔ��肷�� */
	bool ret = current && !prevState[0];
	/* ���̏�Ԃ�ۑ����� */
	prevState[0] = current;
	/* ���茋�ʂ�Ԃ� */
	return ret;
}

bool CInputMouse::GetMouseTriggerRight(void)
{
	/* �O�Ɏ擾�������̃}�E�X�̏�� */
	static bool prevState[sizeof(m_dIMouseState.rgbButtons) / sizeof(m_dIMouseState.rgbButtons[0])];
	/* ���̃}�E�X�̏�� */
	bool current = m_MState.rButton;
	/* �O�̏�Ԃ�false�ŁA���̏�Ԃ�true�Ȃ�΁A�N���b�N�����u�ԂƔ��肷�� */
	bool ret = current && !prevState[0];
	/* ���̏�Ԃ�ۑ����� */
	prevState[0] = current;
	/* ���茋�ʂ�Ԃ� */
	return ret;
}

CInputMouse::MSTATE *CInputMouse::GetMouse(void)
{
	return &m_MState;
}