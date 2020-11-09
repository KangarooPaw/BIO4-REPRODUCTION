//-----------------------------------------------------------
// Paricle
// paricle.h
// Author : 管原　司
//-----------------------------------------------------------
#ifndef _PERTICLE_H_
#define _PERTICLE_H_
//----------------------------------------------------
// マクロ定義
//----------------------------------------------------
#define EXPLOSION_SIZE_X 10					// 爆発のサイズX
#define EXPLOSION_SIZE_Y 10					// 爆発のサイズY
#define SPARK_SIZE_X 5.0f					// 火花のサイズX
#define SPARK_SIZE_Y 50.0f					// 火花のサイズY
#define SMOKE_SIZE_X 10						// 煙のサイズX
#define SMOKE_SIZE_Y 10						// 爆発のサイズY
#define BLOOD_SIZE_X 15						// 血のサイズX
#define BLOOD_SIZE_Y 10						// 血のサイズY
#define MAZLE_FLASH_SIZE_X 5				// マズルフラッシュのサイズX
#define MAZLE_FLASH_SIZE_Y 5				// マズルフラッシュのサイズY
#define PARTICLE_HIT_SIZE_X 20				// ヒットパーティクルサイズX
#define PARTICLE_HIT_SIZE_Y 20				// ヒットパーティクルサイズY
#define PARTICLE_CIRCLE_SIZE_X 7			// 円パーティクルサイズX
#define PARTICLE_CIRCLE_SIZE_Y 200			// 円パーティクルサイズY
#define PARTICLE_CIRCLE_COL_MAX 0.5f		// 円のカラー最大値
#define PARTICLE_CIRCLE_COL_MIN 0.1f		// 円のカラー最小値

#include "billboard.h"

class CParticle : public CBillboard
{
public:

	// パーティクルタイプ
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_EXPLOSION,
		TYPE_SPARK,
		TYPE_SMOKE,
		TYPE_HIT,
		TYPE_CIRCLE,
		TYPE_MAZLE_FLASH,
		TYPE_MAX,
	}TYPE;

	// テクスチャタイプ
	typedef enum
	{
		TEX_TYPE_NONE = 0,
		TEX_TYPE_1,
		TEX_TYPE_2,
		TEX_TYPE_MAX,
	}TEX_TYPE;

	// カラー加算、減算
	typedef enum
	{
		COLOR_NONE = 0,
		COLOR_ADD,
		COLOR_MIN,
	}COLOR_TYPE;
	CParticle(int nPriority = 7);
	~CParticle();
	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, float fRadian, float fLength, TYPE Type, TEX_TYPE TexType);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, float fRadian, float fLength, TYPE Type, TEX_TYPE TexType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];	// texture
	D3DXVECTOR3 m_pos;								// 位置座標
	D3DXVECTOR3 m_rot;								// 向き
	D3DXVECTOR3 m_size;								// サイズ
	D3DXVECTOR3 m_move;								// 移動量
	D3DXCOLOR m_col;								// カラー
	TYPE m_Type;									// タイプ
	TEX_TYPE m_TexType;								// テクスチャタイプ
	COLOR_TYPE m_ColorType;							// カラータイプ
	float m_fRadian;
	float m_fLength;
	float m_fAngle;
	float m_fScale;									// 拡大率
	float m_fAddScale;								// 拡大率加算
	float m_fAddColor;								// カラー加算
	int m_nCount;									// カウント
};
#endif