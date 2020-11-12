//=============================================================================
//
// 弾数表示処理 [bullet_ui.h]
// Author : 林川紗梨夏
//
//=============================================================================
#ifndef _BULLET_UI_H_
#define _BULLET_UI_H_
#include "number.h"
#define MAX_DIGITS 10 //最大桁数
#define POINTS_SIZE_WIDTH 20.0f
#define POINTS_SIZE_HEIGHT 30.0f

#define DISPLAY_TIME 100 //表示時間
//2Dオブジェクトクラス
class CBulletUi : public CScene
{
public:

	CBulletUi(int nPriority = 8);
	~CBulletUi();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletUi * Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight, int points);
	void SetbulletUi(float nPoints);
	void AddPoints(float nValue);

private:
	D3DXVECTOR3                        m_pos;
	CNumber                           *m_apNumber[MAX_DIGITS];//ナンバー（最大桁数分）
	float                                m_nPoints; //スコアの数値
	float                                m_fFloatX;
	float                                m_fFloatY;
	int                                  m_digits;//けたすう
	int                                  m_nTimeCount;//表示時間
};
#endif // !_SCORE_H_
