//----------------------------------------
//�|���S������
//----------------------------------------

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture[MAX_TYPE_POLYGON] = {};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CPolygon::CPolygon(int nPriority) :CScene3d(nPriority)
{

}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CPolygon::~CPolygon()
{

}

//----------------------------------------
//��������
//----------------------------------------
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 size,int type)
{
	CPolygon *pPolygon;
	pPolygon = new CPolygon;
	pPolygon->m_pos = pos;
	pPolygon->m_rot = rot;
	pPolygon->m_size = size;
	pPolygon->m_nType=type;
	pPolygon->Init();
	return pPolygon;
}

//----------------------------------------
//�e�N�X�`���̓ǂݍ���
//----------------------------------------
HRESULT CPolygon::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"PolygonTexture1.png", 
		&m_pTexture[0]);

	D3DXCreateTextureFromFile(pDevice, 
		"PolygonTexture2.png", 
		&m_pTexture[1]);

	return S_OK;
}

//----------------------------------------
//�e�N�X�`���̔j��
//----------------------------------------
void CPolygon::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TYPE_POLYGON; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CPolygon::Init(void)
{
	CScene3d::SetPosition(m_pos);
	CScene3d::SetRotation(m_rot);
	CScene3d::SetSize(m_size);
	CScene3d::BindTexture(m_pTexture[m_nType]);
	CScene3d::Init();

	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CPolygon::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene3d::Uninit();
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CPolygon::Update(void)
{
	CScene3d::Update();
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CPolygon::Draw(void)
{
	CScene3d::Draw();
}

