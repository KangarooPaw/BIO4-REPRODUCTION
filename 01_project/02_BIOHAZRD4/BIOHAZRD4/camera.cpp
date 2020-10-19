//--------------------------------------
//カメラ処理
//--------------------------------------

//--------------------------------------
//インクルードファイル
//--------------------------------------
#include "camera.h"
#include "manager.h"
#include "renderer.h"

//--------------------------------------
//インクリメント
//--------------------------------------
CCamera::CCamera()
{
	g_camera = {};
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
	g_camera.posV = D3DXVECTOR3(0, 40, 0);
	g_camera.posR = D3DXVECTOR3(0, 20, 80);
	g_camera.vecU = D3DXVECTOR3(0, 1, 0);
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
}

//--------------------------------------
//カメラ描画
//--------------------------------------
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMatrixIdentity(&g_camera.mtxView);
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
	D3DXMatrixIdentity(&g_camera.mtxProjection);
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45), SCREEN_WIDTH / SCREEN_HEIGHT, 10, 1000);
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}
