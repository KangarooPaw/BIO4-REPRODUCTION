//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mode.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CTutorial :public CMode
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif