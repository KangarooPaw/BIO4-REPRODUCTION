//-----------------------------------------------------------
// Billboard
// billboard.h
// Author : �ǌ��@�i
//-----------------------------------------------------------
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "scene.h"
//-----------------------------------------------
//�N���X
//-----------------------------------------------
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = 3);
	~CBillboard();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	void SetScale(float fScale);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu���W
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXVECTOR3 m_rot;						// ����
	D3DXCOLOR m_col;						// �J���[
	D3DXMATRIX m_mtxWorld;					// �}�g���b�N�X
	float m_fScale;							// �g��
};
#endif