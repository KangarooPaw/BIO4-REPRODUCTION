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
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Distance = 0;
	m_Theta = 1;
	m_Phi = 1.7f;
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
	//--------------------------
	//移動
	//--------------------------		

	//左スティックを前に倒す
	if (pStick.lX <= -500)
	{
		m_Phi += D3DXToRadian(1);
	}
	//左スティックを後ろに倒す
	if (pStick.lX >= 500)
	{
		m_Phi -= D3DXToRadian(1);
	}
	//左スティックを前に倒す
	if (pKeyborad->GetKeyPress(DIK_UP))
	{
		m_Theta -= D3DXToRadian(1);
	}
	//左スティックを後ろに倒す
	if (pKeyborad->GetKeyPress(DIK_DOWN))
	{
		m_Theta += D3DXToRadian(1);
	}

	//注視点
	//距離
	m_Distance = -15;
	posR.x = m_Distance*cosf(pModelRot.x)+ pModelPos.x;
	posR.y = pModelPos.y+47;
	posR.z = m_Distance*sinf(-pModelRot.x) + pModelPos.z;

	//視点	
	//距離
	m_Distance = 25;
	posV.x = m_Distance*(sinf(m_Theta)*cosf(m_Phi)) + posR.x;
	posV.y = m_Distance*cosf(m_Theta) + posR.y;
	posV.z = m_Distance*(sinf(m_Theta)*sinf(m_Phi)) + posR.z;

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