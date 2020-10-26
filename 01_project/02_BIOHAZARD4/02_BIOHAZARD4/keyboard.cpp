#include "keyboard.h"

CInputKeyboard::CInputKeyboard()
{
	memset(m_akeyState, 0, sizeof(m_akeyState));
	memset(m_akeyStateTrigger, 0, sizeof(m_akeyStateTrigger));
	memset(m_akeyStateRelease, 0, sizeof(m_akeyStateRelease));
}

CInputKeyboard::~CInputKeyboard()
{

}

HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//���̓f�o�C�X�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pInputDevice, NULL))) {
		return E_FAIL;
	}
	//�f�[�^�E�t�H�[�}�b�g�ݒ�
	if (FAILED(m_pInputDevice->SetDataFormat(&c_dfDIKeyboard))) {
		return E_FAIL;
	}
	//�������[�h�ݒ�
	if (FAILED(m_pInputDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))) {
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X���l��
	m_pInputDevice->Acquire();

	return S_OK;
}

void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

void CInputKeyboard::Update(void)
{
	BYTE akeyState[NUM_KEY_MAX];//�L�[�̍ő吔
	int nCntkey;

	//�f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pInputDevice->GetDeviceState(sizeof(akeyState), akeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			m_akeyStateTrigger[nCntkey] = (m_akeyState[nCntkey] ^ akeyState[nCntkey]) & akeyState[nCntkey];
			m_akeyStateRelease[nCntkey] = (m_akeyState[nCntkey] ^ akeyState[nCntkey]) & ~akeyState[nCntkey];
			m_akeyState[nCntkey] = akeyState[nCntkey];
		}
	}
	//�L�[�{�[�h�X�V����
	else {
		//�L�[�{�[�h�̃A�N�Z�X���擾
		m_pInputDevice->Acquire();
	}
}

bool CInputKeyboard::GetKeyPress(int nKey)
{
	return (m_akeyState[nKey] & 0x80) ? true : false;
}
bool CInputKeyboard::GetKeyTrigger(int nKey)
{
	return (m_akeyStateTrigger[nKey] & 0x80) ? true : false;

}
bool CInputKeyboard::GetKeyRelease(int nKey)
{
	return (m_akeyStateRelease[nKey] & 0x80) ? true : false;
}