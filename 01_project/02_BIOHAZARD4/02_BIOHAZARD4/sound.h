//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include <xaudio2.h>

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		//�^�C�g��
		SOUND_LABEL_BGM_TUTORIAL,		//�`���[�g���A��
		SOUND_LABEL_BGM_GAME,			//�Q�[��
		SOUND_LABEL_BGM_RESULT,			//���U���g
		SOUND_LABEL_SE_BACK_WALK,		//���ɕ���
		SOUND_LABEL_SE_DASH,			//�_�b�V��
		SOUND_LABEL_SE_DECISION,		//����
		SOUND_LABEL_SE_DOOR_OPEN,		//����J��
		SOUND_LABEL_SE_GAME_START,		//�Q�[���X�^�[�g
		SOUND_LABEL_SE_GET,				//�A�C�e���擾
		SOUND_LABEL_SE_KNIFE,			//�i�C�t
		SOUND_LABEL_SE_PLAYER_DAMAGE,	//�_���[�W(�v���C���[)
		SOUND_LABEL_SE_RELOAD,			//�����[�h
		SOUND_LABEL_SE_ROTATION,		//�]���r�̉�]
		SOUND_LABEL_SE_SHOT,			//�ˌ�
		SOUND_LABEL_SE_TURN,			//��������
		SOUND_LABEL_SE_WOODEN_BOX,		//�ؔ���j��
		SOUND_LABEL_SE_ZOMBIE_DAMAGE,	//�_���[�W(�]���r)
		SOUND_LABEL_SE_ZOMBIE_DEATH,	//��(�]���r)
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								    // XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			    // �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];

};

#endif
