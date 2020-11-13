//--------------------------------
//インクルードファイル
//--------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "light.h"

//--------------------------------
//コンストラクタ
//--------------------------------
CLight::CLight()
{

}

//--------------------------------
//デストラクタ
//--------------------------------
CLight::~CLight()
{

}

//--------------------------------
//初期化処理
//--------------------------------
void CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	vecDir = D3DXVECTOR3(0.5f, -0.8f, 0.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light.Direction = vecDir;
	pDevice->SetLight(0, &m_light);
	pDevice->LightEnable(0, TRUE);
}

//--------------------------------
//終了処理
//--------------------------------
void CLight::Uninit(void)
{
}
