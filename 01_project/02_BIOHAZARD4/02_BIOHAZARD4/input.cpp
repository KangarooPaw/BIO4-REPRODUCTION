//--------------------------------
//�C���v�b�g����
//--------------------------------

//--------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------
#include "main.h"
#include "input.h"

//--------------------------------
//�ÓI�����o�ϐ�
//--------------------------------
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//--------------------------------
//�R���X�g���N�^
//--------------------------------
CInput::CInput()
{
	m_pInputDevice = NULL;
}

//--------------------------------
//�f�X�g���N�^
//--------------------------------
CInput::~CInput()
{

}

//--------------------------------
//����������
//--------------------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Directlnput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))) {
		return E_FAIL;
	}
	return S_OK;
}

//--------------------------------
//�I������
//--------------------------------
void CInput::Uninit(void)
{
	//���̓f�o�C�X�J��
	if (m_pInputDevice != NULL) {
		//�L�[�{�[�h�̃A�N�Z�X���J��
		m_pInputDevice->Unacquire();
		m_pInputDevice->Release();
		m_pInputDevice = NULL;
	}
	//Directlnput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL) {
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//--------------------------------
//�X�V����
//--------------------------------
void CInput::Update(void)
{

}