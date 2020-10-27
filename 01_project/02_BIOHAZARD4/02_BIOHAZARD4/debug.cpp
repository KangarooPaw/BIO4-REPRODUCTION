//--------------------------------
//インクルードファイル
//--------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "debug.h"

//--------------------------------
//静的メンバ変数
//--------------------------------
LPD3DXFONT CDebugProc::m_pFont =NULL;
char CDebugProc::m_astr[1024] = {};

//--------------------------------
//コンストラクタ
//--------------------------------
CDebugProc::CDebugProc()
{
}

//--------------------------------
//デストラクタ
//--------------------------------
CDebugProc::~CDebugProc()
{
}

//--------------------------------
//初期化処理
//--------------------------------
void CDebugProc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();
	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//--------------------------------
//終了処理
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
//描画
//--------------------------------
void CDebugProc::Print(char * fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	vprintf(fmt, va_arg(list, char *));
	va_end(list);
}

//--------------------------------
//描画処理
//--------------------------------
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// テキスト描画
	m_pFont->DrawText(NULL, m_astr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
