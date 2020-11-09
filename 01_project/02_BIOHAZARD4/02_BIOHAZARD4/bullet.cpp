//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author:伊藤陽梧
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "box.h"
#include "ui.h"
#include "camera.h"
#include "blood.h"


//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9	CBullet::m_pTexture = NULL;

//=============================================================================
// バレットクラスのコンストラクタ
//=============================================================================
CBullet::CBullet(int nPriority) :CScene3d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//現在の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //大きさ
	m_Getpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Getsize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = BULLETTYPE_PLAYER;	//種類
	m_nLife = 0;			//寿命
	m_nDamage = 0;      //ダメージ
}

//=============================================================================
// バレットクラスのデストラクタ
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// バレットクラスのインスタンス生成
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nLife, int nDamage, BULLETTYPE type)
{
	CBullet *pBullet;
	pBullet = new CBullet;

	// 弾のセット
	pBullet->SetBullet(pos, size, move, nLife, nDamage, type);
	pBullet->Init();

	return pBullet;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"PolygonTexture1.png",								// ファイルの名前
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CBullet::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//バレットクラスの初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{	
	CScene3d::BindTexture(m_pTexture);
	CScene3d::Init();
	return S_OK;
}

//=============================================================================
// バレットクラスの終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene3d::Uninit();
}

//=============================================================================
//バレットクラスの更新処理
//=============================================================================
void CBullet::Update(void)
{
	
	//移動量を反映させる
	m_pos += m_move;

	//弾の射程を決める
	m_nLife--;

	CScene *pScene = NULL;

	do
	{
		pScene = GetScene(OBJTYPE_ENEMY);
		if (pScene != NULL)
		{	
			if (m_type==BULLETTYPE_PLAYER)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_ENEMY)
				{
					// 座標とサイズの受け取り
					m_Getpos = ((CEnemy*)pScene)->GetPos();
					m_Getsize = ((CEnemy*)pScene)->GetSize();

					// 当たり判定
					if (CollisionBullet(m_pos, m_size, m_Getpos, m_Getsize) == true)
					{
						// 敵を消す
						((CEnemy*)pScene)->HitBullet(m_nDamage);

						// 弾を消す
						Uninit();
						return;
					}
				}
			}
		}
	} while (pScene != NULL);

	do//プレイヤーの当たり判定
	{
		pScene = GetScene(OBJTYPE_PLAYER);
		if (pScene != NULL)
		{
			if (m_type == BULLETTYPE_ENEMY)
			{
				OBJTYPE objType = pScene->GetObjType();
				if (objType == OBJTYPE_PLAYER)
				{
					m_Getpos = ((CPlayer*)pScene)->GetPos();
					m_Getsize = ((CPlayer*)pScene)->GetSize();
					CBlood::BloodSplash(m_pos, D3DXVECTOR3(SPLACH_BLOOD_SIZE_X, SPLACH_BLOOD_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 0, 0, 255));
					// 当たり判定
					if (CollisionBullet(m_pos, m_size, m_Getpos, m_Getsize) == true)
					{
						// 敵を消す
						((CPlayer*)pScene)->HitDamage(m_nDamage);

						// 弾を消す
						Uninit();
						return;
					}
				}
			}
		}
	} while (pScene != NULL);

	do//箱の当たり判定
	{
		pScene = GetScene(OBJTYPE_BOX);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_BOX)
			{
				// 座標とサイズの受け取り
				m_Getpos = ((CBox*)pScene)->GetPos();
				m_Getsize = ((CBox*)pScene)->GetSize();

				// 当たり判定
				if (CollisionBullet(m_pos, m_size, m_Getpos, m_Getsize) == true)
				{
					// 箱を破壊する
					bool bHit = ((CBox*)pScene)->HitBox();
					//破壊したら消す（すでに破壊されているものは貫通する）
					if (bHit == true)
					{
						// 弾を消す
						Uninit();
						return;
					}
				}
				else if (m_nLife <= 0)
				{ // ライフがなくなったら消す
					Uninit();
					return;
				}
			}
		}
	} while (pScene != NULL);

	if (m_nLife <= 0)
	{ // ライフがなくなったら消す
		Uninit();
		return;
	}

	// 座標のセット
	SetPosition(m_pos);
	CScene3d::Update();
}

//=============================================================================
//バレットクラスの描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene3d::Draw();
}

//=============================================================================
//バレットクラスのタイプを渡す処理
//=============================================================================
CBullet::BULLETTYPE CBullet::GetBulletType(void)
{
	return m_type;
}

//=====================================================
// バレットクラスの当たり判定の設定
//=====================================================
bool CBullet::CollisionBullet(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2)
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