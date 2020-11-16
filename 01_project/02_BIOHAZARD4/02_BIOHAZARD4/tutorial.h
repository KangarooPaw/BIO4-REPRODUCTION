//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//****************************************************************************************************
//�w�b�_�t�@�C���̃C���N���[�h
//****************************************************************************************************
#include "mode.h"


class CPlayer;
class CBulletUi;
class CKey;
class CGate;
//****************************************************************************************************
//�N���X��`
//****************************************************************************************************
class CTutorial :public CMode
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static CPlayer *m_pPlayer;	//�v���C���[
	static CBulletUi *m_pBulletUi;//�e�̎c�e���\��
	static CBulletUi *m_pBulletHaveUi;//�����Ă���e���\��
	static CKey *m_pKey;//�����Ă���J�M�\��
	static CGate *m_pGate;				// ��
	int m_nCount;
	bool m_bSoundGameStart;	//�Q�[���X�^�[�g�T�E���h���Đ�����Ă��邩�̔���
};

#endif