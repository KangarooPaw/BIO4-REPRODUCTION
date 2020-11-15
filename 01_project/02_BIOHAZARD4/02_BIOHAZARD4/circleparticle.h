//--------------------------------------------------------------------
// CircleParticle
// circleparticle.h
// Author : �ǌ� �i
//--------------------------------------------------------------------
#ifndef _CIRCLEPARTICLE_H_
#define _CIRCLEPARTICLE_H_

#define PARTICLE_CIRCLE_SIZE_X 4			// �~�p�[�e�B�N���T�C�YX
#define PARTICLE_CIRCLE_SIZE_Y 50			// �~�p�[�e�B�N���T�C�YY
#define PARTICLE_CIRCLE_COL_MAX 0.5f		// a�l�ő�l
#define PARTICLE_CIRCLE_COL_MIN 0.1f		// a�l�ŏ��l
#define MAX_CIRCLE 20						// �~�̍ő�

#include"particle.h"

//--------------------------------------------------------------------
//�N���X
//--------------------------------------------------------------------
class CCircleParticle : public CParticle
{
public:

	CCircleParticle(int nPriority = 5);
	~CCircleParticle();
	static CCircleParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void CircleCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, int nMax, float fLength);
private:
	D3DXVECTOR3 m_pos;		// �ʒu���W
	float m_fRadian;		// �ʓx
	float m_fLength;		// ���a
	float m_fAngle;			// �p�x
	float m_fAddColor;		// �J���[���Z�l
};
#endif