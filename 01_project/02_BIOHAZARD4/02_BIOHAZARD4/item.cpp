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
#include "kira.h"
#include "joystick.h"
#include "circleparticle.h"
#define ROT_ADDSPEED 0.01f //向き加算
#define UPDOWN_SPEED 0.05f //上下運動スピード
#define ITEM_UP_VALUE 2.5f //上に上がる力
#define ITEM_GRAVITY 0.05f //重力
#define ITEM_KIRAKIRA_INTERVAL 50 //きらきら間隔

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CItem::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CItem::m_pBuffMat[TYPE_MAX] = {};
DWORD CItem::m_nNumMat[TYPE_MAX] = {};
//D3DXMATRIX CItem::m_mtxWorld = {};	 // 行列計算用
char* CItem::m_apFileName[TYPE_MAX] = { 
{ "data/MODEL/ITEM/habu.x" },
{ "data/MODEL/ITEM/supure.x" },
{ "data/MODEL/ITEM/ammo_box.x" },
{ "data/MODEL/ITEM/key.x" } , };// アイテムモデル
LPDIRECT3DTEXTURE9 CItem::m_pTexture[TYPE_MAX][50] = {};

//----------------------------------------
//インクリメント
//----------------------------------------
CItem::CItem(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(ITEM_ROT_X, 0.0f, ITEM_ROT_X);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_pModel = NULL;
	m_fRd = 0.0f;
	m_Attribute = ITEM_NONE;
	m_mtxWorld = {};
	m_nCountTimer = 0;
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
	if (pItem->m_type != TYPE_KEY)
	{
		CCircleParticle::CircleCreate(pos, D3DXVECTOR3(PARTICLE_CIRCLE_SIZE_X, PARTICLE_CIRCLE_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_CIRCLE, 7.5f);
	}

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

	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CItem::Uninit(void)
{
		if (m_pModel != NULL)
		{
			// モデルクラスの終了処理
			m_pModel->Uninit();
			m_pModel = NULL;
		}
	Release();
}
//----------------------------------------
//更新処理
//----------------------------------------
void CItem::Update(void)
{
	m_pModel->Update();

	if (m_type == TYPE_KEY)
	{
		m_nCountTimer++;
		if (m_nCountTimer % ITEM_KIRAKIRA_INTERVAL == 0)
		{
			CKira::EffectKira(m_pos, D3DXVECTOR3(KIRA_SIZE_X, KIRA_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255));
		}
	}

	//回転
	m_rot.y += ROT_ADDSPEED;

	if (m_Attribute == ITEM_DROP)
	{
		if (m_pos.y > (m_size.y * 1.5f))
		{
			m_move.y += -ITEM_GRAVITY;
			
		}
		else if(m_pos.y < (m_size.y * 1.5f))
		{
			m_pos.y = (m_size.y * 1.5f);
		}

	}
	else
	{
		//上下運動
		m_fRd += 0.1f;
		if (m_fRd > 360)
		{
			m_fRd = 0;
		}
		m_move.y = float(UPDOWN_SPEED * sin(m_fRd));
	}

	//位置更新
	m_pos += m_move;
	
	//情報更新
	SetItem(m_pos, m_rot, m_size);

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


void CItem::SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos; m_rot = rot; m_size = size;
	m_pModel->SetModel(m_pos, m_rot, m_size);
	SetObjType(OBJTYPE_ITEM);
}

void CItem::DropItem(D3DXVECTOR3 pos, TYPE type)
{
	//アイテム生成
	CItem * pItem = CItem::Create(pos, D3DXVECTOR3(ITEM_ROT_X, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 5.0f), TYPE_KEY);
	pItem->m_Attribute = ITEM_DROP;
	pItem->m_move = D3DXVECTOR3(0.0f, ITEM_UP_VALUE, 0.0f);
	
}
