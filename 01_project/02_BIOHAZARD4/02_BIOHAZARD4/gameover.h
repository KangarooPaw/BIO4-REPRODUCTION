//=============================================================================
//
// �Q�[���I�[�o�[���� [gameover.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mode.h"

#define TEXTURE_GAMEOVER	 "data/TEXTURE/gameover.png"
//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CGameover :public CMode
{
public:
	CGameover();
	~CGameover();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
private:
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif