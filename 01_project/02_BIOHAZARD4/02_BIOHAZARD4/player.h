//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PLAYER_PARTS (15) // プレイヤーのモデルのパーツの最大数
#define MAX_MATERIAL (50)
#define MOTION_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/motion.txt") // モーションのテキスト
#define LOAD_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/player.txt") // 各モデルパーツの初期値

#define MAX_BULLET_ROT_X	(15)	//弾の角度(X)最大値
#define MAX_BULLET_ROT_Y	(20)	//弾の角度(Y)最大値
#define MIN_BULLET_ROT_X	(-15)	//弾の角度(X)最小値
#define MIN_BULLET_ROT_Y	(-20)	//弾の角度(Y)最小値

#define MAX_MAGAZINE_BULLET	(15)	//最大装弾数

//=============================================================================
// 前方宣言
//=============================================================================
class CMotion;
class CModel;
class CReticle;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer :public CScene
{
public:
	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);//コンストラクタ
	~CPlayer();//デストラクタ

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//生成処理
	static HRESULT Load(void);//モデルの読み込み
	static void Unload(void);//モデルの破棄
	static HRESULT LoadTexture(void);//テクスチャの読み込み

	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	
	void Keyboard(void);//キーボードの処理
	void GamePad(void);//ゲームパッド処理
	
	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//各種設定
	void HitDamage(int nDamage);	//ダメージ処理
	void PickUpItem(void);			//アイテム取得処理
	static void DeathFlag(void);	//死亡フラグ

	//受け渡し処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }//場所
	D3DXVECTOR3 GetRot(void) { return m_rot; }//角度
	D3DXVECTOR3 GetSize(void) { return m_size; }//サイズ
	bool GetDeath(void) { return m_bDeath; }//死亡フラグ
private:
	bool CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2);

	static LPD3DXMESH m_pMesh[MAX_PLAYER_PARTS];	  // メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[MAX_PLAYER_PARTS]; // マテリアル情報のポインタ
	static DWORD m_nNumMat[MAX_PLAYER_PARTS];		  // マテリアル情報の数
	static D3DXMATRIX m_mtxWorld[MAX_PLAYER_PARTS];	  // 行列計算用
	static int m_nldxModelParent[MAX_PLAYER_PARTS];	  // 親モデルのインデックス
	static char* m_apFileName[MAX_PLAYER_PARTS];	  // ファイルの名前
	static char* m_apTextureFileName[MAX_PLAYER_PARTS]; //テクスチャのファイルの名前
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PLAYER_PARTS][MAX_MATERIAL];

	D3DXVECTOR3 m_pos;					// 場所
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 大きさ

	D3DXVECTOR3 m_bulletRot;			// 弾の角度
	int m_bulletRotX;					// 弾の角度(X)変更数のカウント
	int m_bulletRotY;					// 弾の角度(Y)変更数のカウント

	int m_nMagazineBullet;				//マガジンの装弾数
	int m_nHaveBullet;					//所持弾数
	int m_nKey;//鍵所持数

	int m_nKnifeMotionCnt;				// ナイフモーションのカウント	
	bool m_bKnifeMotion;				// ナイフモーションの判定

	int m_nDamageMotionCnt;				// ダメージモーションのカウント
	bool m_bDamageMotion;				// ダメージモーションの判定

	int m_nDeathMotionCnt;				//死亡モーションのカウント
	bool m_bDeathMotion;				//死亡モーションの判定
	static bool m_bDeath;				//死亡フラグ

	int m_nTurnCnt;						// ターンのカウント
	bool m_bTurn;						// ターンの判定

	bool m_bReticle;					// レティクルの生成判定

	CMotion *m_pMotion;					// モーションクラスのポインタ
	CModel *m_pModel[MAX_PLAYER_PARTS]; // モデルクラスのポインタ

};

#endif