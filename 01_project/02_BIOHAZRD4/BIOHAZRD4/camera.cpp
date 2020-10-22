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
	posV = D3DXVECTOR3(-20.0f, 70.0f, 70.0f);
	posR = D3DXVECTOR3(-20.0f, 50.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fCameraAngle = 0.0f;
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
	//モデル場所の取得
	D3DXVECTOR3 pModelPos = CManager::GetModel()->GetPos();
	D3DXVECTOR3 pModelRot = CManager::GetModel()->GetRot();
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
	float angleV;
	float angleR;
	//--------------------------
	//移動
	//--------------------------
	//左スティックを左に倒す
	if (pStick.lX <= -500)
	{
		//注視点	
		angleR = atan2((posR.z - pModelPos.z), (posR.x - pModelPos.x));
		posR.x -= sinf(angleR) * 0.25f;
		posR.z += cosf(angleR) * 0.25f;
		//視点	
		angleV = atan2((posR.z - posV.z), (posR.x - posV.x));
		posV.x += sinf(angleV) * 0.7f;
		posV.z -= cosf(angleV) * 0.7f;
	}										 
	//左スティックを右に倒す				  
	if (pStick.lX >= 500)
	{		
		//注視点	
		angleR = atan2((posR.z - pModelPos.z), (posR.x - pModelPos.x));
		posR.x += sinf(angleR) * 0.3f;
		posR.z -= cosf(angleR) * 0.3f;
		//視点	
		angleV = atan2((posR.z - posV.z), (posR.x - posV.x));
		posV.x -= sinf(angleV) * 0.7f;
		posV.z += cosf(angleV) * 0.7f;
	}							   
	//左スティックを前に倒す
	if (pStick.lY <= -500)
	{
		//視点
		posV.z -= 0.5f;
		//注視点
		posR.z -= 0.5f;
	}
	//左スティックを後ろに倒す
	if (pStick.lY >= 500)
	{
		//視点
		posV.z += 0.5f;
		//注視点
		posR.z += 0.5f;
	}

	//--------------------------------------
	//カメラ描画
	//--------------------------------------
	D3DXMatrixIdentity(&mtxView);
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixIdentity(&mtxProjection);
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(45), SCREEN_WIDTH / SCREEN_HEIGHT, 10, 1000);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}