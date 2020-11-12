#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "scene.h"
//-----------------------------------------------
//クラス
//-----------------------------------------------
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = 3);
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }
	void SetTexture(float fTexX, float fTexY, float fTexX2, float fTexY2);
	void SetScale(float fScale);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetAlpha(int nAlpha);
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						// 位置座標
	D3DXVECTOR3 m_size;						// サイズ
	D3DXVECTOR3 m_rot;						// 向き
	D3DXCOLOR m_col;	// カラー
	float                              m_fTexX;      //テクスチャX座標
	float                              m_fTexX2;      //テクスチャX2座標
	float                              m_fTexY;      //テクスチャY座標
	float                              m_fTexY2;      //テクスチャY座標
	D3DXMATRIX m_mtxWorld;					// マトリックス
	float m_fScale;							// 拡大
	int m_nAlpha;							// 透過値
};
#endif