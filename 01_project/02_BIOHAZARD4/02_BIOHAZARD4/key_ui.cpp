//=============================================================================
//
// ��UI [key_ui.cpp]
// Author : �ѐ�ї���
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "key_ui.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
LPDIRECT3DTEXTURE9 CKeyUi::m_pTexture = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKeyUi::CKeyUi()
{
	m_pVtxBuff = NULL;
	m_nPatternAnim = TYPE_NOGLOW;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKeyUi::~CKeyUi()
{
}
//=============================================================================
// ����
//=============================================================================
CKeyUi * CKeyUi::Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight)
{
	CKeyUi *pKey = NULL;

	if (pKey == NULL)
	{
		pKey = new CKeyUi;
		pKey->Init(pos, fSizeWidth, fSizeHeight);
	}

	return pKey;
}
//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CKeyUi::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_KEY, &m_pTexture);
	return S_OK;
}
//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CKeyUi::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CKeyUi::Init(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x + (-fSizeWidth / 2), pos.y + (-fSizeHeight / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (fSizeWidth / 2), pos.y + (-fSizeHeight / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x + (-fSizeWidth / 2), pos.y + (fSizeHeight / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (fSizeWidth / 2), pos.y + (fSizeHeight / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.5f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.5f + 0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.5f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.5f + 0.5f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CKeyUi::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void CKeyUi::Update(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void CKeyUi::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//�A���t�@�e�X�g�̔�r���@�̐ݒ�iGREATER�͊�l���傫���ꍇ)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, m_pTexture);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=============================================================================
// ���Z�b�g����
//=============================================================================
void CKeyUi::SetKey(TYPE type)
{

	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(type * 0.5f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(type * 0.5f + 0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(type * 0.5f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(type * 0.5f + 0.5f, 1.0f);

	m_pVtxBuff->Unlock();
}
