#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "model.h"

class CEnemy :public CModel
{
public:
	CEnemy(int nPriority = CScene::OBJTYPE_ENEMY);//コンストラクタ
	~CEnemy();//デストラクタ

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//生成処理
	static HRESULT Load(void);//テクスチャの読み込み
	static void Unload(void);//テクスチャの破棄

	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size) {
		m_pos = pos; m_rot = rot; m_size = size;
		SetModel(pos, rot);
		SetObjType(OBJTYPE_ENEMY);
	}

	//受け取り処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }	//場所
	D3DXVECTOR3 GetSize(void) { return m_size; }//大きさ
private:
	static LPD3DXMESH m_pMesh;
	static LPD3DXBUFFER m_pBuffMat;
	static DWORD m_nNumMat;
	D3DXVECTOR3 m_pos;		//場所
	D3DXVECTOR3 m_rot;		//角度
	D3DXVECTOR3 m_size;		//大きさ
	static bool m_bChase;	//プレイヤーを追いかけるトリガー
	float m_fPlayerDirection;//プレイヤーの方向
};

#endif