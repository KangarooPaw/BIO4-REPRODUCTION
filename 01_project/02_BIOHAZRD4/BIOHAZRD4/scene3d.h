#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "scene.h"

class CScene3d :public CScene
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXMATRIX mtxWorld;
		int nType;
	}POLYGON;

	CScene3d();
	~CScene3d();	
	static CScene3d *Create(float nPosX, float nPosY);
	virtual HRESULT Init(float nPosX, float nPosY, int nPolygonWidth, int nPolygonHeight);	//初期化処理
	virtual void Uninit(void);	//終了処理
	virtual void Update(void);	//更新処理
	virtual void Draw(void);		//描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	int						m_PolygonWidth;
	int						m_PolygonHeight;
	POLYGON					m_Polygon;
};
#endif //_SCENE3D_H_