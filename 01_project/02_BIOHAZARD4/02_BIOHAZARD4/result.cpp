//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
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
//コンストラクタ
//*****************************************************************************
CResult::CResult()
{
	m_Type = TYPE_NONE;
	m_bSoundDecision = false;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CResult::~CResult()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CResult::Init()
{
	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);

	//ゲームタイトルのUIの生成
	CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_RESULT);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CResult::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_RESULT);

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CResult::Update(void)
{
	if (CScene::GetUpdateStop() == false)
	{
		if (m_bSoundDecision == false)
		{
			if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
			{ //Enterキー または Bボタンを押したとき
				//サウンドの再生
				CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECISION);

				//フェードの生成
				CManager::CreateFade(CManager::MODE_TITLE);

				m_bSoundDecision = true;
			}
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CResult::Draw(void)
{
}