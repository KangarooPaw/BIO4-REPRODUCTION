//--------------------------------------------------------------------
// CircleParticle
// circleparticle.h
// Author : �ǌ� �i
//--------------------------------------------------------------------
#ifndef _CIRCLEPARTICLE_H_
#define _CIRCLEPARTICLE_H_

#define PARTICLE_CIRCLE_SIZE_X 7			// �~�p�[�e�B�N���T�C�YX
#define PARTICLE_CIRCLE_SIZE_Y 200			// �~�p�[�e�B�N���T�C�YY
#define PARTICLE_CIRCLE_COL_MAX 0.5f		// a�l�ő�l
#define PARTICLE_CIRCLE_COL_MIN 0.1f		// a�l�ŏ��l

#include"particle.h"

//--------------------------------------------------------------------
//�N���X
//--------------------------------------------------------------------
class CCircleParticle : public CParticle
{
public:
	// �J���[���Z�A���Z
	typedef enum
	{
		COLOR_NONE = 0,
		COLOR_ADD,
		COLOR_MIN,
	}COLOR_TYPE;

	CCircleParticle();
	~CCircleParticle();
	static CCircleParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	COLOR_TYPE m_ColorType;	// �J���[�^�C�v
	float m_fRadian;		// �ʓx
	float m_fLength;		// ���a
	float m_fAngle;			// �p�x
	float m_fAddColor;		// �J���[���Z�l
};
#endif