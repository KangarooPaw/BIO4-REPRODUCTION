//--------------------------------
//インプット処理
//--------------------------------

//--------------------------------
//インクルードファイル
//--------------------------------
#include "main.h"
#include "input.h"

//--------------------------------
//静的メンバ変数
//--------------------------------
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//--------------------------------
//コンストラクタ
//--------------------------------
CInput::CInput()
{
	m_pInputDevice = NULL;
}

//--------------------------------
//デストラクタ
//--------------------------------
CInput::~CInput()
{

}

//--------------------------------
//初期化処理
//--------------------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Directlnputオブジェクトの作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))) {
		return E_FAIL;
	}
	return S_OK;
}

//--------------------------------
//終了処理
//--------------------------------
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

//--------------------------------
//更新処理
//--------------------------------
void CInput::Update(void)
{

}