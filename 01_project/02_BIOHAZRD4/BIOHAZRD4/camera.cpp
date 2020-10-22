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
#include "joystick.h"
#include "model.h"

//--------------------------------------
//�C���N�������g
//--------------------------------------
CCamera::CCamera()
{
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	posR = D3DXVECTOR3(0, 50, 0);
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
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice= CManager::GetRenderer()->GetDevice();
	//���f���ꏊ�̎擾
	D3DXVECTOR3 pModelPos = CManager::GetModel()->GetPos();;
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pKeyborad = CManager::GetInputKeyboard();	
	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}

	//--------------------------
	//�ړ�
	//--------------------------
	//���X�e�B�b�N�����ɓ|��
	if (pStick.lX <= -500)
	{

	}
	//���X�e�B�b�N���E�ɓ|��
	if (pStick.lX >= 500)
	{

	}
	//���X�e�B�b�N��O�ɓ|��
	if (pStick.lY <= -500)
	{
		posV.z -= 0.5f;
	}
	//���X�e�B�b�N�����ɓ|��
	if (pStick.lY >= 500)
	{
		posV.x = pModelPos.x - 50;
		posV.z = pModelPos.z - 100;
	}
	//���_
	posV.x = pModelPos.x - 100;
	posV.z = pModelPos.z + 100;
	//�����_
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
//�J�����`��
//--------------------------------------
