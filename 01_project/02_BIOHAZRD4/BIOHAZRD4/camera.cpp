//--------------------------------------
//�J��������
//--------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "keyboard.h"
//--------------------------------------
//�C���N�������g
//--------------------------------------
CCamera::CCamera()
{
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fDistance		 = 0.0f;
}

//--------------------------------------
//�f�N�������g
//--------------------------------------
CCamera::~CCamera()
{

}

//--------------------------------------
//��������
//--------------------------------------
CCamera * CCamera::Create(void)
{
	CCamera*pCamera;
	pCamera = new CCamera;
	pCamera->Init();
	return pCamera;
}

//--------------------------------------
//����������
//--------------------------------------
void CCamera::Init(void)
{
	posV = D3DXVECTOR3(0, 100, 100);
	posR = D3DXVECTOR3(0, 0, 0);
	vecU = D3DXVECTOR3(0, 1, 0);
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
	LPDIRECT3DDEVICE9 pDevice= CManager::GetRenderer()->GetDevice();
	//�L�[�{�[�h�擾
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
//�J�����`��
//--------------------------------------
