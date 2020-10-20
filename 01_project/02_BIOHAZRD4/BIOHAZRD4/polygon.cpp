//----------------------------------------
//ポリゴン処理
//----------------------------------------

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"

//----------------------------------------
//インクリメント
//----------------------------------------
CPolygon::CPolygon()
{

}

//----------------------------------------
//デクリメント
//----------------------------------------
CPolygon::~CPolygon()
{

}

//----------------------------------------
//初期化処理
//----------------------------------------
void CPolygon::Init(void)
{

}

//----------------------------------------
//終了処理
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
//更新処理
//----------------------------------------
void CPolygon::Update(void)
{

}

//----------------------------------------
//描画処理
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
