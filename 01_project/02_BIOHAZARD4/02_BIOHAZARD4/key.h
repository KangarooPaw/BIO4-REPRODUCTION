//=============================================================================
//
// スコア処理 [life.h]
// Author : 
//
//=============================================================================
#ifndef _KEY_H_
#define _KEY_H_
#include "key_ui.h"
#define MAX_KEY 4 //最大桁数
#define PLAYER_LIFE 1 //プレイヤーのライフ
//2Dオブジェクトクラス
class CKey : public CScene
{
public:

	CKey(int nPriority = 8);
	~CKey();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CKey * Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight);
	void SetKeyUi(int nLife);

private:
	CKeyUi                           *m_apKeyUi[MAX_KEY];//星（最大桁数分）
	D3DXVECTOR3                        m_pos;//位置
	int                                m_nKey; //スコアの数値
	float                              m_fSizeWidth;//幅
	float                              m_fSizeHeight;//高さ
};
#endif // !_LIFE_H_
