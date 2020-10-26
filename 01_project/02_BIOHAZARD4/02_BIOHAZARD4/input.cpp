#include "main.h"
#include "input.h"

LPDIRECTINPUT8 CInput::m_pInput = NULL;

CInput::CInput()
{
	m_pInputDevice = NULL;
}

CInput::~CInput()
{

}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Directlnputオブジェクトの作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))) {
		return E_FAIL;
	}
	return S_OK;
}

void CInput::Uninit(void)
{
	//入力デバイス開放
	if (m_pInputDevice != NULL) {
		//キーボードのアクセス権開放
		m_pInputDevice->Unacquire();
		m_pInputDevice->Release();
		m_pInputDevice = NULL;
	}
	//Directlnputオブジェクトの開放
	if (m_pInput != NULL) {
		m_pInput->Release();
		m_pInput = NULL;
	}
}

void CInput::Update(void)
{

}