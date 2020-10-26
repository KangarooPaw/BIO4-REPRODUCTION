#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "scene.h"

class CScene3d :public CScene
{
public:
	CScene3d(int nPriority);//インクリメント
	~CScene3d();//デクリメント
	static CScene3d *Create(float nPosX, float nPosY);//生成処理
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);		//描画処理

	//各種設定
	void SetPosition(D3DXVECTOR3 pos);		//位置
	void SetRotation(D3DXVECTOR3 rot);		//角度
	void SetSize(D3DXVECTOR3 size);			//サイズ	
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//テクスチャ


private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
	int m_nType;
};
#endif //_SCENE3D_H_