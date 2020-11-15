//-----------------------------------------------------------
// 木箱破壊エフェクト
// boxeffect.h
// Author : 林川紗梨夏
//-----------------------------------------------------------
#ifndef _BOXEFFECT_H_
#define _BOXEFFECT_H_
//----------------------------------------------------
// マクロ定義
//----------------------------------------------------
#define EFFECT_SIZE_X 20
#define EFFECT_SIZE_Y 20
#define EFFECT_LIFE 100

#include "billboard.h"

class CBoxEffect : public CBillboard
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_SHARD,
		TYPE_SMOKE,
		TYPE_MAX,
	}TYPE;
	CBoxEffect(int nPriority = OBJTYPE_BOX);
	~CBoxEffect();
	static CBoxEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void BreakBox(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
private:

	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];			// texture
	D3DXVECTOR3 m_pos;								// 位置座標
	D3DXVECTOR3 m_move;                             //移動量
	D3DXVECTOR3 m_rot;								// 向き
	D3DXVECTOR3 m_size;								// サイズ
	TYPE        m_type;                             //タイプ
	int         m_nPatternAnim; //アニメーションカウンタ
	int         m_nCounterAnim;//カウンタ
	D3DXCOLOR m_col;								// カラー
	int       m_nLife; //ライフ
};
#endif