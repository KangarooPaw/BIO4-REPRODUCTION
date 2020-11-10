//---------------------------------------------------
// Life
// Life.h
// Author:	管原司
//---------------------------------------------------
#ifndef _LIFE_H_
#define _LIFE_H_
#define LIFE_SIZE_X 25
#define LIFE_SIZE_Y 25
#define MAX_LIFE 100
#define FADE_RATE	0.01f

#include "scene2d.h"

//---------------------------------------------------
//クラス
//---------------------------------------------------
class CLife : public CScene
{
public:
	//フェード
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
	}FADE;
	//色
	typedef enum
	{
		STATE_NONE = 0,
		STATE_GREEN,
		STATE_YELLOW,
		STATE_RED,
	}STATE;
	CLife(int nPriority = 5);
	~CLife();
	static CLife * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float Length);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void LifeDecrement(int nDamage);
private:
	CScene2D *m_apScene2D[MAX_POLYGON];	//Scene2d情報
	D3DXVECTOR3 m_pos;					//位置情報
	D3DXVECTOR3 m_size;					//サイズ
	D3DXCOLOR m_col;					//カラー
	FADE m_Fade;						//Fade
	STATE m_State;						//State
	float m_fRadian;					//弧度
	float m_fLengh;						//半径
	int m_nCnt;							//カウント
	static int m_nDamageCnt;			//ダメージを受けるカウント
	static bool m_bHit;					//ダメージを受けている判定
};
#endif