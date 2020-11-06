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
//#include "sound.h"
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
	//ゲームタイトルのUIの生成
	CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(800.0f, 420.0f, 0.0f)/*, CUi::UI_TYPE_TITLE*/);

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