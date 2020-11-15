//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "title.h"
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
CTitle::CTitle()
{
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CTitle::Init(void)
{
	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);

	//ゲームタイトルのUIの生成
	CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_TITLE);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CTitle::Uninit(void)
{

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CTitle::Update(void)
{
	if (CScene::GetUpdateStop() == false)
	{
		//Enterキー または Bボタンを押したとき
		if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
		{
			//サウンドの再生
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECISION);
			//サウンドの停止
			CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
			//フェードの生成
			CManager::CreateFade(CManager::MODE_TUTORIAL);
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CTitle::Draw(void)
{
}