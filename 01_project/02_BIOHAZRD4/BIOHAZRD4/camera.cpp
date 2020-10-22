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
//--------------------------------------
//インクリメント
//--------------------------------------
CCamera::CCamera()
{
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fDistance		 = 0.0f;
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
	posR = D3DXVECTOR3(0, 0, 0);
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
	LPDIRECT3DDEVICE9 pDevice= CManager::GetRenderer()->GetDevice();
	//キーボード取得
	CInputKeyboard *pKeyborad = CManager::GetInput();	

	if (pKeyborad->GetKeyPress(DIK_W))
	{
		posV.z += -5.0f;
	}
	if (pKeyborad->GetKeyPress(DIK_S))
	{
		posV.z += 5.0f;
	}
	if (pKeyborad->GetKeyPress(DIK_A))
	{
		posV.x += 5.0f;
	}
	if (pKeyborad->GetKeyPress(DIK_D))
	{
		posV.x += -5.0f;
	}

	if (pKeyborad->GetKeyPress(DIK_UP))
	{
		posR.y += 5.0f;
	}
	if (pKeyborad->GetKeyPress(DIK_DOWN))
	{
		posR.y += -5.0f;
	}
	if (pKeyborad->GetKeyPress(DIK_LEFT))
	{
		posR.x += 5.0f;
	}
	if (pKeyborad->GetKeyPress(DIK_RIGHT))
	{
		posR.x += -5.0f;
	}

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
