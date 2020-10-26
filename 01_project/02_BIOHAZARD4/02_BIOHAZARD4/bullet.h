//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene3d.h"

class CBullet :public CScene3d
{
public:
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,	// プレイヤーの弾
		BULLETTYPE_ENEMY,		// 敵の弾
		BULLETTYPE_MAX
	}BULLETTYPE;

	CBullet(int nPriority = CScene3d::OBJTYPE_BULLET);
	~CBullet();

	static CBullet*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		D3DXVECTOR3 move, int nLife, int nDamage, BULLETTYPE type);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, 
		int nLife, int nDamage, BULLETTYPE type) {
		m_pos = pos; m_size = size; m_move = move; 
		m_nLife = nLife; m_nDamage = nDamage; m_type = type;
		SetPosition(m_pos); SetSize(m_size);
		SetObjType(OBJTYPE_BULLET);
	}

	BULLETTYPE GetBulletType(void);
	bool CollisionBullet(D3DXVECTOR3 pPos1, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;	   //現在の位置
	D3DXVECTOR3 m_size;    //大きさ
	D3DXVECTOR3 m_move;	   //移動量
	D3DXVECTOR3 m_Getpos;  // 受け取った座標
	D3DXVECTOR3 m_Getsize; // 受け取ったサイズ
	BULLETTYPE m_type;	   //種類
	int m_nLife;		   //寿命
	int m_nDamage;		   //ダメージ
};
#endif