//----------------------------------------
//�v���C���[����
//----------------------------------------

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "player.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//----------------------------------------
//�C���N�������g
//----------------------------------------
CPlayer::CPlayer(int nPriority):CScene2D(nPriority)
{

}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CPlayer::~CPlayer()
{

}

//----------------------------------------
//��������
//----------------------------------------
CPlayer *CPlayer::Create(float nPosX, float nPosY)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init(nPosX, nPosY);
	return pPlayer;
}

//----------------------------------------
//�ǂݍ��ݏ���
//----------------------------------------
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_PLAYER,					// �t�@�C���̖��O
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
//�e�N�X�`���̔j��
//----------------------------------------
void CPlayer::Unload(void)
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
HRESULT CPlayer::Init(float nPosX, float nPosY)
{
	CScene2D::Init(nPosX, nPosY,PLAYER_WIDTH,PLAYER_HEIGHT);
	CScene2D::BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CPlayer::Update(void)
{

}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}