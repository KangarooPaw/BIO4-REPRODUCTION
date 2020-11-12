//=============================================================================
//
// �Q�[������ [game.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mode.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CPlayer;
class CBulletUi;
//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CGame :public CMode
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer(void);
	static CBulletUi *GetBulletUi(void);
	static CBulletUi *GetBulletHaveUi(void);
private:
	static CPlayer *m_pPlayer;	//�v���C���[
	static CBulletUi *m_pBulletUi;//�e�̎c�e���\��
	static CBulletUi *m_pBulletHaveUi;//�����Ă���e���\��
	int m_nCount;
};

#endif