//=============================================================================
//
// ゲームオーバー処理 [gameover.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "gameover.h"
#include "renderer.h"
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
CGameover::CGameover()
{
	m_bSoundDecision = false;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CGameover::~CGameover()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CGameover::Init()
{
	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);

	//ゲームタイトルのUIの生成
	CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_GAMEOVER);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CGameover::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_RESULT);

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CGameover::Update(void)
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
void CGameover::Draw(void)
{
}