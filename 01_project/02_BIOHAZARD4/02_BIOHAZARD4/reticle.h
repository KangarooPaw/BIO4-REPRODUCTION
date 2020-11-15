//-----------------------------------------------------------
// Reticle
// reticle.h
// Author : �ǌ��@�i
//-----------------------------------------------------------
#ifndef _RETICLE_H_
#define _RETICLE_H_
//----------------------------------------------------
// �}�N����`
//----------------------------------------------------
#define RETICLE_SIZE_X 4.0f
#define RETICLE_SIZE_Y 5.0f

#include "billboard.h"

class CReticle : public CBillboard
{
public:
	CReticle(int nPriority = OBJTYPE_UI);
	~CReticle();
	static CReticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// texture
	D3DXVECTOR3 m_pos;								// �ʒu���W
	D3DXVECTOR3 m_rot;								// ����
	D3DXVECTOR3 m_size;								// �T�C�Y
	D3DXCOLOR m_col;								// �J���[
};
#endif