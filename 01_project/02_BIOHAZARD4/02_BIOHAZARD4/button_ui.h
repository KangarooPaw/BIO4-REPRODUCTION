//---------------------------------------------------
// Life
// Life.h
// Author:	管原司
//---------------------------------------------------
#ifndef _BUTTON_UI_H_
#define _BUTTON_UI_H_
#define BUTTON_UI_SIZE_X 100
#define BUTTON_UI_SIZE_Y 100
#define BUTTON_UI_POS D3DXVECTOR3(SCREEN_WIDTH / 2,600.0f,0.0f)
#include "scene2d.h"

//---------------------------------------------------
//クラス
//---------------------------------------------------
class CButton_UI : public CScene2D
{
public:
	// 種類
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PICKUP,
		TYPE_SPIN,
		TYPE_MAX
	}TYPE;
	CButton_UI(int nPriority = OBJTYPE_UI);
	~CButton_UI();

	static CButton_UI * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetbUse(bool bUse);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	// テクスチャ情報
	static bool m_bUse;									// 使用判定
	int m_Type;											// タイプ
};
#endif