#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "scene3d.h"

//----------------------------------------
//マクロ定義
//----------------------------------------
#define MAX_TYPE_POLYGON 2

class CPolygon:public CScene3d
{
public:

	CPolygon();			//インクリメント
	~CPolygon();		//デクリメント
	void Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理
private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TYPE_POLYGON] = {};
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;

};

#endif