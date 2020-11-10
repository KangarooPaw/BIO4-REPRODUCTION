//-----------------------------------------------------------
// キラキラエフェクト
// blood.h
// Author : 林川紗梨夏
//-----------------------------------------------------------
#ifndef _KIRA_H_
#define _KIRA_H_
//----------------------------------------------------
// マクロ定義
//----------------------------------------------------
#define KIRA_SIZE_X 5
#define KIRA_SIZE_Y 5
#define KIRA_LIFE 50


#include "billboard.h"
#include "particle.h"

class CKira : public CParticle
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BLOOD,
		TYPE_MAX,
	}TYPE;
	CKira(int nPriority = 5);
	~CKira();
	static CKira *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void EffectKira(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
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