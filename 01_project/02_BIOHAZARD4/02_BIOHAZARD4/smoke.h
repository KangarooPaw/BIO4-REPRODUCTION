//--------------------------------------------------------------------
// Smoke
// smoke.h
// Author : 管原 司
//--------------------------------------------------------------------
#ifndef _SMOKE_H_
#define _SMOKE_H_

#define SMOKE_SIZE_X 10			// 煙のサイズX
#define SMOKE_SIZE_Y 10			// 爆発のサイズY

#include"particle.h"

//--------------------------------------------------------------------
//クラス
//--------------------------------------------------------------------
class CSmoke : public CParticle
{
public:
	CSmoke();
	~CSmoke();
	static CSmoke *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3 m_move;		// 移動
	float m_fScale;			// 拡大率
	float m_fAddScale;		// 拡大加算値
	float m_fAddColor;		// カラー加算値
};
#endif