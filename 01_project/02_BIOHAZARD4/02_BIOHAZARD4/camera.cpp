//--------------------------------------
//カメラ処理
//--------------------------------------

//--------------------------------------
//インクルードファイル
//--------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "keyboard.h"
#include "joystick.h"
#include "player.h"
#include "game.h"

//--------------------------------------
//インクリメント
//--------------------------------------
CCamera::CCamera()
{
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Distance = 0;
	m_lTheta = 1.0f;
	m_lPhi = 1.7f;	
	m_nCount = 0;
}

//--------------------------------------
//デクリメント
//--------------------------------------
CCamera::~CCamera()
{

}

//--------------------------------------
//初期化処理
//--------------------------------------
void CCamera::Init(void)
{

}

//--------------------------------------
//終了処理
//--------------------------------------
void CCamera::Uninit(void)
{

}

//--------------------------------------
//更新処理
//--------------------------------------
void CCamera::Update(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//キーボードの取得
	CInputKeyboard *pKeyborad = CManager::GetInputKeyboard();
	//コントローラーの取得処理
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}

	if (CGame::GetPlayer() != NULL)
	{
		//プレイヤーの場所の取得
		D3DXVECTOR3 pPlayerPos = CGame::GetPlayer()->GetPos();
		//プレイヤーの角度の取得
		D3DXVECTOR3 pPlayerRot = CGame::GetPlayer()->GetRot();
		if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) == false)
		{
			//カウントのリセット
			m_nCount = 0;
			//--------------------------
			//移動
			//--------------------------		
			//左スティックを左に倒す
			if (pStick.lX <= -500)
			{
				m_lPhi += D3DXToRadian(1);
			}
			//左スティックを右に倒す
			if (pStick.lX >= 500)
			{
				m_lPhi -= D3DXToRadian(1);
			}
			//左スティックを後ろに倒しながらAボタン
			if (pStick.lY >= 500 && pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_A))
			{
					m_lPhi += D3DXToRadian(180);
			}
			//注視点
			m_Distance = CAMERA_GAZE;	//距離
			posR.x = m_Distance*cosf(pPlayerRot.x) + pPlayerPos.x;
			posR.y = pPlayerPos.y + GAZE_Y;
			posR.z = m_Distance*sinf(-pPlayerRot.x) + pPlayerPos.z;

			//視点	
			m_Distance = CAMERA_VIEW;	//距離
			posV.x = m_Distance*(sinf(m_lTheta)*cosf(m_lPhi)) + posR.x;
			posV.y = m_Distance*cosf(m_lTheta) + posR.y;
			posV.z = m_Distance*(sinf(m_lTheta)*sinf(m_lPhi)) + posR.z;

			//---------------------------
			//カメラの角度変更
			//---------------------------
			//右スティックを左に倒す
			if (pStick.lRx <= -500)
			{
				m_Distance = CAMERA_GAZE;	//距離
				posR.x  += MOVE;
			}
			//右スティックを右に倒す
			if (pStick.lRx >= 500)
			{
				m_Distance = CAMERA_GAZE;	//距離
				posR.x -= MOVE;
			}
			//右スティックを上に倒す
			if (pStick.lRy <= -500)
			{
				posR.y = pPlayerPos.y + GAZE_Y + MOVE;
			}
			//右スティックを下に倒す
			if (pStick.lRy >= 500)
			{
				posR.y = pPlayerPos.y + GAZE_Y - MOVE;
			}
		}
		//LTで銃を構える/LBでナイフを構える
		else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2)|| pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1))
		{
			//10フレームだけ進める
			if (m_nCount <= HOLD_FRAME)
			{
				//注視点
				posR.x += (float)-sin(pPlayerRot.x);
				posR.z += (float)-cos(pPlayerRot.x);
				//視点	
				posV.x += (float)-sin(pPlayerRot.x);
				posV.z += (float)-cos(pPlayerRot.x);
			}
			m_nCount++;
		}
		//--------------------------------------
		//カメラ描画
		//--------------------------------------
		D3DXMatrixIdentity(&mtxView);
		D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
		pDevice->SetTransform(D3DTS_VIEW, &mtxView);
		D3DXMatrixIdentity(&mtxProjection);
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(90), SCREEN_WIDTH / SCREEN_HEIGHT, 10, 1000);
		pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
	}
}