//---------------------------------------------------
// joystick
// inputcontroller.cpp
// Author:	管原司
//---------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "inputkeyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "inputjoystick.h"
LPDIRECTINPUTDEVICE8 CInputJoystick::m_pJDevice = NULL;
//------------------------------------------------
//コンストラクタ
//------------------------------------------------
CInputJoystick::CInputJoystick()
{
	memset(m_aJoyState, 0, sizeof(m_aJoyState));
	memset(m_aJoyStateTrigger, 0, sizeof(m_aJoyStateTrigger));
	memset(m_aJoyStateRelease, 0, sizeof(m_aJoyStateRelease));
}
//------------------------------------------------
//デストラクタ
//------------------------------------------------
CInputJoystick::~CInputJoystick()
{
}
//------------------------------------------------
//初期化
//------------------------------------------------
HRESULT CInputJoystick::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT  hr;

	hr = CInput::Init(hInstance, hWnd);

	hr = m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY);

	if (m_pJDevice != NULL)
	{
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't create Device.", "Error", MB_OK);
			return FALSE;
		}

		hr = m_pJDevice->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't set data format.", "Error", MB_OK);
			return FALSE;
		}

		hr = m_pJDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't set cooperative level.", "Error", MB_OK);
			return FALSE;
		}

		m_diDevCaps.dwSize = sizeof(DIDEVCAPS);
		hr = m_pJDevice->GetCapabilities(&m_diDevCaps);
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't create device capabilities.", "Error", MB_OK);
			return FALSE;
		}

		hr = m_pJDevice->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);
		if (FAILED(hr)) {
			MessageBox(hWnd, "Can't set property.", "Error", MB_OK);
			return FALSE;
		}

		hr = m_pJDevice->Poll();
		if (FAILED(hr)) {
			hr = m_pJDevice->Acquire();
			while (hr == DIERR_INPUTLOST) {
				hr = m_pJDevice->Acquire();
			}
		}
	}
	return TRUE;
}
//------------------------------------------------
//終了
//------------------------------------------------
void CInputJoystick::Uninit(void)
{
	CInput::Uninit();
	if (m_pJDevice != NULL)
	{
		//デバイス制御の停止
		m_pJDevice->Unacquire();
		m_pJDevice->Release();
		m_pJDevice = NULL;
	}
}
//------------------------------------------------
//更新
//------------------------------------------------
void CInputJoystick::Update(void)
{
	int nCntKey;
	DIJOYSTATE js;

	if (m_pJDevice != NULL)
	{
		m_pJDevice->Poll();
		m_pJDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
		//デバイスからデータを取得
		if (SUCCEEDED(m_pJDevice->GetDeviceState(sizeof(DIJOYSTATE), &js)))
		{
			for (nCntKey = 0; nCntKey < NUM_JS_MAX; nCntKey++)
			{
				//キープレス情報を保存
				m_aJoyState[nCntKey] = m_aJoyState[nCntKey];

				//キートリガー
				m_aJoyStateTrigger[nCntKey] = (m_aJoyState[nCntKey] ^ js.rgbButtons[nCntKey]) &  js.rgbButtons[nCntKey];

				//キーリリース
				m_aJoyStateRelease[nCntKey] = (m_aJoyState[nCntKey] ^ js.rgbButtons[nCntKey]) & ~js.rgbButtons[nCntKey];

				//キープレス情報を保存
				m_aJoyState[nCntKey] = js.rgbButtons[nCntKey];
			}
		}
		else
		{
			m_pJDevice->Acquire();
		}
	}
}
//------------------------------------------------
//joystickPress
//------------------------------------------------
bool CInputJoystick::GetJoystickPress(int nKey)
{
	return m_aJoyState[nKey] & 0x80 ? true : false;
}
//------------------------------------------------
//joystickTrigger
//------------------------------------------------
bool CInputJoystick::GetJoystickTrigger(int nKey)
{
	return m_aJoyStateTrigger[nKey] & 0x80 ? true : false;
}
//------------------------------------------------
//joystickRelease
//------------------------------------------------
bool CInputJoystick::GetJoystickRelease(int nKey)
{
	return m_aJoyStateRelease[nKey] & 0x80 ? true : false;
}
//------------------------------------------------
//EnumJoysticksCallback
//------------------------------------------------
BOOL CALLBACK CInputJoystick::EnumJoysticksCallback(const DIDEVICEINSTANCE * pdidInstance, VOID * pContext)
{
	HRESULT hr;

	hr = m_pDInput->CreateDevice(pdidInstance->guidInstance, &m_pJDevice, NULL);

	if (FAILED(hr)) return DIENUM_CONTINUE;

	return DIENUM_STOP;
}
//------------------------------------------------
//EnumAxesCallback
//------------------------------------------------
BOOL CALLBACK CInputJoystick::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE * pdidoi, VOID * pContext)
{
	HRESULT     hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = 0 - 1000;
	diprg.lMax = 0 + 1000;
	hr = m_pJDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr)) return DIENUM_STOP;
	DWORD *pdwNumForceFeedbackAxis = (DWORD*)pContext;
	if ((pdidoi->dwFlags & DIDOI_FFACTUATOR) != 0) (*pdwNumForceFeedbackAxis)++;
	return DIENUM_CONTINUE;
}
