//---------------------------------------------------
// Life
// Life.h
// Author:	�ǌ��i
//---------------------------------------------------
#ifndef _LIFE_H_
#define _LIFE_H_
#define LIFE_SIZE_X 25
#define LIFE_SIZE_Y 25
#define MAX_LIFE 100
#define FADE_RATE	0.01f

#include "scene2d.h"

//---------------------------------------------------
//�N���X
//---------------------------------------------------
class CLife : public CScene
{
public:
	//�t�F�[�h
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
	}FADE;
	//�F
	typedef enum
	{
		STATE_NONE = 0,
		STATE_GREEN,
		STATE_YELLOW,
		STATE_RED,
	}STATE;
	CLife(int nPriority = OBJTYPE_UI);
	~CLife();

	static CLife * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float Length);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void LifeDecrement(int nDamage);
	static void LifeIncrement(int nDamage);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`�����
	CScene2D *m_apScene2D[MAX_POLYGON];		//Scene2d���
	CScene2D *m_pScene2D;					//Scene2D���
	D3DXVECTOR3 m_pos;						//�ʒu���
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXCOLOR m_col;						//�J���[
	FADE m_Fade;							//Fade
	STATE m_State;							//State
	float m_fRadian;						//�ʓx
	float m_fLengh;							//���a
	int m_nCnt;								//�J�E���g
	static int m_nDamageCnt;				//�_���[�W���󂯂�J�E���g
	static bool m_bHit;						//�_���[�W���󂯂Ă��锻��
	static bool m_bHerb;					//�n�[�u�g�p����
};
#endif