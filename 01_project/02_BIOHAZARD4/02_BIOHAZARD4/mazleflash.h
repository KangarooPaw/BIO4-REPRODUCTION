//--------------------------------------------------------------------
// MazleFlash
// mazleflash.h
// Author : 管原 司
//--------------------------------------------------------------------
#ifndef _MAZLEFLASH_H_
#define _MAZLEFLASH_H_
#define MAZLE_FLASH_SIZE_X 5	// マズルフラッシュのサイズX
#define MAZLE_FLASH_SIZE_Y 5	// マズルフラッシュのサイズY
#include"particle.h"

//--------------------------------------------------------------------
//クラス
//--------------------------------------------------------------------
class CMazleFlash : public CParticle
{
public:
	CMazleFlash(int nPriority = OBJTYPE_PARTICLE);
	~CMazleFlash();
	static CMazleFlash *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	float m_fScale;			// 拡大率
	float m_fAddScale;		// 拡大加算値
	float m_fAddColor;		// カラー加算値
};
#endif
