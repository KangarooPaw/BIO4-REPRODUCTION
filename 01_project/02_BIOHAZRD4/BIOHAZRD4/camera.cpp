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
#include "model.h"

//--------------------------------------
//インクリメント
//--------------------------------------
CCamera::CCamera()
{
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//--------------------------------------
//デクリメント
//--------------------------------------
CCamera::~CCamera()
{

}

//--------------------------------------
//生成処理
//--------------------------------------
CCamera * CCamera::Create(void)
{
	CCamera*pCamera;
	pCamera = new CCamera;
	pCamera->Init();
	return pCamera;
}

//--------------------------------------
//初期化処理
//--------------------------------------
void CCamera::Init(void)
{
	posV = D3DXVECTOR3(0, 100, 100);
	posR = D3DXVECTOR3(0, 50, 0);
	vecU = D3DXVECTOR3(0, 1, 0);
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
	LPDIRECT3DDEVICE9 pDevice= CManager::GetRenderer()->GetDevice();
	//モデル場所の取得
	D3DXVECTOR3 pModelPos = CManager::GetModel()->GetPos();;
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

	//--------------------------
	//移動
	//--------------------------
	//左スティックを左に倒す
	if (pStick.lX <= -500)
	{

	}
	//左スティックを右に倒す
	if (pStick.lX >= 500)
	{

	}
	//左スティックを前に倒す
	if (pStick.lY <= -500)
	{
		posV.z -= 0.5f;
	}
	//左スティックを後ろに倒す
	if (pStick.lY >= 500)
	{
		posV.x = pModelPos.x - 50;
		posV.z = pModelPos.z - 100;
	}
	//視点
	posV.x = pModelPos.x - 100;
	posV.z = pModelPos.z + 100;
	//注視点
	posR.x = pModelPos.x - 50;
	//posR.z = pModelPos.z-25;


	D3DXMatrixIdentity(&mtxView);
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixIdentity(&mtxProjection);
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(45), SCREEN_WIDTH / SCREEN_HEIGHT, 10, 1000);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//--------------------------------------
//カメラ描画
//--------------------------------------
