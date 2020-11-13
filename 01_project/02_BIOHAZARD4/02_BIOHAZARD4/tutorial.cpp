//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "tutorial.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "time.h"
//#include "sound.h"
#include "ui.h"
#include "mode.h"
#include "player.h"
#include "life.h"
#include "enemy.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "map.h"
#include "item.h"
#include "box.h"
#include "skybox.h"
#include "bullet_ui.h"
#include "key.h"
#include "gate.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
CPlayer *CTutorial::m_pPlayer = NULL;
CBulletUi *CTutorial::m_pBulletUi = NULL;
CBulletUi *CTutorial::m_pBulletHaveUi = NULL;
CKey *CTutorial::m_pKey = NULL;
CGate *CTutorial::m_pGate = NULL;
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTutorial::CTutorial()
{
	m_nCount = 0;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CTutorial::~CTutorial()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CTutorial::Init(void)
{
	//�`���[�g���A����UI�̐���
	CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_TUTORIAL);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CTutorial::Uninit(void)
{
	//�w�肵���I�u�W�F�N�g�ȊO�̃������̊J������
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CTutorial::Update(void)
{
	if (CScene::GetUpdateStop() == false)
	{
		if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
		{ //Enter�L�[ �܂��� B�{�^�����������Ƃ�
		  //�t�F�[�h�̐���
			CManager::CreateFade(CManager::MODE_GAME);
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CTutorial::Draw(void)
{
}