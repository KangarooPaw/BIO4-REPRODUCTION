//****************************************
//モデル処理
//****************************************

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "model.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CModel::m_pMesh = NULL;
LPD3DXBUFFER CModel::m_pBuffMat = NULL;
DWORD CModel::m_nNumMat = 0;

//----------------------------------------
//インクリメント
//----------------------------------------
CModel::CModel()
{

}

//----------------------------------------
//デクリメント
//----------------------------------------
CModel::~CModel()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pModel;
	pModel = new CModel;
	pModel->m_pos = pos;
	pModel->m_rot = rot;
	pModel->Init();
	return pModel;
}

//----------------------------------------
//モデルの読み込み
//----------------------------------------
HRESULT CModel::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("data/MODEL/playermodel_test001.x", 
		D3DXMESH_SYSTEMMEM, 
		pDevice, 
		NULL, 
		&m_pBuffMat, 
		NULL, 
		&m_nNumMat, 
		&m_pMesh
	);

	return E_NOTIMPL;
}

//----------------------------------------
//モデルの破棄
//----------------------------------------
void CModel::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CModel::Init(void)
{	
	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CModel::Uninit(void)
{
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	CScene3d::Uninit();
}

//----------------------------------------
//更新処理
//----------------------------------------
void CModel::Update(void)
{
	//コントローラーの取得処理
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	//--------------------------
	//移動
	//--------------------------
	//左スティックを左に倒す
	if (pStick.lX <= -500)
	{
		m_rot.x -= 0.01f;
	}
	//左スティックを右に倒す
	if (pStick.lX >= 500)
	{
		m_rot.x += 0.01f;
	}
	//左スティックを前に倒す	
	if (pStick.lY <= -500)
	{
		m_pos.z -= 0.5f;
	}
	//左スティックを後ろに倒す
	if (pStick.lY >= 500)
	{
		m_pos.z += 0.5f;
	}
}

//----------------------------------------
//描画処理
//----------------------------------------
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.x, m_rot.y, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		m_pMesh->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);
}
