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
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Distance = 0;
	m_Theta = 1;
	m_Phi = 1.7f;
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
	//--------------------------
	//�ړ�
	//--------------------------		

	//���X�e�B�b�N��O�ɓ|��
	if (pStick.lX <= -500)
	{
		m_Phi += D3DXToRadian(1);
	}
	//���X�e�B�b�N�����ɓ|��
	if (pStick.lX >= 500)
	{
		m_Phi -= D3DXToRadian(1);
	}
	//���X�e�B�b�N��O�ɓ|��
	if (pKeyborad->GetKeyPress(DIK_UP))
	{
		m_Theta -= D3DXToRadian(1);
	}
	//���X�e�B�b�N�����ɓ|��
	if (pKeyborad->GetKeyPress(DIK_DOWN))
	{
		m_Theta += D3DXToRadian(1);
	}

	//�����_
	//����
	m_Distance = -15;
	posR.x = m_Distance*cosf(pModelRot.x)+ pModelPos.x;
	posR.y = pModelPos.y+47;
	posR.z = m_Distance*sinf(-pModelRot.x) + pModelPos.z;

	//���_	
	//����
	m_Distance = 25;
	posV.x = m_Distance*(sinf(m_Theta)*cosf(m_Phi)) + posR.x;
	posV.y = m_Distance*cosf(m_Theta) + posR.y;
	posV.z = m_Distance*(sinf(m_Theta)*sinf(m_Phi)) + posR.z;

	//--------------------------------------
	//�J�����`��
	//--------------------------------------
	D3DXMatrixIdentity(&mtxView);
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixIdentity(&mtxProjection);
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(90), SCREEN_WIDTH / SCREEN_HEIGHT, 10, 1000);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}