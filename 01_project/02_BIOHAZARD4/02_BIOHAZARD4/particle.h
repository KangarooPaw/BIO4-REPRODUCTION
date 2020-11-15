//--------------------------------------------------------------------
// Particle
// particle.h
// Author : 管原 司
//--------------------------------------------------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "billboard.h"

class CParticle : public CBillboard
{
public:
	typedef enum
		// テクスチャタイプ
	{
		TEX_TYPE_NONE = 0,
		TEX_TYPE_1,
		TEX_TYPE_2,
		TEX_TYPE_3,
		TEX_TYPE_BLOOD,//血
		TEX_TYPE_SHARD,//木片
		TEX_TYPE_BOXSMOKE,//箱破壊の煙
		TEX_TYPE_KIRA,//きらきら
		TEX_TYPE_MAX,
	}TEX_TYPE;
	CParticle(int nPriority = OBJTYPE_PARTICLE);
	~CParticle();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE m_TexType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_TYPE_MAX];	// texture
	D3DXVECTOR3 m_pos;									// 位置座標
	D3DXVECTOR3 m_rot;									// 向き
	D3DXVECTOR3 m_size;									// サイズ
	D3DXCOLOR m_col;									// カラー
	TEX_TYPE m_TexType;									// テクスチャタイプ
};
#endif