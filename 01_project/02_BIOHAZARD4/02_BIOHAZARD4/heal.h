//--------------------------------------------------------------------
// Heal
// heal.h
// Author : �ǌ� �i
//--------------------------------------------------------------------
#ifndef _HEAL_H_
#define _HEAL_H_
#define HEAL_SIZE_X 5	// �}�Y���t���b�V���̃T�C�YX
#define HEAL_SIZE_Y 5	// �}�Y���t���b�V���̃T�C�YY

#include"particle.h"

//--------------------------------------------------------------------
//�N���X
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
	D3DXVECTOR3 m_move;		// �ړ�
	float m_fAddColor;		// �J���[���Z�l
};
#endif
