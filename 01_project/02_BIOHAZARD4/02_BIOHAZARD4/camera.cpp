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
#include "player.h"
#include "game.h"

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


	if (CGame::GetPlayer() != NULL)
	{
		//�v���C���[�̏ꏊ�̎擾
		D3DXVECTOR3 pPlayerPos = CGame::GetPlayer()->GetPos();
		//�v���C���[�̊p�x�̎擾
		D3DXVECTOR3 pPlayerRot = CGame::GetPlayer()->GetRot();
		if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) == false)
		{
			//--------------------------
			//�ړ�
			//--------------------------		
			//���X�e�B�b�N�����ɓ|��
			if (pStick.lX <= -500)
			{
				m_Phi += D3DXToRadian(1);
			}
			//���X�e�B�b�N���E�ɓ|��
			if (pStick.lX >= 500)
			{
				m_Phi -= D3DXToRadian(1);
			}

			//�����_
			m_Distance = -15;	//����
			posR.x = m_Distance*cosf(pPlayerRot.x) + pPlayerPos.x;
			posR.y = pPlayerPos.y + 47;
			posR.z = m_Distance*sinf(-pPlayerRot.x) + pPlayerPos.z;

			//���_	
			m_Distance = 25;	//����
			posV.x = m_Distance*(sinf(m_Theta)*cosf(m_Phi)) + posR.x;
			posV.y = m_Distance*cosf(m_Theta) + posR.y;
			posV.z = m_Distance*(sinf(m_Theta)*sinf(m_Phi)) + posR.z;
			//---------------------------
			//�J�����̊p�x�ύX
			//---------------------------
			//�E�X�e�B�b�N�����ɓ|��
			if (pStick.lRx <= -500)
			{
				m_Distance = -15;	//����
				posR.x = m_Distance*cosf(pPlayerRot.x) + pPlayerPos.x + 15.0f;
			}
			//�E�X�e�B�b�N���E�ɓ|��
			if (pStick.lRx >= 500)
			{
				m_Distance = -15;	//����
				posR.x = m_Distance*cosf(pPlayerRot.x) + pPlayerPos.x - 15.0f;
			}
		}
		else if(pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2))
		{

		}
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
}