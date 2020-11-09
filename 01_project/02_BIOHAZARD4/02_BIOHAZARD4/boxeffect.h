//-----------------------------------------------------------
// �ؔ��j��G�t�F�N�g
// boxeffect.h
// Author : �ѐ�ї���
//-----------------------------------------------------------
#ifndef _BOXEFFECT_H_
#define _BOXEFFECT_H_
//----------------------------------------------------
// �}�N����`
//----------------------------------------------------
#define EFFECT_SIZE_X 20
#define EFFECT_SIZE_Y 20
#define EFFECT_LIFE 100

#include "billboard.h"

class CBoxEffect : public CBillboard
{
public:
	CBoxEffect(int nPriority = 5);
	~CBoxEffect();
	static CBoxEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void BreakBox(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// texture
	D3DXVECTOR3 m_pos;								// �ʒu���W
	D3DXVECTOR3 m_move;                             //�ړ���
	D3DXVECTOR3 m_rot;								// ����
	D3DXVECTOR3 m_size;								// �T�C�Y
	D3DXCOLOR m_col;								// �J���[
	int       m_nLife; //���C�t
};
#endif