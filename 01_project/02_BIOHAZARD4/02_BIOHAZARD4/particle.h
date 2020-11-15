//--------------------------------------------------------------------
// Particle
// particle.h
// Author : �ǌ� �i
//--------------------------------------------------------------------
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "billboard.h"

class CParticle : public CBillboard
{
public:
	typedef enum
		// �e�N�X�`���^�C�v
	{
		TEX_TYPE_NONE = 0,
		TEX_TYPE_1,
		TEX_TYPE_2,
		TEX_TYPE_3,
		TEX_TYPE_BLOOD,//��
		TEX_TYPE_SHARD,//�ؕ�
		TEX_TYPE_BOXSMOKE,//���j��̉�
		TEX_TYPE_KIRA,//���炫��
		TEX_TYPE_MAX,
	}TEX_TYPE;
	CParticle(int nPriority = OBJTYPE_PARTICLE);
	~CParticle();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE m_TexType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_TYPE_MAX];	// texture
	D3DXVECTOR3 m_pos;									// �ʒu���W
	D3DXVECTOR3 m_rot;									// ����
	D3DXVECTOR3 m_size;									// �T�C�Y
	D3DXCOLOR m_col;									// �J���[
	TEX_TYPE m_TexType;									// �e�N�X�`���^�C�v
};
#endif