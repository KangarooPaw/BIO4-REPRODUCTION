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
#include "player.h"
#include "model.h"
#include "polygon.h"
#include "debug.h"
#include "light.h"

//=============================================================================
//�X�^�e�B�b�N�ϐ�������
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputJoystick *CManager::m_pInputJoystick = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CModel *CManager::m_pModel = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;

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
	//�J����
	m_pCamera = CCamera::Create();
	//���C�g
	m_pLight = CLight::Create();

	//�e�N�X�`���̓ǂݍ���
	LoadAll();
	//�|���S������
	CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR3(40.0f, 0.0f, -40.0f),0);
	CPolygon::Create(D3DXVECTOR3(0.0f, 0.0f, 20.0f), D3DXVECTOR3(90.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 0.0f, -20.0f), 0);
	m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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
	m_pInputKeyboard->Update();
	m_pInputJoystick->Update();
	m_pRenderer->Update();
	m_pCamera->Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//=============================================================================
//�e�N�X�`���̓ǂݍ��݂܂Ƃ�
//=============================================================================
void CManager::LoadAll(void)
{
	CPlayer::Load();
	CPolygon::Load();
	CModel::Load();
}

//=============================================================================
//�e�N�X�`���̔j���܂Ƃ�
//=============================================================================
void CManager::UnloadAll(void)
{
	CModel::Unload();
	CPolygon::Unload();
	CPlayer::Unload();
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

//�v���C���[
CPlayer *CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//���f��
CModel * CManager::GetModel(void)
{
	return m_pModel;
}

//�f�o�b�O
CDebugProc * CManager::GetDebug(void)
{
	return m_pDebugProc;
}

