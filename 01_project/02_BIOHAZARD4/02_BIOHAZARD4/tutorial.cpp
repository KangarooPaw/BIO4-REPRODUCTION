//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "tutorial.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "time.h"
#include "sound.h"
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
//静的メンバ変数
//*****************************************************************************
CPlayer *CTutorial::m_pPlayer = NULL;
CBulletUi *CTutorial::m_pBulletUi = NULL;
CBulletUi *CTutorial::m_pBulletHaveUi = NULL;
CKey *CTutorial::m_pKey = NULL;
CGate *CTutorial::m_pGate = NULL;
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTutorial::CTutorial()
{
	m_nCount = 0;
	m_bSoundGameStart = false;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTutorial::~CTutorial()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CTutorial::Init(void)
{
	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);

	//チュートリアルのUIの生成
	CUi::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::TYPE_TUTORIAL);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CTutorial::Uninit(void)
{
	//サウンドの停止
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CTutorial::Update(void)
{
	if (CScene::GetUpdateStop() == false)
	{
		if (m_bSoundGameStart == false)
		{
			if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
			{ //Enterキー または Bボタンを押したとき
				//サウンドの再生
				CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_GAME_START);

				//フェードの生成
				CManager::CreateFade(CManager::MODE_GAME);
			
				m_bSoundGameStart = true;
			}
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CTutorial::Draw(void)
{
}