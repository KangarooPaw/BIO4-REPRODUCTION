//--------------------------------------------------------------------
// Explosion
// explosion.h
// Author : �ǌ� �i
//--------------------------------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define EXPLOSION_SIZE_X 10		// �����̃T�C�YX
#define EXPLOSION_SIZE_Y 10		// �����̃T�C�YY

#include"particle.h"

//--------------------------------------------------------------------
//�N���X
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
	D3DXVECTOR3 m_move;		// �ړ�
	float m_fScale;			// �g�嗦
	float m_fAddScale;		// �g����Z�l
	float m_fAddColor;		// �J���[���Z�l
	int m_nCount;			// �J�E���g
};
#endif