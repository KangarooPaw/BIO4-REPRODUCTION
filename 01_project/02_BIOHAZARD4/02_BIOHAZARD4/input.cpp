#include "main.h"
#include "input.h"

LPDIRECTINPUT8 CInput::m_pInput = NULL;

CInput::CInput()
{
	m_pInputDevice = NULL;
}

CInput::~CInput()
{

}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Directlnput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))) {
		return E_FAIL;
	}
	return S_OK;
}

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

void CInput::Update(void)
{

}