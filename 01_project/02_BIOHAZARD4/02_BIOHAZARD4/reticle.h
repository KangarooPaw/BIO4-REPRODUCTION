//-----------------------------------------------------------
// Reticle
// reticle.h
// Author : 管原　司
//-----------------------------------------------------------
#ifndef _RETICLE_H_
#define _RETICLE_H_
//----------------------------------------------------
// マクロ定義
//----------------------------------------------------
#define RETICLE_SIZE_X 2
#define RETICLE_SIZE_Y 2

#include "billboard.h"

class CReticle : public CBillboard
{
public:
	CReticle(int nPriority = 5);
	~CReticle();
	static CReticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// texture
	D3DXVECTOR3 m_pos;								// 位置座標
	D3DXVECTOR3 m_rot;								// 向き
	D3DXVECTOR3 m_size;								// サイズ
	D3DXCOLOR m_col;								// カラー
};
#endif