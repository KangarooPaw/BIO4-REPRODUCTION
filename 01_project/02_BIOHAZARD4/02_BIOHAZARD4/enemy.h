#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

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
class CModel;

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemy :public CScene
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
	void HitBullet(int nDamage);

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size) {
		m_pos = pos; m_rot = rot; m_size = size;
		SetObjType(OBJTYPE_ENEMY);
	}

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	static LPD3DXMESH m_pMesh[MAX_ENEMY_PARTS];		 // メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[MAX_ENEMY_PARTS]; // マテリアル情報のポインタ
	static DWORD m_nNumMat[MAX_ENEMY_PARTS];		 // マテリアル情報の数
	static D3DXMATRIX m_mtxWorld[MAX_ENEMY_PARTS];	 // 行列計算用
	static int m_nldxModelParent[MAX_ENEMY_PARTS];	 // 親モデルのインデックス
	static char* m_apFileName[MAX_ENEMY_PARTS];		 // ファイルの名前
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ENEMY_PARTS];

	D3DXVECTOR3 m_pos;					// 場所
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 大きさ
	CMotion *m_pMotion;					// モーションクラスのポインタ
	CModel *m_pModel[MAX_ENEMY_PARTS]; // モデルクラスのポインタ
	static bool m_bChase;
	bool m_bHit;
	int m_nEnemyLife;
	int m_nCntFrame;
};

#endif