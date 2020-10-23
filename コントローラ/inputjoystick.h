//---------------------------------------------------
// BG
// inputcontroller.h
// Authur:	管原司
//---------------------------------------------------
#ifndef _INPUT_JOYSTICK_H_
#define _INPUT_JOYSTICK_H_
#define INITGUID
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define JS_X 0
#define JS_Y 1
#define JS_A 2
#define JS_B 3
#define	NUM_JS_MAX (256)
class CInputJoystick : public CInput
{
public:
	CInputJoystick();
	~CInputJoystick();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetJoystickPress(int nKey);
	bool GetJoystickTrigger(int nKey);
	bool GetJoystickRelease(int nKey);
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	static LPDIRECTINPUTDEVICE8 GetDevice(void) { return m_pJDevice; }
private:
	static LPDIRECTINPUTDEVICE8 m_pJDevice;
	DIDEVCAPS	m_diDevCaps;	//Caps
	BYTE m_aJoyState[NUM_JS_MAX];// キーボードの入力情報ワーク
	BYTE m_aJoyStateTrigger[NUM_JS_MAX];	//キーボードトリガー情報
	BYTE m_aJoyStateRelease[NUM_JS_MAX];	// キーボードのリリース情報
};
#endif