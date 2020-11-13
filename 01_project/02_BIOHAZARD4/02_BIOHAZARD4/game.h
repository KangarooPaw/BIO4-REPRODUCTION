//=============================================================================
//
// ゲーム処理 [game.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
//ヘッダファイルのインクルード
//*****************************************************************************
#include "mode.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CPlayer;
class CBulletUi;
class CKey;
class CGate;
//*****************************************************************************
//クラス定義
//*****************************************************************************
class CGame :public CMode
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer(void);
	static CBulletUi *GetBulletUi(void);
	static CBulletUi *GetBulletHaveUi(void);
	static CKey *GetKey(void);
	static CGate *GetGate(void) { return m_pGate; }
private:
	static CPlayer *m_pPlayer;	//プレイヤー
	static CBulletUi *m_pBulletUi;//弾の残弾数表示
	static CBulletUi *m_pBulletHaveUi;//持っている弾数表示
	static CKey *m_pKey;//持っているカギ表示
	static CGate *m_pGate;				// 門
	int m_nCount;
};

#endif