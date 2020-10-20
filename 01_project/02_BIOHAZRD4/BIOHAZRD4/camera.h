#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"
#define MOVE_RATE 80
class CCamera
{
public:
	typedef struct
	{
		D3DXVECTOR3 posV;
		D3DXVECTOR3 posR;
		D3DXVECTOR3 vecU;
		D3DXVECTOR3 posOld;
		D3DXMATRIX mtxProjection;
		D3DXMATRIX mtxView;
		D3DXVECTOR3 rot;
		float fDistance;
	}Camera;
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
private:
	Camera g_camera;
};

#endif