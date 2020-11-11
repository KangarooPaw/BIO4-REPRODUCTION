#pragma once
//=============================================================================
//
// アイテムの処理 [item.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModel;

#define ITEM_ROT_X 0.5f //傾き

#define ITEM_SIZE 2.0f
//=============================================================================
// プレイヤークラス
//=============================================================================
class CItem :public CScene
{
public:
	CItem(int nPriority = CScene::OBJTYPE_ITEM);//コンストラクタ
	~CItem();//デストラクタ

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_HABU,//ハーブ
		TYPE_SUPURE,//スプレー
		TYPE_AMMO,//弾薬
		TYPE_KEY,//カギ
		TYPE_MAX
	}TYPE;
	typedef enum
	{
		ITEM_NONE = -1,
		ITEM_DROP,//ハーブ
		ITEM_MAX
	}ITEM_ATTRIBUTE;
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type);//生成処理
	static HRESULT Load(void);//モデルの読み込み
	static void Unload(void);//モデルの破棄
	static HRESULT LoadTexture(void);//テクスチャの読み込み
	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	static void DropItem(D3DXVECTOR3 pos, TYPE type);//ドロップアイテム
	//受け渡し処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }//場所
	D3DXVECTOR3 GetRot(void) { return m_rot; }//角度
private:
	bool CItem::CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2);
	static LPD3DXMESH m_pMesh[TYPE_MAX];	  // メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX]; // マテリアル情報のポインタ
	static DWORD m_nNumMat[TYPE_MAX];	 // マテリアル情報の数
	D3DXMATRIX m_mtxWorld;	     // 行列計算用
	static char* m_apFileName[TYPE_MAX]; // ファイルの名前
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX][50];
	ITEM_ATTRIBUTE m_Attribute;//アイテム属性
	D3DXVECTOR3 m_pos;					// 場所
	D3DXVECTOR3 m_move;//移動量
	float m_fRd;//ラジアン
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 大きさ
	int         m_type;                 //種類
	int         m_nCountTimer;         //カウント
	CModel *m_pModel; // モデルクラスのポインタ
};

#endif