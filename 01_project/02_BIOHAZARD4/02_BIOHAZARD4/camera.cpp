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
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
	m_Distance = 0;
	m_lTheta = 1.0f;
	m_lPhi = 1.7f;	
	m_nCount = 0;
	m_bTurn = false;
	m_nTurnCnt = 0;
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
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
	m_Distance = 0;
	m_lTheta = 1.0f;
	m_lPhi = 1.7f;
	m_nCount = 0;
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
		//�^�[�����Ȃ�
		if (m_bTurn == true)
		{
			m_lPhi -= D3DXToRadian(3);
			m_nTurnCnt++;
			//�^�[���̏I��
			if (m_nTurnCnt == 60)
			{
				m_bTurn = false;
				m_nTurnCnt = 0;
			}
		}
		else
		{
			if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1) == false &&
				pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) == false)
			{
				//�J�E���g�̃��Z�b�g
				m_nCount = 0;
				//--------------------------
				//�ړ�
				//--------------------------		
				//���X�e�B�b�N�����ɓ|��
				if (pStick.lX <= -500)
				{
					m_lPhi += D3DXToRadian(2);
				}
				//���X�e�B�b�N���E�ɓ|��
				if (pStick.lX >= 500)
				{
					m_lPhi -= D3DXToRadian(2);
				}
				//���X�e�B�b�N�����ɓ|��//A�{�^���������Ĕ��]
				if (pStick.lY >= 500 && pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_A))
				{
					m_bTurn = true;
				}
				//---------------------------
				//�J�����̊p�x�ύX
				//---------------------------
				//�E�X�e�B�b�N�����ɓ|��
				if (pStick.lRx <= -500)
				{
					m_Distance = CAMERA_GAZE;	//����
					posR.x += MOVE;
				}
				//�E�X�e�B�b�N���E�ɓ|��
				if (pStick.lRx >= 500)
				{
					m_Distance = CAMERA_GAZE;	//����
					posR.x -= MOVE;
				}
				//�E�X�e�B�b�N����ɓ|��
				if (pStick.lRy <= -500)
				{
					posR.y = pPlayerPos.y + GAZE_Y + MOVE;
				}
				//�E�X�e�B�b�N�����ɓ|��
				if (pStick.lRy >= 500)
				{
					posR.y = pPlayerPos.y + GAZE_Y - MOVE;
				}
			}
			//LT�ŏe���\����/LB�Ńi�C�t���\����
			else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) ||
				pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1))
			{
				//10�t���[�������i�߂�
				if (m_nCount <= HOLD_FRAME)
				{
					//�����_
					posR.x += (float)-sin(pPlayerRot.y);
					posR.z += (float)-cos(pPlayerRot.y);
					//���_	
					posV.x += (float)-sin(pPlayerRot.y);
					posV.z += (float)-cos(pPlayerRot.y);
				}
				m_nCount++;
			}
		}
		//�����_
		m_Distance = CAMERA_GAZE;	//����
		posR.x = m_Distance*cosf(pPlayerRot.y) + pPlayerPos.x;
		posR.y = pPlayerPos.y + GAZE_Y;
		posR.z = m_Distance*sinf(-pPlayerRot.y) + pPlayerPos.z;

		//���_	
		m_Distance = CAMERA_VIEW;	//����
		posV.x = m_Distance*(sinf(m_lTheta)*cosf(m_lPhi)) + posR.x;
		posV.y = m_Distance*cosf(m_lTheta) + posR.y;
		posV.z = m_Distance*(sinf(m_lTheta)*sinf(m_lPhi)) + posR.z;
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