#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

#define GAZE_Y (47.0f)

class CCamera
{
public:
	CCamera();
	~CCamera();		//デストラクタ
	void Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	D3DXVECTOR3 GetPosR(void) { return posR; }		//角度の受け取り処理
private:
	D3DXVECTOR3 posV;		//位置
	D3DXVECTOR3 posR;		//角度
	D3DXVECTOR3 vecU;
	D3DXMATRIX	mtxProjection;
	D3DXMATRIX	mtxView;
	float m_Distance;		//距離
	float m_lTheta;			//シータ
	float m_lPhi;			//ファイ
	int m_nCount;			//構えのカウント
};

#endif