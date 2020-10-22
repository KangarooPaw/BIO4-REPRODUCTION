#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//�O���錾
class CRenderer;
class CPlayer;
class CInputKeyboard;
class CCamera;
class CLight;
class CDebugProc;

//�}�l�[�W���[�N���X
class CManager
{
public:
	CManager();//�C���N�������g
	~CManager();//�f�N�������g
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindouw);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��

	CPlayer *GetPlayer(void);				//�v���C���[
	static CInputKeyboard *GetInput(void);	//�����_���[
	static CRenderer *GetRenderer(void);	//�L�[�{�[�h
	static CCamera *GetCamera(void);		//�J����
	static CLight *GetLight(void);			//���C�g
	static CDebugProc*GetDebug(void);		//�f�o�b�O
private:								  
	static CPlayer *m_pPlayer;				//�v���C���[
	static CRenderer *m_pRenderer;			//�����_���[
	static CInputKeyboard *m_pInputKeyboard;//�L�[�{�[�h
	static CCamera *m_pCamera;				//�J����
	static CLight *m_pLight;				//���C�g
	static CDebugProc*m_pDebugProc;			//�f�o�b�O
};	

#endif // !_MANAGER_H_
