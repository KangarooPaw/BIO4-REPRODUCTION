//----------------------------------------
//�v���C���[����
//----------------------------------------

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
LPDIRECT3DTEXTURE9 CUi::m_pTexture = NULL;

//----------------------------------------
//�C���N�������g
//----------------------------------------
CUi::CUi(int nPriority):CScene2D(nPriority)
{

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
CUi *CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CUi *pUi;
	pUi = new CUi(OBJTYPE_UI);
	pUi->SetPosition(pos);
	pUi->SetSize(size);
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
		TEXTURE_PLAYER,								// �t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
//�e�N�X�`���̔j��
//----------------------------------------
void CUi::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CUi::Init(void)
{	
	CScene2D::Init();
	CScene2D::BindTexture(m_pTexture);

	SetObjType(CScene::OBJTYPE_UI);
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
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CUi::Draw(void)
{
	CScene2D::Draw();
}