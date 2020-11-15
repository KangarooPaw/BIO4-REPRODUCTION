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
#include "bullet.h"
#include "skybox.h"
//----------------------------------------
//インクリメント
//----------------------------------------
CModel::CModel()
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = NULL;
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
	m_nldxModelParent = 0;
	m_bIsFog = false;
	memset(m_pTexture, 0, sizeof(m_pTexture));

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pParent = NULL;
}

//----------------------------------------
//デクリメント
//----------------------------------------
CModel::~CModel()
{

}

//=============================================================================
// モーションクラスのインスタンス生成
//=============================================================================
CModel * CModel::Create()
{
	CModel *pModel;
	pModel = new CModel;
	pModel->Init();
	return pModel;
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CModel::Init()
{
	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CModel::Uninit(void)
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = NULL;

	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));

	m_pParent = NULL;
}

//----------------------------------------
//更新処理
//----------------------------------------
void CModel::Update(void)
{

}

//----------------------------------------
//描画処理
//----------------------------------------
void CModel::Draw(void)
{
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//D3DXMATRIX mtxRot, mtxTrans;
	//D3DMATERIAL9 matDef;
	//D3DXMATERIAL*pMat;
	//D3DXMatrixIdentity(&m_mtxWorld);
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//pDevice->GetMaterial(&matDef);
	//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	//{
	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//	m_pMesh->DrawSubset(nCntMat);
	//}
	//pDevice->SetMaterial(&matDef);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;

	//if (m_bIsFog == false)
	//{
	//	// フォグ設定
	//	float FogStart = 200.0f, FogEnd = 250.0f;
	//	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); // フォグ有効
	//	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.1f, 0.0f, 0.0f, 0.05f)); // フォグ色
	//	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR); // バーテックスフォグ
	//	pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE); // 範囲ベースのフォグ
	//	pDevice->SetRenderState(D3DRS_FOGSTART, *((DWORD*)(&FogStart))); // フォグ開始点
	//	pDevice->SetRenderState(D3DRS_FOGEND, *((DWORD*)(&FogEnd))); // フォグ終了点
	//}
	
	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x , m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pBuffMat != NULL)
	{
		//マテリアルデータへのポインタを取得する
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	}

	D3DXMATRIX mtxParent;
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD2, &mtxParent);
	}

	//モデルパーツに親のマトリックスを掛け合わせることで、位置や回転を親に追従させる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		if (m_pMesh != NULL)
		{
			//モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);
		}
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}


//=============================================================================
// モデルのテクスチャ設定
//=============================================================================
void CModel::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat, int nldxModelParent)
{
	// メッシュ、マテリアル情報のポインタ、マテリアル情報の数、親モデルのインデックスのバインド、テクスチャの情報
	m_pMesh = pMesh;
	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_nldxModelParent = nldxModelParent;
}

//=============================================================================
// モデルのテクスチャ設定
//=============================================================================
void CModel::BindTexture(LPDIRECT3DTEXTURE9 Texture, int nCount)
{
	m_pTexture[nCount] = Texture;
}

//=============================================================================
// モデルの場所、角度設定
//=============================================================================
void CModel::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
}

//=============================================================================
// モデルのペアレントの情報の受け取り
//=============================================================================
void CModel::SetParent(CModel *cmodel)
{
	// ポインタの受け取り
	m_pParent = cmodel;
}

//=============================================================================
// モデルの
//=============================================================================
void CModel::SetWorldMatrix(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}

void CModel::SetBoolFog(bool bFog)
{
    m_bIsFog = bFog;
}