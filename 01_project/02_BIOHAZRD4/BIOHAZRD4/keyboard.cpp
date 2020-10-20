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
	//入力デバイスの作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pInputDevice, NULL))) {
		return E_FAIL;
	}
	//データ・フォーマット設定
	if (FAILED(m_pInputDevice->SetDataFormat(&c_dfDIKeyboard))) {
		return E_FAIL;
	}
	//強調モード設定
	if (FAILED(m_pInputDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))) {
		return E_FAIL;
	}
	//キーボードへのアクセス権獲得
	m_pInputDevice->Acquire();

	return S_OK;
}

void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

void CInputKeyboard::Update(void)
{
	BYTE akeyState[NUM_KEY_MAX];//キーの最大数
	int nCntkey;

	//デバイスからデータ取得
	if (SUCCEEDED(m_pInputDevice->GetDeviceState(sizeof(akeyState), akeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			m_akeyStateTrigger[nCntkey] = (m_akeyState[nCntkey] ^ akeyState[nCntkey]) & akeyState[nCntkey];
			m_akeyStateRelease[nCntkey] = (m_akeyState[nCntkey] ^ akeyState[nCntkey]) & ~akeyState[nCntkey];
			m_akeyState[nCntkey] = akeyState[nCntkey];
		}
	}
	//キーボード更新処理
	else {
		//キーボードのアクセス権取得
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