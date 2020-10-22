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
	posV = D3DXVECTOR3(-20.0f, 70.0f, 70.0f);
	posR = D3DXVECTOR3(-20.0f, 50.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fCameraAngle = 0.0f;
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//���f���ꏊ�̎擾
	D3DXVECTOR3 pModelPos = CManager::GetModel()->GetPos();
	D3DXVECTOR3 pModelRot = CManager::GetModel()->GetRot();
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
	float angleV;
	float angleR;
	//--------------------------
	//�ړ�
	//--------------------------
	//���X�e�B�b�N�����ɓ|��
	if (pStick.lX <= -500)
	{
		//�����_	
		angleR = atan2((posR.z - pModelPos.z), (posR.x - pModelPos.x));
		posR.x -= sinf(angleR) * 0.25f;
		posR.z += cosf(angleR) * 0.25f;
		//���_	
		angleV = atan2((posR.z - posV.z), (posR.x - posV.x));
		posV.x += sinf(angleV) * 0.7f;
		posV.z -= cosf(angleV) * 0.7f;
	}										 
	//���X�e�B�b�N���E�ɓ|��				  
	if (pStick.lX >= 500)
	{		
		//�����_	
		angleR = atan2((posR.z - pModelPos.z), (posR.x - pModelPos.x));
		posR.x += sinf(angleR) * 0.3f;
		posR.z -= cosf(angleR) * 0.3f;
		//���_	
		angleV = atan2((posR.z - posV.z), (posR.x - posV.x));
		posV.x -= sinf(angleV) * 0.7f;
		posV.z += cosf(angleV) * 0.7f;
	}							   
	//���X�e�B�b�N��O�ɓ|��
	if (pStick.lY <= -500)
	{
		//���_
		posV.z -= 0.5f;
		//�����_
		posR.z -= 0.5f;
	}
	//���X�e�B�b�N�����ɓ|��
	if (pStick.lY >= 500)
	{
		//���_
		posV.z += 0.5f;
		//�����_
		posR.z += 0.5f;
	}

	//--------------------------------------
	//�J�����`��
	//--------------------------------------
	D3DXMatrixIdentity(&mtxView);
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixIdentity(&mtxProjection);
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(45), SCREEN_WIDTH / SCREEN_HEIGHT, 10, 1000);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}