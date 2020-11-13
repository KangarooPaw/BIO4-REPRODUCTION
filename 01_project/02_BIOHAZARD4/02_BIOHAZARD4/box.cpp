//-----------------------------------------------------------
// 木箱
// box.cpp
// Author : 林川紗梨夏
//-----------------------------------------------------------

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "player.h"
#include "box.h"
#include "model.h"
#include "item.h"
#include "boxeffect.h"
#include "sound.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CBox::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CBox::m_pBuffMat[TYPE_MAX] = {};
DWORD CBox::m_nNumMat[TYPE_MAX] = {};
//D3DXMATRIX CItem::m_mtxWorld = {};	 // 行列計算用
char* CBox::m_apFileName[TYPE_MAX] = { { "data/MODEL/OBJECT/box.x" },
{ "data/MODEL/OBJECT/box02.x" } };// 箱
LPDIRECT3DTEXTURE9 CBox::m_pTexture[TYPE_MAX][50] = {};

//----------------------------------------
//インクリメント
//----------------------------------------
CBox::CBox(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_pModel = NULL;
	m_mtxWorld = {};
	m_bHit = false;
}

//----------------------------------------
//デクリメント
//----------------------------------------
CBox::~CBox()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CBox * CBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type)
{
	CBox *pItem;
	pItem = new CBox;
	pItem->m_type = type;
	pItem->Init();
	pItem->SetBox(pos, rot, size);

	return pItem;
}

//----------------------------------------
//モデルの読み込み
//----------------------------------------
HRESULT CBox::Load(void)
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
HRESULT CBox::LoadTexture(void)
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
void CBox::Unload(void)
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
HRESULT CBox::Init(void)
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
void CBox::Uninit(void)
{
	// モデルクラスの終了処理
	m_pModel->Uninit();
	m_pModel = NULL;
}

//----------------------------------------
//更新処理
//----------------------------------------
void CBox::Update(void)
{
	/*CScene3d::Update();*/
	SetBox(m_pos, m_rot, m_size);
	CScene *pScene = NULL;

	do
	{
		pScene = GetScene(OBJTYPE_PLAYER);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BULLET)
			{
				// 座標とサイズの受け取り
				D3DXVECTOR3 Getpos = ((CPlayer*)pScene)->GetPos();
				D3DXVECTOR3 Getsize = ((CPlayer*)pScene)->GetSize();

				// 当たり判定
				if (CollisionItem(m_pos, m_size, Getpos, Getsize) == true)
				{
					//// アイテムを消す
					/*Uninit();
					return;*/
				}
			}
		}
	} while (pScene != NULL);
}

//----------------------------------------
//描画処理
//----------------------------------------
void CBox::Draw(void)
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

//壊されたときの処理
bool CBox::HitBox(void)
{
	if (m_bHit == false)
	{
		//サウンドの再生
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_WOODEN_BOX);

		int nRand = rand() % 3;
		//アイテム生成
		CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 5.0f, m_pos.z), D3DXVECTOR3(ITEM_ROT_X, 0.0f, 0.0f), D3DXVECTOR3(ITEM_SIZE, ITEM_SIZE, ITEM_SIZE), (CItem::TYPE)nRand);
		// モデルのバインド
		m_pModel->BindModel(m_pMesh[TYPE_BREAKED], m_pBuffMat[TYPE_BREAKED], m_nNumMat[TYPE_BREAKED], -1);

		m_pos.y = 0.0f;

		m_bHit = true;
		//破壊エフェクト
		CBoxEffect::BreakBox(m_pos, m_size, m_rot, D3DCOLOR_RGBA(255, 255, 255, 255));
		return true;//当たっていることを返す
	}
	else
	{
		return false;//当っていない(既に壊されている)ことを返す
	}
}
//当たり判定
bool CBox::CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2)
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

void CBox::SetBox(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos; m_rot = rot; m_size = size;
	m_pModel->SetModel(m_pos, m_rot, m_size);
	SetObjType(OBJTYPE_BOX);
}