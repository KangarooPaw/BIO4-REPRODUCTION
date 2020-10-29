#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "model_hierarchy.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ENEMY_PARTS (13) // プレイヤーのモデルのパーツの最大数
#define MOTION_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/motion.txt") // モーションのテキスト
#define LOAD_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/enemy.txt") // 各モデルパーツの初期値

//=============================================================================
// 前方宣言
//=============================================================================
class CMotion;

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemy :public CModelhierarchy
{
public:
	CEnemy(int nPriority = CScene::OBJTYPE_ENEMY);
	~CEnemy();

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size) {
		m_pos = pos; m_rot = rot; m_size = size;
		SetModel(pos, rot, size);
		SetObjType(OBJTYPE_ENEMY);
	}

private:
	typedef struct {
		char* pFileName;	   // 読み込みファイル名
		int nIndex;			   // モデルナンバー
		int nParents;		   // モデルの親子関係
		D3DXVECTOR3 pos;	   // 位置
		D3DXVECTOR3 rot;	   // 角度
	}MODELPARENT;

	static LPD3DXMESH m_pMesh[MAX_ENEMY_PARTS];
	static LPD3DXBUFFER m_pBuffMat[MAX_ENEMY_PARTS];
	static DWORD m_nNumMat[MAX_ENEMY_PARTS];
	static MODELPARENT m_modelParent[MAX_ENEMY_PARTS];
	D3DXVECTOR3 m_pos;			//場所
	D3DXVECTOR3 m_rot;			//角度
	D3DXVECTOR3 m_size;			//大きさ
	CMotion *m_pMotion;
};

#endif