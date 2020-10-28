#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "scene.h"

class CScene2D :public CScene
{
public:
	CScene2D(int nPriority);
	~CScene2D();

	static CScene2D *Create(float nPosX, float nPosY);

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void SetPosition(D3DXVECTOR3 pos);		//位置
	void SetSize(D3DXVECTOR3 size);			//サイズ
	void SetColor(D3DXCOLOR color);
	void SetRotVertex(float sizeX, float sizeY, float fAngle);

	D3DXVECTOR3 GetPosition(void);
	D3DXCOLOR GetColor(void);

private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	D3DXVECTOR3				m_size;
	D3DXCOLOR				m_color;
	int						m_PolygonWidth;
	int						m_PolygonHeight;
	float					m_angleX, m_angleY;
};

#endif // !_SCENE2D_H_
