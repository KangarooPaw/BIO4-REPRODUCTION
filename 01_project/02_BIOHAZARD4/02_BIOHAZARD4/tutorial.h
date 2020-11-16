//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//****************************************************************************************************
//ヘッダファイルのインクルード
//****************************************************************************************************
#include "mode.h"


class CPlayer;
class CBulletUi;
class CKey;
class CGate;
//****************************************************************************************************
//クラス定義
//****************************************************************************************************
class CTutorial :public CMode
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static CPlayer *m_pPlayer;	//プレイヤー
	static CBulletUi *m_pBulletUi;//弾の残弾数表示
	static CBulletUi *m_pBulletHaveUi;//持っている弾数表示
	static CKey *m_pKey;//持っているカギ表示
	static CGate *m_pGate;				// 門
	int m_nCount;
	bool m_bSoundGameStart;	//ゲームスタートサウンドが再生されているかの判定
};

#endif