//=============================================================================
//
// モデルの階層構造の処理 [model_hierarchy.cpp]
// Author : 伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "model_hierarchy.h"
#include "bullet.h"

//=============================================================================
// インクリメント
//=============================================================================
CModelhierarchy::CModelhierarchy(int nPriority) :CScene3d(nPriority)
{
	for (int nCount = 0; nCount < 14; nCount++)
	{
		m_Model[nCount].m_pMeshParts = NULL;
		m_Model[nCount].m_pBuffMatParts = NULL;
		m_Model[nCount].m_nNumMatParts = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
}

//=============================================================================
// デクリメント
//=============================================================================
CModelhierarchy::~CModelhierarchy()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModelhierarchy::Init(void)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModelhierarchy::Uninit(void)
{
	
}

//=============================================================================
// 更新処理
//=============================================================================
void CModelhierarchy::Update(void)
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void CModelhierarchy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.x, m_rot.y, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&m_Model[nCount].m_mtxWorldParts);

		//向きを反転
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.x, m_rot.y, m_rot.z);
		D3DXMatrixMultiply(&m_Model[nCount].m_mtxWorldParts, &m_Model[nCount].m_mtxWorldParts, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_Model[nCount].m_mtxWorldParts, &m_Model[nCount].m_mtxWorldParts, &mtxTrans);
		
		//マテリアルデータへのポインタを取得する
		pMat = (D3DXMATERIAL*)m_Model[nCount].m_pBuffMatParts->GetBufferPointer();

		D3DXMATRIX mtxParent;
		if (m_Model[nCount].m_nldxModelParent == -1) {
			mtxParent = m_mtxWorld;
		}
		else {
			mtxParent = m_Model[m_Model[nCount].m_nldxModelParent].m_mtxWorldParts;
		}

		//モデルパーツに親のマトリックスを掛け合わせることで、位置や回転を親に追従させる
		D3DXMatrixMultiply(&m_Model[nCount].m_mtxWorldParts, &m_Model[nCount].m_mtxWorldParts, &mtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		for (int nCntMat = 0; nCntMat < (int)m_Model[nCount].m_nNumMatParts; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

			//モデルパーツの描画
			m_Model[nCount].m_pMeshParts->DrawSubset(nCntMat);
		}
		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// モデルのテクスチャ設定
//=============================================================================
void CModelhierarchy::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat, int nldxModelParent)
{
	// メッシュ、マテリアル情報のポインタ、マテリアル情報の数、親モデルのインデックスのバインド
	m_Model[m_nNumModel].m_pMeshParts= pMesh;
	m_Model[m_nNumModel].m_pBuffMatParts = pBuffMat;
	m_Model[m_nNumModel].m_nNumMatParts = nNumMat;
	m_Model[m_nNumModel].m_nldxModelParent = nldxModelParent;

	// モデルのパーツ分加算
	m_nNumModel++;
}

//=============================================================================
// モデルの場所、角度設定
//=============================================================================
void CModelhierarchy::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
}