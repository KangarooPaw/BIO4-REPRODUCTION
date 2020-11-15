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
#include "mouse.h"
#include "joystick.h"
#include "player.h"
#include "game.h"
#include "gate.h"
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
	m_lTheta	= 1.0f;
	m_lPhi		= 1.7f;	
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
	m_RotX = 0;
	m_RotY = 0;
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
	// ����J�����̔�����擾
	bool bGateOpen = CGame::GetGate()->GetOpen();
	// ��̈ʒu�擾
	D3DXVECTOR3 GatePos = CGame::GetGate()->GetPos();
	if (CGame::GetPlayer() != NULL)
	{
		// bGateOpen��false��
		if (bGateOpen == false)
		{
			//Keyboard();
			GamePad();
		}
		// bGateOpen��true�̏ꍇ
		if (bGateOpen == true)
		{
			// �ʒu���̑O��
			posV = D3DXVECTOR3(GatePos.x, GatePos.y + 50, GatePos.z - 300);
			// �����_
			posR.x = GatePos.x;
			posR.y = GatePos.y + 50;
			posR.z = GatePos.z;
		}
		//--------------------------------------
		//�J�����`��
		//--------------------------------------
		D3DXMatrixIdentity(&mtxView);
		D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
		pDevice->SetTransform(D3DTS_VIEW, &mtxView);
		D3DXMatrixIdentity(&mtxProjection);
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(90), SCREEN_WIDTH / SCREEN_HEIGHT, 10, 10000);
		pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
	}
}

//--------------------------------------
//�L�[�{�[�h����
//--------------------------------------
void CCamera::Keyboard(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�}�E�X�̎擾
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	//�v���C���[�̏ꏊ�̎擾
	D3DXVECTOR3 pPlayerPos = CGame::GetPlayer()->GetPos();
	//�v���C���[�̊p�x�̎擾
	D3DXVECTOR3 pPlayerRot = CGame::GetPlayer()->GetRot();
	//�v���C���[�̎��S�t���O�̎擾
	bool pPlayerDeath = CGame::GetPlayer()->GetDeath();
	//�v���C���[�̃��[�V��������
	bool pPlayerMotion = CGame::GetPlayer()->GetMotion();
	//�^�[�����Ȃ�
	if (m_bTurn == true)
	{
		m_lPhi -= D3DXToRadian(6);
		m_nTurnCnt++;
		//�^�[���̏I��
		if (m_nTurnCnt == 30)
		{
			m_bTurn = false;
			m_nTurnCnt = 0;
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
	}
	else if (pPlayerDeath == false&&pPlayerMotion==false)
	{
		if (pInputKeyboard->GetKeyPress(DIK_LSHIFT) == false &&
			pInputMouse->GetMouseTriggerRight() == false)
		{
			//�J�E���g�̃��Z�b�g
			m_nCount = 0;
			m_RotX = 0;
			m_RotY = 0;
			m_lTheta = 1.0f;

			//--------------------------
			//�ړ�
			//--------------------------		
			//���X�e�B�b�N�����ɓ|��
			if (pInputKeyboard->GetKeyPress(DIK_A))
			{
				m_lPhi += D3DXToRadian(2);
			}
			//���X�e�B�b�N���E�ɓ|��
			if (pInputKeyboard->GetKeyPress(DIK_D))
			{
				m_lPhi -= D3DXToRadian(2);
			}
			//���X�e�B�b�N�����ɓ|��//A�{�^���������Ĕ��]
			if (pInputKeyboard->GetKeyPress(DIK_S) && pInputKeyboard->GetKeyPress(DIK_SPACE))
			{
				m_bTurn = true;
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

			//m_rotY = pPlayerRot.y;
		}
		//LT�ŏe���\����/LB�Ńi�C�t���\����
		else if (pInputKeyboard->GetKeyPress(DIK_LSHIFT) ||
			pInputMouse->GetMouseTriggerRight())
		{
			//�E�X�e�B�b�N�����ɓ|��
			if (pInputKeyboard->GetKeyPress(DIK_A))
			{
				posR.x += cosf(pPlayerRot.y)*RETICLE_MOVE;
				posR.z -= sinf(pPlayerRot.y)*RETICLE_MOVE;

				m_lPhi += D3DXToRadian(1);
				m_RotX++;
				if (m_RotX >= MAX_ROT_Y)
				{
					posR.x -= cosf(pPlayerRot.y)*RETICLE_MOVE;
					posR.z += sinf(pPlayerRot.y)*RETICLE_MOVE;

					m_lPhi -= D3DXToRadian(1);
					m_RotX = MAX_ROT_Y;
				}
			}
			//�E�X�e�B�b�N���E�ɓ|��
			if (pInputKeyboard->GetKeyPress(DIK_D))
			{
				posR.x -= cosf(pPlayerRot.y)*RETICLE_MOVE;
				posR.z += sinf(pPlayerRot.y)*RETICLE_MOVE;

				m_lPhi -= D3DXToRadian(1);
				m_RotX--;
				if (m_RotX <= MIN_ROT_Y)
				{
					posR.x += cosf(pPlayerRot.y)*RETICLE_MOVE;
					posR.z -= sinf(pPlayerRot.y)*RETICLE_MOVE;

					m_lPhi += D3DXToRadian(1);
					m_RotX = MIN_ROT_Y;
				}
			}
			//�E�X�e�B�b�N����ɓ|��
			if (pInputKeyboard->GetKeyPress(DIK_W))
			{

				m_lTheta += D3DXToRadian(1);
				posR.y += cosf(m_lTheta);
				m_RotY++;
				if (m_RotY >= MAX_ROT_X)
				{
					posR.y -= cosf(m_lTheta);
					m_lTheta -= D3DXToRadian(1);
					m_RotY = MAX_ROT_X;
				}
			}
			//�E�X�e�B�b�N�����ɓ|��
			if (pInputKeyboard->GetKeyPress(DIK_S))
			{
				m_lTheta -= D3DXToRadian(1);
				posR.y -= cosf(m_lTheta);
				m_RotY--;
				if (m_RotY <= MIN_ROT_X)
				{
					posR.y += cosf(m_lTheta);
					m_lTheta += D3DXToRadian(1);
					m_RotY = MIN_ROT_X;
				}
			}

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

}

//--------------------------------------
//�Q�[���p�b�h����
//--------------------------------------
void CCamera::GamePad(void)
{
	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick = {};
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	//�v���C���[�̏ꏊ�̎擾
	D3DXVECTOR3 pPlayerPos = CGame::GetPlayer()->GetPos();
	//�v���C���[�̊p�x�̎擾
	D3DXVECTOR3 pPlayerRot = CGame::GetPlayer()->GetRot();
	//�v���C���[�̎��S�t���O�̎擾
	bool pPlayerDeath = CGame::GetPlayer()->GetDeath();
	//�v���C���[�̃��[�V��������
	bool pPlayerMotion = CGame::GetPlayer()->GetMotion();
	if (m_bTurn == false)
	{
		//���X�e�B�b�N�����ɓ|��//A�{�^���������Ĕ��]
		if (pStick.lY >= 500 && pInputJoystick->GetJoystickTrigger(pInputJoystick->BUTTON_A))
		{
			m_bTurn = true;
		}
	}
	//�^�[�����Ȃ�
	if (m_bTurn == true)
	{
		m_lPhi -= D3DXToRadian(6);
		m_nTurnCnt++;
		//�^�[���̏I��
		if (m_nTurnCnt == 30)
		{
			m_bTurn = false;
			m_nTurnCnt = 0;
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
	}
	else if (pPlayerDeath == false&&pPlayerMotion == false)
	{
		if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1) == false &&
			pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) == false)
		{
			//�J�E���g�̃��Z�b�g
			m_nCount = 0;
			m_RotX = 0;
			m_RotY = 0;
			m_lTheta = 1.0f;

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

			//m_rotY = pPlayerRot.y;
		}
		//LT�ŏe���\����/LB�Ńi�C�t���\����
		else if (pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L2) ||
			pInputJoystick->GetJoystickPress(pInputJoystick->BUTTON_L1))
		{
			//�E�X�e�B�b�N�����ɓ|��
			if (pStick.lRx <= -500 || pStick.lZ <= -500)
			{
				posR.x += cosf(pPlayerRot.y)*RETICLE_MOVE;
				posR.z -= sinf(pPlayerRot.y)*RETICLE_MOVE;

				m_lPhi += D3DXToRadian(1);
				m_RotX++;
				if (m_RotX >= MAX_ROT_Y)
				{
					posR.x -= cosf(pPlayerRot.y)*RETICLE_MOVE;
					posR.z += sinf(pPlayerRot.y)*RETICLE_MOVE;

					m_lPhi -= D3DXToRadian(1);
					m_RotX = MAX_ROT_Y;
				}
			}
			//�E�X�e�B�b�N���E�ɓ|��
			if (pStick.lRx >= 500 || pStick.lZ >= 500)
			{
				posR.x -= cosf(pPlayerRot.y)*RETICLE_MOVE;
				posR.z += sinf(pPlayerRot.y)*RETICLE_MOVE;

				m_lPhi -= D3DXToRadian(1);
				m_RotX--;
				if (m_RotX <= MIN_ROT_Y)
				{
					posR.x += cosf(pPlayerRot.y)*RETICLE_MOVE;
					posR.z -= sinf(pPlayerRot.y)*RETICLE_MOVE;

					m_lPhi += D3DXToRadian(1);
					m_RotX = MIN_ROT_Y;
				}
			}
			//�E�X�e�B�b�N����ɓ|��
			if (pStick.lRy <= -500 || pStick.lRz <= -500)
			{

				m_lTheta += D3DXToRadian(1);
				posR.y += cosf(m_lTheta);
				m_RotY++;
				if (m_RotY >= MAX_ROT_X)
				{
					posR.y -= cosf(m_lTheta);
					m_lTheta -= D3DXToRadian(1);
					m_RotY = MAX_ROT_X;
				}
			}
			//�E�X�e�B�b�N�����ɓ|��
			if (pStick.lRy >= 500 || pStick.lRz >= 500)
			{

				m_lTheta -= D3DXToRadian(1);
				posR.y -= cosf(m_lTheta);
				m_RotY--;
				if (m_RotY <= MIN_ROT_X)
				{
					posR.y += cosf(m_lTheta);
					m_lTheta += D3DXToRadian(1);
					m_RotY = MIN_ROT_X;
				}
			}

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
}
