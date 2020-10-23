#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CInputJoystick;
class CCamera;
class CLight;
class CPlayer;
class CModel;
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

	void LoadAll(void);//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
	void UnloadAll(void);//�e�N�X�`���̔j���܂Ƃ�

	
	static CRenderer *GetRenderer(void);	//�����_���[
	static CInputKeyboard *GetInputKeyboard(void);	//�L�[�{�[�h
	static CInputJoystick *GetInputJoystick(void);	//�Q�[���p�b�h
	static CCamera *GetCamera(void);		//�J����
	static CLight *GetLight(void);			//���C�g
	static CPlayer *GetPlayer(void);		//�v���C���[
	static CModel *GetModel(void);			//���f��
	static CDebugProc*GetDebug(void);		//�f�o�b�O
private:								  
	static CRenderer *m_pRenderer;			//�����_���[
	static CInputKeyboard *m_pInputKeyboard;//�L�[�{�[�h
	static CInputJoystick *m_pInputJoystick;//�Q�[���p�b�h
	static CCamera *m_pCamera;				//�J����
	static CLight *m_pLight;				//���C�g
	static CPlayer *m_pPlayer;				//�v���C���[
	static CModel *m_pModel;				//���f��
	static CDebugProc*m_pDebugProc;			//�f�o�b�O
};	

#endif // !_MANAGER_H_
