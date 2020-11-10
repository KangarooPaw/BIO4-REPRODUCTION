//--------------------------------------------------------------------
// Spark
// Spark.h
// Author : �ǌ� �i
//--------------------------------------------------------------------
#ifndef _SPARK_H_
#define _SPARK_H_

#define SPARK_SIZE_X 5.0f		// �ΉԂ̃T�C�YX
#define SPARK_SIZE_Y 50.0f		// �ΉԂ̃T�C�YY

#include"particle.h"

//--------------------------------------------------------------------
//�N���X
//--------------------------------------------------------------------
class CSpark : public CParticle
{
public:
	CSpark();
	~CSpark();
	static CSpark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3 m_move;		// �ړ�
	float m_fAddColor;		// �J���[���Z�l
	int m_nCount;			// �J�E���g
};
#endif