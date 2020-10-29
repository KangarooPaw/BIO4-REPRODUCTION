//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : 
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene.h"
#include "scene2d.h"
#include "scene3d.h"
#include "camera.h"
#include "ui.h"
#include "model.h"
#include "polygon.h"
#include "debug.h"
#include "light.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "tutorial.h"
#include "result.h"
#include "title.h"
#include "game.h"
#include "fade.h"

//=============================================================================
//�X�^�e�B�b�N�ϐ�������
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputJoystick *CManager::m_pInputJoystick = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CFade *CManager::m_pFade = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CMode *CManager::m_pMode = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_NONE;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{
	//�N���X�����Ə�����	
	//�����_���[
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, TRUE);
	//�L�[�{�[�h
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);
	//�Q�[���p�b�h
	m_pInputJoystick = new CInputJoystick;
	m_pInputJoystick->Init(hInstance, hWnd);
	//�f�o�b�O
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
	//�e�N�X�`���̓ǂݍ���
	LoadAll();

	//���[�h�̐ݒ�
	SetMode(MODE_TITLE);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();
	//�e�N�X�`���̔j��
	UnloadAll();
	//�f�o�b�O�̏I��
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
	//���C�g�̏I��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	//�J�����̏I��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	//�Q�[���p�b�h�̏I��
	if (m_pInputJoystick != NULL)
	{
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = NULL;
	}
	//�L�[�{�[�h�̏I��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�̏I������
		m_pMode->Uninit();
	}
	//�����_���[�̏I��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pInputJoystick != NULL)
	{
		//�L�[�{�[�h�̍X�V����
		m_pInputKeyboard->Update();
	}

	if (m_pInputJoystick != NULL)
	{
		//�W���C�X�e�B�b�N�̍X�V����
		m_pInputJoystick->Update();
	}

	if (m_pRenderer != NULL)
	{
		//�����_���[�̍X�V����
		m_pRenderer->Update();
	}

	if (m_pCamera != NULL)
	{
		//�J�����̂̍X�V����
		m_pCamera->Update();
	}

	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�̍X�V����
		m_pMode->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//�`�揈��
		m_pRenderer->Draw();
	}

	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�̕`�揈��
		m_pMode->Draw();
	}
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
//=============================================================================
void CManager::LoadAll(void)
{
	CUi::Load();
	CPolygon::Load();
	CPlayer::Load();
	CEnemy::Load();
	CBullet::Load();
}

//=============================================================================
//�e�N�X�`���̔j���܂Ƃ�
//=============================================================================
void CManager::UnloadAll(void)
{	
	CBullet::Unload();
	CEnemy::Unload();
	CPlayer::Unload();
	CPolygon::Unload();
	CUi::Unload();
}

//=============================================================================
//���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�̏I������
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}

	if (m_pMode == NULL)
	{
		m_mode = mode;

		switch (m_mode)
		{
		case MODE_TITLE:

			//�^�C�g���̐���
			m_pMode = new CTitle;

			//�^�C�g���̏���������
			m_pMode->Init();

			break;

		case MODE_GAME:
			if (m_pCamera != NULL)
			{
				m_pCamera->Uninit();
				delete m_pCamera;
				m_pCamera = NULL;
			}
			//�Q�[���̐���
			m_pMode = new CGame;

			//�Q�[���̏���������
			m_pMode->Init();

			break;

		case MODE_TUTORIAL:

			//�`���[�g���A���̐���
			m_pMode = new CTutorial;

			//�`���[�g���A���̏���������
			m_pMode->Init();

			break;

		case MODE_RESULT:

			//�N���A��ʂ̐���
			m_pMode = new CResult;

			//�N���A��ʂ̏���������
			m_pMode->Init();

			break;
		}
	}
}

//=============================================================================
//�J�����̐���
//=============================================================================
void CManager::CreateCamera(void)
{
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;

		if (m_pCamera != NULL)
		{
			m_pCamera->Init();
		}
	}
}

//=============================================================================
//���C�g�̐���
//=============================================================================
void CManager::CreateLight(void)
{
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;

		if (m_pLight != NULL)
		{
			m_pLight->Init();
		}
	}
}

//=============================================================================
//�t�F�[�h�̐���
//=============================================================================
void CManager::CreateFade(MODE mode)
{
	if (m_pFade == NULL)
	{
		m_pFade = new CFade(CScene::OBJTYPE_FADE);

		m_pFade->SetFade(mode);
		m_pFade->Init();
	}
	else if (m_pFade != NULL)
	{
		m_pFade->SetFade(mode);
	}
}

//=============================================================================
// �󂯓n������
//=============================================================================
//�����_���[
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;	
}

//�L�[�{�[�h
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//�Q�[���p�b�h
CInputJoystick * CManager::GetInputJoystick(void)
{
	return m_pInputJoystick;
}

//�J����
CCamera * CManager::GetCamera(void)
{
	return m_pCamera;
}

//���C�g
CLight * CManager::GetLight(void)
{
	return m_pLight;
}

//�t�F�[�h
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//�f�o�b�O
CDebugProc * CManager::GetDebug(void)
{
	return m_pDebugProc;
}

//���[�h�̎擾
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}