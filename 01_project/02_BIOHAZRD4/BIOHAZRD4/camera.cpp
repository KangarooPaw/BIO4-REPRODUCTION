//--------------------------------------
//�J��������
//--------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "camera.h"
#include "manager.h"
#include "renderer.h"

//--------------------------------------
//�C���N�������g
//--------------------------------------
CCamera::CCamera()
{
	g_camera = {};
}

//--------------------------------------
//�f�N�������g
//--------------------------------------
CCamera::~CCamera()
{

}

//--------------------------------------
//����������
//--------------------------------------
void CCamera::Init(void)
{
	g_camera.posV = D3DXVECTOR3(0, 40, 0);
	g_camera.posR = D3DXVECTOR3(0, 20, 80);
	g_camera.vecU = D3DXVECTOR3(0, 1, 0);
}

//--------------------------------------
//�I������
//--------------------------------------
void CCamera::Uninit(void)
{

}

//--------------------------------------
//�X�V����
//--------------------------------------
void CCamera::Update(void)
{
}

//--------------------------------------
//�J�����`��
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
