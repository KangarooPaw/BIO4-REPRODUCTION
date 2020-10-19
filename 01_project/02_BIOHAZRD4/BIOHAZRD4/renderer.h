#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"
//レンダリングクラス
class CRenderer
{
public:
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
	CRenderer();	//コンストラクタ
	~CRenderer();	//デストラクタ
	HRESULT Init(HWND hWnd, bool bWindow);	//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

private:

	void DrawFPS(void);

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
	int						m_nCountFPS;			// FPSカウンタ
#endif
};
#endif // !_RENDERER_H_
