//=============================================================================
//
// 扉の処理 [gate.h]
// Author : 管原　司
//
//=============================================================================
#ifndef _GATE_H_
#define _GATE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CModel;

//マクロ定義
#define GATE_SIZE 50.0f
//=============================================================================
// プレイヤークラス
//=============================================================================
class CGate :public CScene
{
public:
	CGate(int nPriority = CScene::OBJTYPE_GATE);//コンストラクタ
	~CGate();//デストラクタ

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_LEFT,// 右
		TYPE_RIGHT,//左
		TYPE_MAX
	}TYPE;
	static CGate *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//生成処理
	static HRESULT Load(void);//モデルの読み込み
	static void Unload(void);//モデルの破棄
	static HRESULT LoadTexture(void);//テクスチャの読み込み
	HRESULT Init(void);//初期化処理
	void Uninit(void);//終了処理
	void Update(void);//更新処理
	void Draw(void);//描画処理
	void SetGate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	//受け渡し処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }//場所
	D3DXVECTOR3 GetRot(void) { return m_rot; }//角度
	D3DXVECTOR3 GetSize(void) { return m_size; };//サイズ
	bool GetOpen(void) { return m_bOpen; }
private:
	static LPD3DXMESH m_pMesh[TYPE_MAX];	  // メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX]; // マテリアル情報のポインタ
	static DWORD m_nNumMat[TYPE_MAX];	 // マテリアル情報の数
	D3DXMATRIX m_mtxWorld[TYPE_MAX];	     // 行列計算用
	static char* m_apFileName[TYPE_MAX]; // ファイルの名前
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX][50];

	D3DXVECTOR3 m_pos;					// 場所
	D3DXVECTOR3 m_rot;					// 角度
	D3DXVECTOR3 m_size;					// 大きさ
	CModel *m_pModel[TYPE_MAX]; // モデルクラスのポインタ
	bool m_bOpen;
	bool m_bmove;
	int m_nCount;						//	カウント
	bool m_bSoundGateOpen;				//ゲートを開けるサウンドが再生されているかの判定
};

#endif