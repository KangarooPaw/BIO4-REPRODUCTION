//--------------------------------------------------------------------
// Smoke
// smoke.h
// Author : �ǌ� �i
//--------------------------------------------------------------------
#ifndef _SMOKE_H_
#define _SMOKE_H_

#define SMOKE_SIZE_X 10			// ���̃T�C�YX
#define SMOKE_SIZE_Y 10			// �����̃T�C�YY

#include"particle.h"

//--------------------------------------------------------------------
//�N���X
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
	D3DXVECTOR3 m_move;		// �ړ�
	float m_fScale;			// �g�嗦
	float m_fAddScale;		// �g����Z�l
	float m_fAddColor;		// �J���[���Z�l
};
#endif