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
//�C���N�������g
//----------------------------------------
CPolygon::CPolygon()
{

}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CPolygon::~CPolygon()
{

}

//----------------------------------------
//����������
//----------------------------------------
void CPolygon::Init(void)
{

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
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CPolygon::Update(void)
{

}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CPolygon::Draw(void)
{
	CScene3d::Draw();
}

//void CPolygon::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
//{
//	m_Polygon.pos = pos;
//	m_Polygon.rot = D3DXVECTOR3(D3DXToRadian(rot.x), D3DXToRadian(rot.y), D3DXToRadian(rot.z));
//	m_Polygon.nType = nType;
//}
//
//CPolygon::POLYGON * CPolygon::GetPolygon(void)
//{
//	return &m_Polygon;
//}
