//-----------------------------------------------------------
// 門
// gate.cpp
// Author : 管原　司
//-----------------------------------------------------------

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "player.h"
#include "model.h"
#include "gate.h"
#include "game.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CGate::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CGate::m_pBuffMat[TYPE_MAX] = {};
DWORD CGate::m_nNumMat[TYPE_MAX] = {};
char* CGate::m_apFileName[TYPE_MAX] = { { "data/MODEL/MAP/x/gate_left.x" },
{ "data/MODEL/MAP/x/gate_right.x" } };// 門
LPDIRECT3DTEXTURE9 CGate::m_pTexture[TYPE_MAX][50] = {};

//----------------------------------------
//インクリメント
//----------------------------------------
CGate::CGate(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(m_pModel, 0, sizeof(m_pModel));
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
	m_bOpen = false;
	m_bmove = false;
	m_nCount = 0;
}

//----------------------------------------
//デクリメント
//----------------------------------------
CGate::~CGate()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CGate * CGate::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CGate *pGate;
	pGate = new CGate(OBJTYPE_GATE);
	pGate->SetGate(pos, rot, size);
	pGate->Init();

	return pGate;
}

//----------------------------------------
//モデルの読み込み
//----------------------------------------
HRESULT CGate::Load(void)
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
HRESULT CGate::LoadTexture(void)
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
void CGate::Unload(void)
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
HRESULT CGate::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// モデルの生成
		m_pModel[nCnt] = CModel::Create();

		// モデルのバインド
		m_pModel[nCnt]->BindModel(m_pMesh[nCnt], m_pBuffMat[nCnt], m_nNumMat[nCnt], -1);

		for (int nCntMat = 0; nCntMat < (signed)m_nNumMat[nCnt]; nCntMat++)
		{
			// テクスチャのバインド
			m_pModel[nCnt]->BindTexture(m_pTexture[nCnt][nCntMat], nCntMat);
		}
	}

	m_pModel[TYPE_LEFT]->SetModel(D3DXVECTOR3(m_pos.x - 142, m_pos.y, m_pos.x), m_rot, m_size);
	m_pModel[TYPE_RIGHT]->SetModel(D3DXVECTOR3(m_pos.x + 142, m_pos.y, m_pos.x), -m_rot, m_size);
	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CGate::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// モデルクラスの終了処理
		m_pModel[nCnt]->Uninit();
		m_pModel[nCnt] = NULL;
	}
}

//----------------------------------------
//更新処理
//----------------------------------------
void CGate::Update(void)
{
	// プレイヤーがカギを持っているかを取得
	bool bPlayerHasKey = CGame::GetPlayer()->GetHasKeyAll();
	// プレイヤーがカギを持っている場合
	if (bPlayerHasKey == true)
	{
		if (m_bmove == false)
		{
			// m_bOpenをtrueに
			m_bOpen = true;
			// m_bOpenがtrueの場合
			if (m_bOpen == true)
			{
				// カウントインクリメント
				m_nCount++;
				// m_nCountが60以上の場合
				if (m_nCount >= 60)
				{
					// カウントが2
					if (m_nCount % 2 == 0)
					{
						// rot.yを0.5fずつ加算
						m_rot.y += D3DXToRadian(0.5f);
					}
				}
				// rot.yが60以上の場合
				if (m_rot.y >= D3DXToRadian(60.0f))
				{
					// m_bOpenをfalseに
					m_bOpen = false;
					// m_bOpenをtrueに
					m_bmove = true;
				}
			}
		}

	}
	// モデルの更新
	m_pModel[TYPE_LEFT]->SetModel(D3DXVECTOR3(m_pos.x - 142, m_pos.y, m_pos.x), m_rot, m_size);
	m_pModel[TYPE_RIGHT]->SetModel(D3DXVECTOR3(m_pos.x + 142, m_pos.y, m_pos.x), -m_rot, m_size);
}

//----------------------------------------
//描画処理
//----------------------------------------
void CGate::Draw(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトの効果を無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// TYPE_MAX分回す
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&m_mtxWorld[nCnt]);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCnt], &m_mtxWorld[nCnt], &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCnt], &m_mtxWorld[nCnt], &mtxTrans);

		//ワールドマトリックスの設定
		m_pModel[nCnt]->SetWorldMatrix(m_mtxWorld[nCnt]);

		// モデルクラスの描画処理
		m_pModel[nCnt]->Draw();
	}
	// ライトの効果を有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CGate::SetGate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// モデルの情報を代入
	m_pos = pos; m_rot = rot; m_size = size;
	// オブジェクトを設定
	SetObjType(OBJTYPE_GATE);
}