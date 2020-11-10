//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CScene3d::CScene3d(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CScene3d::~CScene3d()
{
}

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CScene3d * CScene3d::Create(float nPosX, float nPosY)
{
	CScene3d *pScene3d;
	pScene3d = new CScene3d(0);

	pScene3d->Init();
	return pScene3d;

}

//--------------------------------------
//����������
//--------------------------------------
HRESULT CScene3d::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice= CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_POLYGON,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- (m_size.x / 2),m_size.y, + (m_size.z / 2));
	pVtx[1].pos = D3DXVECTOR3(+ (m_size.x / 2),m_size.y, + (m_size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(- (m_size.x / 2),m_size.y, - (m_size.z / 2));
	pVtx[3].pos = D3DXVECTOR3(+ (m_size.x / 2),m_size.y, - (m_size.z / 2));

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

	//�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255,0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255,0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255,0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255,0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//--------------------------------------
//�I������
//--------------------------------------
void CScene3d::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//--------------------------------------
//�X�V����
//--------------------------------------
void CScene3d::Update(void)
{
	// ���_����ݒ�
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- (m_size.x / 2), m_pos.y,  + (m_size.z / 2));
	pVtx[1].pos = D3DXVECTOR3(+ (m_size.x / 2), m_pos.y,  + (m_size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(- (m_size.x / 2), m_pos.y,  - (m_size.z / 2));
	pVtx[3].pos = D3DXVECTOR3(+ (m_size.x / 2), m_pos.y,  - (m_size.z / 2));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//--------------------------------------
//�`�揈��
//--------------------------------------
void CScene3d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->SetTexture(0, m_pTexture);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//================================================================================
//�e��ݒ�
//================================================================================
//----------------------------------------
//�ꏊ
//----------------------------------------
void CScene3d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//----------------------------------------
//�p�x
//----------------------------------------
void CScene3d::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//----------------------------------------
//�T�C�Y
//----------------------------------------
void CScene3d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//----------------------------------------
//�e�N�X�`��
//----------------------------------------
void CScene3d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}