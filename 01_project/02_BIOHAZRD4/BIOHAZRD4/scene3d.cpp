#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"

CScene3d::CScene3d()
{
}

CScene3d::~CScene3d()
{
}

CScene3d * CScene3d::Create(float nPosX, float nPosY)
{
	return nullptr;
}

HRESULT CScene3d::Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight)
{
	return E_NOTIMPL;
}

void CScene3d::Uninit(void)
{
}

void CScene3d::Update(void)
{
}

void CScene3d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMatrixIdentity(&m_Polygon.mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Polygon.rot.y, m_Polygon.rot.x, m_Polygon.rot.z);
	D3DXMatrixMultiply(&m_Polygon.mtxWorld, &m_Polygon.mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, m_Polygon.pos.x, m_Polygon.pos.y, m_Polygon.pos.z);
	D3DXMatrixMultiply(&m_Polygon.mtxWorld, &m_Polygon.mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_Polygon.mtxWorld);
	pDevice->SetTexture(0, m_pTexture);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void CScene3d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
