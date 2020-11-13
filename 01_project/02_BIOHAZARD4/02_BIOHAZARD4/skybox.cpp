//****************************************
//モデル処理
//****************************************

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "skybox.h"
#include "model.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CSkyBox::m_pMesh = NULL;
LPD3DXBUFFER CSkyBox::m_pBuffMat = NULL;
DWORD CSkyBox::m_nNumMat = NULL;
D3DXMATRIX CSkyBox::m_mtxWorld = {};	 // 行列計算用
char* CSkyBox::m_apFileName = { "data/MODEL/MAP/sky.x" };// マップ
LPDIRECT3DTEXTURE9 CSkyBox::m_pTexture[MAX_MATERIAL] = {};

//----------------------------------------
//インクリメント
//----------------------------------------
CSkyBox::CSkyBox(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pModel = NULL;
}

//----------------------------------------
//デクリメント
//----------------------------------------
CSkyBox::~CSkyBox()
{
}

//----------------------------------------
//生成処理
//----------------------------------------
CSkyBox * CSkyBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CSkyBox *pMap;
	pMap = new CSkyBox;
	pMap->Init();
	pMap->SetSky(pos, rot, size);
	return pMap;
}

//----------------------------------------
//モデルの読み込み
//----------------------------------------
HRESULT CSkyBox::Load(void)
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

	// テクスチャの読み込み
	LoadTexture();

	return E_NOTIMPL;
}

//----------------------------------------
//モデルの破棄
//----------------------------------------
void CSkyBox::Unload(void)
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
// テクスチャの読み込み
//----------------------------------------
HRESULT CSkyBox::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// マテリアル情報を取り出す
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// 使用しているテクスチャがあれば読み込む
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// テクスチャ読み込み
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat])))
			{
				return E_FAIL;
			}
		}
	}

	return E_NOTIMPL;
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CSkyBox::Init(void)
{
	// モデルの生成
	m_pModel = CModel::Create();

	// モデルのバインド
	m_pModel->BindModel(m_pMesh, m_pBuffMat, m_nNumMat, 0);

	for (int nCntMat = 0; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// テクスチャのバインド
		m_pModel->BindTexture(m_pTexture[nCntMat], nCntMat);
	}
	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CSkyBox::Uninit(void)
{
	// モデルクラスの終了処理
	m_pModel->Uninit();
	m_pModel = NULL;
}

//----------------------------------------
//更新処理
//----------------------------------------
void CSkyBox::Update(void)
{

}

//----------------------------------------
//描画処理
//----------------------------------------
void CSkyBox::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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

	//アルファテスト無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// モデルクラスの描画処理
	m_pModel->Draw();

	//アルファテスト無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//----------------------------------------
//初期設定
//----------------------------------------
void CSkyBox::SetSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;				//場所
	m_rot = rot;				//角度
	m_size = size;				//大きさ
	SetObjType(OBJTYPE_SKYBOX); //オブジェクトタイプの設定
}
