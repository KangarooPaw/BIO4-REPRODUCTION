#ifndef _FADE_H_
#define _FADE_H_

#include "renderer.h"
#include "manager.h"
#include "mode.h"
#include "scene2d.h"

class CFade :public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT
	}FADE;

	CFade(int nPriority);							//コンストラクタ
	~CFade();										//デストラクタ
	HRESULT Init(void);								//初期化処理
	void Uninit(void);								//終了処理	
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
	void SetFade(CManager::MODE mode);
	void FadeIn(void);
	void FadeOut(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	D3DXCOLOR				m_color;				//色
	int						m_PolygonWidth;
	int						m_PolygonHeight;
	float					m_TexPos;
	static CManager::MODE	m_mode;
	static FADE				m_fade;
};
#endif // !_FADE_H_
