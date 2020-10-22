#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"
#define MOVE_RATE 80
class CCamera
{
public:
	CCamera();
	~CCamera();
	static CCamera *Create(void);
	void Init(void);
	void Uninit(void);
	void Update(void);
private:
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	D3DXVECTOR3 vecU;
	D3DXMATRIX	mtxProjection;
	D3DXMATRIX	mtxView;
	D3DXVECTOR3 rot;
	float		fDistance;
};

#endif