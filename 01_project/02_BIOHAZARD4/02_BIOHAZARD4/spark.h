//--------------------------------------------------------------------
// Spark
// Spark.h
// Author : 管原 司
//--------------------------------------------------------------------
#ifndef _SPARK_H_
#define _SPARK_H_

#define SPARK_SIZE_X 5.0f		// 火花のサイズX
#define SPARK_SIZE_Y 50.0f		// 火花のサイズY

#include"particle.h"

//--------------------------------------------------------------------
//クラス
//--------------------------------------------------------------------
class CSpark : public CParticle
{
public:
	CSpark();
	~CSpark();
	static CSpark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3 m_move;		// 移動
	float m_fAddColor;		// カラー加算値
	int m_nCount;			// カウント
};
#endif