#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

#define GAZE_Y		(47.0f)
#define CAMERA_GAZE	(-15)
#define CAMERA_VIEW	(25)
#define MOVE		(15.0f)
#define HOLD_FRAME	(10)
class CCamera
{
public:
	CCamera();
	~CCamera();		//�f�X�g���N�^
	void Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	D3DXVECTOR3 GetPosR(void) { return posR; }		//�p�x�̎󂯎�菈��
private:
	D3DXVECTOR3 posV;		//�ʒu
	D3DXVECTOR3 posR;		//�p�x
	D3DXVECTOR3 vecU;
	D3DXMATRIX	mtxProjection;
	D3DXMATRIX	mtxView;
	float m_Distance;		//����
	float m_lTheta;			//�V�[�^
	float m_lPhi;			//�t�@�C
	int m_nCount;			//�\���̃J�E���g
	bool m_bTurn;			//�^�[������
	int m_nTurnCnt;			//�^�[���̃J�E���g
};

#endif