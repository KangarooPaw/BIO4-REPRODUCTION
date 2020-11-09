//****************************************
//モデル処理
//****************************************

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "player.h"
#include "item.h"
#include "model.h"

#define ROT_ADDSPEED 0.01f //向き加算
#define UPDOWN_SPEED 0.05f //上下運動スピード

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CItem::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CItem::m_pBuffMat[TYPE_MAX] = {};
DWORD CItem::m_nNumMat[TYPE_MAX] = {};
//D3DXMATRIX CItem::m_mtxWorld = {};	 // 行列計算用
char* CItem::m_apFileName[TYPE_MAX] = { { "data/MODEL/ITEM/habu.x" },
{ "data/MODEL/ITEM/supure.x" },
{ "data/MODEL/ITEM/ammo_box.x" } };// マップ
LPDIRECT3DTEXTURE9 CItem::m_pTexture[TYPE_MAX][50] = {};

//----------------------------------------
//インクリメント
//----------------------------------------
CItem::CItem(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(ITEM_ROT_X, 0.0f, ITEM_ROT_X);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_pModel = NULL;
	m_fRd = 0.0f;
	m_mtxWorld = {};
}

//----------------------------------------
//デクリメント
//----------------------------------------
CItem::~CItem()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type)
{
	CItem *pItem;
	pItem = new CItem;
	pItem->m_type = type;
	pItem->Init();
	pItem->SetItem(pos, rot, size);

	return pItem;
}

//----------------------------------------
//モデルの読み込み
//----------------------------------------
HRESULT CItem::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFileName[nCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCount],
			NULL,
			&m_nNumMat[nCount],
			&m_pMesh[nCount]
		);
	}
	LoadTexture();
	return S_OK;
}
//----------------------------------------
// テクスチャの読み込み
//----------------------------------------
HRESULT CItem::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// マテリアル情報を取り出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat[nCount]->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[nCount]; nCntMat++)
		{
			// 使用しているテクスチャがあれば読み込む
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// テクスチャ読み込み
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_pTexture[nCount][nCntMat])))
				{
					return E_FAIL;
				}
			}
		}
	}

	return S_OK;
}
//----------------------------------------
//モデルの破棄
//----------------------------------------
void CItem::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// メッシュの破棄
		if (m_pMesh != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}

		// マテリアルの破棄
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}

		if (m_nNumMat != NULL)
		{
			m_nNumMat[nCount] = NULL;
		}
	}
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CItem::Init(void)
{
	// モデルの生成
	m_pModel = CModel::Create();

	// モデルのバインド
	m_pModel->BindModel(m_pMesh[m_type], m_pBuffMat[m_type], m_nNumMat[m_type], -1);

	for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[m_type]; nCntMat++)
	{
		// テクスチャのバインド
		m_pModel->BindTexture(m_pTexture[m_type][nCntMat], nCntMat);
	}

	//CScene3d::Init();

	////セット
	//SetPosition(m_pos);
	//SetRotation(m_rot);
	//SetSize(m_size);
	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CItem::Uninit(void)
{
	// モデルクラスの終了処理
	m_pModel->Uninit();
	m_pModel = NULL;
}

//----------------------------------------
//更新処理
//----------------------------------------
void CItem::Update(void)
{
	/*CScene3d::Update();*/

	m_pModel->Update();
	//回転
	m_rot.y += ROT_ADDSPEED;

	//上下運動
	m_fRd += 0.1f;
	if (m_fRd >= 360)
	{
		m_fRd = 0;
	}
	m_pos.y += (UPDOWN_SPEED * sin(m_fRd));
	
	//情報更新
	SetItem(m_pos, m_rot, m_size);

	//当たり判定処理
	CScene *pScene = NULL;

	do
	{
		pScene = GetScene(OBJTYPE_PLAYER);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_PLAYER)
			{
				// 座標とサイズの受け取り
				D3DXVECTOR3 Getpos = ((CPlayer*)pScene)->GetPos();
				D3DXVECTOR3 Getsize = ((CPlayer*)pScene)->GetSize();

				// 当たり判定
				if (CollisionItem(m_pos, m_size, Getpos, Getsize) == true)
				{
					//// アイテムを消す
				/*	Uninit();
					return;*/
				}
			}
		}
	} while (pScene != NULL);


}

//----------------------------------------
//描画処理
//----------------------------------------
void CItem::Draw(void)
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

	//ワールドマトリックスの設定
	m_pModel->SetWorldMatrix(m_mtxWorld);

	// モデルクラスの描画処理
	m_pModel->Draw();
}
//当たり判定
bool CItem::CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2)
{
	bool bHit = false;  //当たったかどうか

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pos1;       //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	return bHit;    //当たったかどうかを返す
}

void CItem::SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos; m_rot = rot; m_size = size;
	m_pModel->SetModel(m_pos, m_rot, m_size);
	SetObjType(OBJTYPE_ITEM);
}