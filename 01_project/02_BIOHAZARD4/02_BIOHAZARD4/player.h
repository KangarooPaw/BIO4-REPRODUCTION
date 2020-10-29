#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "model_hierarchy.h"

#define MAX_PLAYER_PARTS (13)

class CPlayer :public CModelhierarchy
{
public:
	typedef struct {
		char* pFileName;	   //読み込みファイル名
		int modelparentIndex;  //モデルの親子関係
		int nIndex;
		int nParents;		   // モデルナンバー
		D3DXVECTOR3 pos;	   // 位置
		D3DXVECTOR3 posOrigin; // 始まりの位置
		D3DXVECTOR3 rot;	   // 角度
	}MODELPARENT;

	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);//コンストラクタ
	~CPlayer();//デストラクタ

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//生成処理
	static HRESULT Load(void);//テクスチャの読み込み
	static void Unload(void);//テクスチャの破棄

	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理

	//初期設定
	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	//受け渡し処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }//場所
	D3DXVECTOR3 GetRot(void) { return m_rot; }//角度
private:
	static LPD3DXMESH m_pMesh[MAX_PLAYER_PARTS];
	static LPD3DXBUFFER m_pBuffMat[MAX_PLAYER_PARTS];
	static DWORD m_nNumMat[MAX_PLAYER_PARTS];
	D3DXVECTOR3 m_pos;			//場所
	D3DXVECTOR3 m_rot;			//角度
	D3DXVECTOR3 m_size;			//大きさ
	static MODELPARENT m_modelParent[MAX_PLAYER_PARTS];
};

#endif