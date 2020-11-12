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
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }
	void SetTexture(float fTexX, float fTexY, float fTexX2, float fTexY2);
	void SetScale(float fScale);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetAlpha(int nAlpha);
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu���W
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXVECTOR3 m_rot;						// ����
	D3DXCOLOR m_col;	// �J���[
	float                              m_fTexX;      //�e�N�X�`��X���W
	float                              m_fTexX2;      //�e�N�X�`��X2���W
	float                              m_fTexY;      //�e�N�X�`��Y���W
	float                              m_fTexY2;      //�e�N�X�`��Y���W
	D3DXMATRIX m_mtxWorld;					// �}�g���b�N�X
	float m_fScale;							// �g��
	int m_nAlpha;							// ���ߒl
};
#endif