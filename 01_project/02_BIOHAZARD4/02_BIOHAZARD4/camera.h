#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

#define MOVE_RATE 80
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR3 GetPosR(void) { return posR; }
private:
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	D3DXVECTOR3 vecU;
	D3DXMATRIX	mtxProjection;
	D3DXMATRIX	mtxView;
	float m_Distance;
	float m_lTheta;
	float m_rTheta;
	float m_lPhi;
	float m_rPhi;
};

#endif