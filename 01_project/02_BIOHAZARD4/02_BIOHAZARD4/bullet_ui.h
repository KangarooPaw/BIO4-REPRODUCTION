//=============================================================================
//
// �e���\������ [bullet_ui.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _BULLET_UI_H_
#define _BULLET_UI_H_
#include "number.h"
#define MAX_DIGITS 10 //�ő包��
#define POINTS_SIZE_WIDTH 20.0f
#define POINTS_SIZE_HEIGHT 30.0f

#define DISPLAY_TIME 100 //�\������
//2D�I�u�W�F�N�g�N���X
class CBulletUi : public CScene
{
public:

	CBulletUi(int nPriority = 8);
	~CBulletUi();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletUi * Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight, int points);
	void SetbulletUi(float nPoints);
	void AddPoints(float nValue);

private:
	D3DXVECTOR3                        m_pos;
	CNumber                           *m_apNumber[MAX_DIGITS];//�i���o�[�i�ő包�����j
	float                                m_nPoints; //�X�R�A�̐��l
	float                                m_fFloatX;
	float                                m_fFloatY;
	int                                  m_digits;//��������
	int                                  m_nTimeCount;//�\������
};
#endif // !_SCORE_H_
