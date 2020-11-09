//-----------------------------------------------------------
// Paricle
// paricle.h
// Author : �ǌ��@�i
//-----------------------------------------------------------
#ifndef _PERTICLE_H_
#define _PERTICLE_H_
//----------------------------------------------------
// �}�N����`
//----------------------------------------------------
#define EXPLOSION_SIZE_X 10					// �����̃T�C�YX
#define EXPLOSION_SIZE_Y 10					// �����̃T�C�YY
#define SPARK_SIZE_X 5.0f					// �ΉԂ̃T�C�YX
#define SPARK_SIZE_Y 50.0f					// �ΉԂ̃T�C�YY
#define SMOKE_SIZE_X 10						// ���̃T�C�YX
#define SMOKE_SIZE_Y 10						// �����̃T�C�YY
#define BLOOD_SIZE_X 15						// ���̃T�C�YX
#define BLOOD_SIZE_Y 10						// ���̃T�C�YY
#define MAZLE_FLASH_SIZE_X 5				// �}�Y���t���b�V���̃T�C�YX
#define MAZLE_FLASH_SIZE_Y 5				// �}�Y���t���b�V���̃T�C�YY
#define PARTICLE_HIT_SIZE_X 20				// �q�b�g�p�[�e�B�N���T�C�YX
#define PARTICLE_HIT_SIZE_Y 20				// �q�b�g�p�[�e�B�N���T�C�YY
#define PARTICLE_CIRCLE_SIZE_X 7			// �~�p�[�e�B�N���T�C�YX
#define PARTICLE_CIRCLE_SIZE_Y 200			// �~�p�[�e�B�N���T�C�YY
#define PARTICLE_CIRCLE_COL_MAX 0.5f		// �~�̃J���[�ő�l
#define PARTICLE_CIRCLE_COL_MIN 0.1f		// �~�̃J���[�ŏ��l

#include "billboard.h"

class CParticle : public CBillboard
{
public:

	// �p�[�e�B�N���^�C�v
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

	// �e�N�X�`���^�C�v
	typedef enum
	{
		TEX_TYPE_NONE = 0,
		TEX_TYPE_1,
		TEX_TYPE_2,
		TEX_TYPE_MAX,
	}TEX_TYPE;

	// �J���[���Z�A���Z
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
	D3DXVECTOR3 m_pos;								// �ʒu���W
	D3DXVECTOR3 m_rot;								// ����
	D3DXVECTOR3 m_size;								// �T�C�Y
	D3DXVECTOR3 m_move;								// �ړ���
	D3DXCOLOR m_col;								// �J���[
	TYPE m_Type;									// �^�C�v
	TEX_TYPE m_TexType;								// �e�N�X�`���^�C�v
	COLOR_TYPE m_ColorType;							// �J���[�^�C�v
	float m_fRadian;
	float m_fLength;
	float m_fAngle;
	float m_fScale;									// �g�嗦
	float m_fAddScale;								// �g�嗦���Z
	float m_fAddColor;								// �J���[���Z
	int m_nCount;									// �J�E���g
};
#endif