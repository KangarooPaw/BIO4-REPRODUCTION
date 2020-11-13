//=============================================================================
//
// UI [ui.cpp]
// Author : �ѐ�ї���
//
//=============================================================================

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "ui.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPDIRECT3DTEXTURE9 CUi::m_pTexture[TYPE_MAX] = {};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CUi::CUi(int nPriority):CScene2D(nPriority)

{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CUi::~CUi()
{

}

//----------------------------------------
//��������
//----------------------------------------
CUi *CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	CUi *pUi;
	pUi = new CUi(OBJTYPE_UI);
	pUi->m_pos = pos;
	pUi->m_size = size;
	pUi->m_type = type;
	pUi->Init();
	return pUi;
}

//----------------------------------------
//�ǂݍ��ݏ���
//----------------------------------------
HRESULT CUi::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE,								// �t�@�C���̖��O
		&m_pTexture[TYPE_TITLE]);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TUTORIAL,								// �t�@�C���̖��O
		&m_pTexture[TYPE_TUTORIAL]);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_GAMEOVER,								// �t�@�C���̖��O
		&m_pTexture[TYPE_GAMEOVER]);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT,								// �t�@�C���̖��O
		&m_pTexture[TYPE_RESULT]);

	return S_OK;
}

//----------------------------------------
//�e�N�X�`���̔j��
//----------------------------------------
void CUi::Unload(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CUi::Init(void)
{	
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_UI);
	SetPosition(m_pos);		//�ʒu
	SetSize(m_size);		//�T�C�Y
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	BindTexture(m_pTexture[m_type]);

	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CUi::Update(void)
{
	CScene2D::Update();

	SetPosition(m_pos);		//�ʒu
	SetSize(m_size);			//�T�C�Y
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CUi::Draw(void)
{
	CScene2D::Draw();
}