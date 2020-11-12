//=============================================================================
//
// ゲームオーバー処理 [gameover.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//*****************************************************************************
//ヘッダファイルのインクルード
//*****************************************************************************
#include "mode.h"

#define TEXTURE_GAMEOVER	 "data/TEXTURE/gameover.png"
//*****************************************************************************
//クラス定義
//*****************************************************************************
class CGameover :public CMode
{
public:
	CGameover();
	~CGameover();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
private:
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif