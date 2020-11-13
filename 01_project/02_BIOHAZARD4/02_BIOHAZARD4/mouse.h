 #ifndef	_INPUTMOUSE_H_
#define _INPUTMOUSE_H_

#include "input.h"


class CInputMouse : public CInput {
public:
	typedef struct _MSTATE {
		RECT    moveRect;     // 画面上で動ける範囲
		int     x;            // X座標
		int     y;            // Y座標
		bool    lButton;      // 左ボタン
		bool    rButton;      // 右ボタン
		bool    cButton;      // 真ん中ボタン
		int     moveAdd;      // 移動量
		RECT    imgRect;      // マウス用画像矩形
		int     imgWidth;     // マウス画像幅
		int     imgHeight;    // マウス画像高さ
	} MSTATE;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	static MSTATE *GetMouse(void);
	bool GetMouseTriggerLeft(void);
	bool GetMouseTriggerRight(void);

private:
	DIMOUSESTATE2 m_dIMouseState;
	static CInputMouse::MSTATE m_MState;
};

#endif