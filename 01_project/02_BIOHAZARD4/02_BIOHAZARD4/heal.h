//--------------------------------------------------------------------
// Heal
// heal.h
// Author : 管原 司
//--------------------------------------------------------------------
#ifndef _HEAL_H_
#define _HEAL_H_
#define HEAL_SIZE_X 5	// マズルフラッシュのサイズX
#define HEAL_SIZE_Y 5	// マズルフラッシュのサイズY

#include"particle.h"

//--------------------------------------------------------------------
//クラス
//--------------------------------------------------------------------
class CHeal : public CParticle
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_RHOMBUS,
	}TYPE;
	CHeal(int nPriority = OBJTYPE_PARTICLE);
	~CHeal();
	static CHeal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void HealCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col);
private:
	D3DXVECTOR3 m_move;		// 移動
	float m_fAddColor;		// カラー加算値
};
#endif
