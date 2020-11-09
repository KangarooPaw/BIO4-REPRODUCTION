//--------------------------------------------------------------------
// Explosion
// explosion.h
// Author : 管原 司
//--------------------------------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define EXPLOSION_SIZE_X 10		// 爆発のサイズX
#define EXPLOSION_SIZE_Y 10		// 爆発のサイズY

#include"particle.h"

//--------------------------------------------------------------------
//クラス
//--------------------------------------------------------------------
class CExplosion : public CParticle
{
public:
	CExplosion();
	~CExplosion();
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3 m_move;		// 移動
	float m_fScale;			// 拡大率
	float m_fAddScale;		// 拡大加算値
	float m_fAddColor;		// カラー加算値
	int m_nCount;			// カウント
};
#endif