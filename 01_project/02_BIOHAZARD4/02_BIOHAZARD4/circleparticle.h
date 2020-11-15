//--------------------------------------------------------------------
// CircleParticle
// circleparticle.h
// Author : 管原 司
//--------------------------------------------------------------------
#ifndef _CIRCLEPARTICLE_H_
#define _CIRCLEPARTICLE_H_

#define PARTICLE_CIRCLE_SIZE_X 4			// 円パーティクルサイズX
#define PARTICLE_CIRCLE_SIZE_Y 50			// 円パーティクルサイズY
#define PARTICLE_CIRCLE_COL_MAX 0.5f		// a値最大値
#define PARTICLE_CIRCLE_COL_MIN 0.1f		// a値最小値
#define MAX_CIRCLE 20						// 円の最大

#include"particle.h"

//--------------------------------------------------------------------
//クラス
//--------------------------------------------------------------------
class CCircleParticle : public CParticle
{
public:
	// カラー加算、減算
	typedef enum
	{
		COLOR_NONE = 0,
		COLOR_ADD,
		COLOR_MIN,
	}COLOR_TYPE;

	CCircleParticle(int nPriority = OBJTYPE_CIRCLE);
	~CCircleParticle();
	static CCircleParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void CircleCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, int nMax, float fLength);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
private:
	D3DXVECTOR3 m_pos;		// 位置座標
	COLOR_TYPE m_ColorType;	// カラータイプ
	float m_fRadian;		// 弧度
	float m_fLength;		// 半径
	float m_fAngle;			// 角度
	float m_fAddColor;		// カラー加算値
};
#endif