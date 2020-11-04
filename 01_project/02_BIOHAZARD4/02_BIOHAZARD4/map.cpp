//****************************************
//モデル処理
//****************************************

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "map.h"
#include "model.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CMap::m_pMesh =NULL;
LPD3DXBUFFER CMap::m_pBuffMat = NULL;
DWORD CMap::m_nNumMat = NULL;
D3DXMATRIX CMap::m_mtxWorld = {};	 // 行列計算用
char* CMap::m_apFileName = {"data/MODEL/MAP/map_test.x"};// マップ
LPDIRECT3DTEXTURE9 CMap::m_pTexture = NULL;

//----------------------------------------
//インクリメント
//----------------------------------------
CMap::CMap(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pModel = NULL;
}

//----------------------------------------
//デクリメント
//----------------------------------------
CMap::~CMap()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CMap * CMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CMap *pMap;
	pMap = new CMap;
	pMap->Init();
	pMap->SetMap(pos, rot, size);
	return pMap;
}

//----------------------------------------
//モデルの読み込み
//----------------------------------------
HRESULT CMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_nNumMat,
			&m_pMesh
		);

		D3DXCreateTextureFromFile(pDevice,
			m_apFileName,
			&m_pTexture);
	return E_NOTIMPL;
}

//----------------------------------------
//モデルの破棄
//----------------------------------------
void CMap::Unload(void)
{
		// メッシュの破棄
		if (m_pMesh != NULL)
		{
			m_pMesh->Release();
			m_pMesh = NULL;
		}

		// マテリアルの破棄
		if (m_pBuffMat != NULL)
		{
			m_pBuffMat->Release();
			m_pBuffMat = NULL;
		}

		if (m_nNumMat != NULL)
		{
			m_nNumMat = NULL;
		}
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CMap::Init(void)
{
		// モデルの生成
		m_pModel = CModel::Create();

		// モデルのバインド
		m_pModel->BindModel(m_pMesh, m_pBuffMat, m_nNumMat, 0, m_pTexture);


	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CMap::Uninit(void)
{
		// モデルクラスの終了処理
		m_pModel->Uninit();
		m_pModel = NULL;
}

//----------------------------------------
//更新処理
//----------------------------------------
void CMap::Update(void)
{

}

//----------------------------------------
//描画処理
//----------------------------------------
void CMap::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;
		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		//m_pModel[nCount]->SetWorldMatrix(m_mtxWorld[nCount]);

		// モデルクラスの描画処理
		m_pModel->Draw();
}

//----------------------------------------
//初期設定
//----------------------------------------
void CMap::SetMap(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;				//場所
	m_rot = rot;				//角度
	m_size = size;				//大きさ
	SetObjType(OBJTYPE_PLAYER); //オブジェクトタイプの設定
}
