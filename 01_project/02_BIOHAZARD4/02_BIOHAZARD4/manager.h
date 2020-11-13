#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CInputJoystick;
class CCamera;
class CLight;
class CFade;
class CPlayer;
class CModel;
class CDebugProc;
class CMode;
class CSound;


//�}�l�[�W���[�N���X
class CManager
{
public:
	//��ʑJ�ڂ̗񋓌^
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,		//�^�C�g��
		MODE_GAME,		//�Q�[��
		MODE_TUTORIAL,	//�`���[�g���A��
		MODE_RESULT,	//���U���g
		MODE_GAMEOVER, //�Q�[���I�[�o�[
		MODE_MAX
	}MODE;

	CManager();//�C���N�������g
	~CManager();//�f�N�������g
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindouw);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��

	void LoadAll(void);//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
	void UnloadAll(void);//�e�N�X�`���̔j���܂Ƃ�

	void SetMode(MODE mode);	//���[�h�̐ݒ�
	
	static void CreateCamera(void);
	static void CreateLight(void);
	static void CreateFade(MODE mode);

	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }

	static CRenderer *GetRenderer(void);	//�����_���[
	static CInputKeyboard *GetInputKeyboard(void);//�L�[�{�[�h
	static CInputMouse *GetInputMouse(void);//�}�E�X
	static CInputJoystick *GetInputJoystick(void);//�Q�[���p�b�h
	static CCamera *GetCamera(void);		//�J����
	static CLight *GetLight(void);			//���C�g
	static CFade *GetFade(void);			//�t�F�[�h
	static CDebugProc*GetDebug(void);		//�f�o�b�O
	static MODE GetMode(void);				//���[�h

private:								  
	static CRenderer *m_pRenderer;			//�����_���[
	static CInputKeyboard *m_pInputKeyboard;//�L�[�{�[�h
	static CInputMouse *m_pInputMouse;		//�}�E�X
	static CInputJoystick *m_pInputJoystick;//�Q�[���p�b�h
	static CCamera *m_pCamera;				//�J����
	static CLight *m_pLight;				//���C�g
	static CFade *m_pFade;					//�t�F�[�h
	static CSound *m_pSound;                //�T�E���h
	static CDebugProc*m_pDebugProc;			//�f�o�b�O
	static CMode *m_pMode;					//���[�h�̃|�C���^
	static MODE m_mode;						//���݂̃��[�h
	int m_nCountFPS;	// FPS�̒l
};	

#endif // !_MANAGER_H_
