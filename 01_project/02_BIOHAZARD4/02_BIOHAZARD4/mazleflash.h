//--------------------------------------------------------------------
// MazleFlash
// mazleflash.h
// Author : �ǌ� �i
//--------------------------------------------------------------------
#ifndef _MAZLEFLASH_H_
#define _MAZLEFLASH_H_
#define MAZLE_FLASH_SIZE_X 5	// �}�Y���t���b�V���̃T�C�YX
#define MAZLE_FLASH_SIZE_Y 5	// �}�Y���t���b�V���̃T�C�YY
#include"particle.h"

//--------------------------------------------------------------------
//�N���X
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
	float m_fScale;			// �g�嗦
	float m_fAddScale;		// �g����Z�l
	float m_fAddColor;		// �J���[���Z�l
};
#endif
