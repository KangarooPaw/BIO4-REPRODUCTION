//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "result.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "time.h"
#include "sound.h"
#include "ui.h"
#include "mode.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CResult::CResult()
{
	m_Type = TYPE_NONE;
	m_bSoundDecision = false;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CResult::~CResult()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CResult::Init()
{
	//�T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);

	//�Q�[���^�C�g����UI�̐���
	CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_RESULT);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CResult::Uninit(void)
{
	//�T�E���h�̒�~
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_RESULT);

	//�w�肵���I�u�W�F�N�g�ȊO�̃������̊J������
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CResult::Update(void)
{
	if (CScene::GetUpdateStop() == false)
	{
		if (m_bSoundDecision == false)
		{
			if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
			{ //Enter�L�[ �܂��� B�{�^�����������Ƃ�
				//�T�E���h�̍Đ�
				CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECISION);

				//�t�F�[�h�̐���
				CManager::CreateFade(CManager::MODE_TITLE);

				m_bSoundDecision = true;
			}
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CResult::Draw(void)
{
}