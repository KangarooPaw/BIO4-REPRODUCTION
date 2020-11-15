//-----------------------------------------------------------
// �����Ԃ��G�t�F�N�g
// blood.h
// Author : �ѐ�ї���
//-----------------------------------------------------------
#ifndef _BLOOD_H_
#define _BLOOD_H_
//----------------------------------------------------
// �}�N����`
//----------------------------------------------------
#define SPLACH_BLOOD_SIZE_X 5
#define SPLACH_BLOOD_SIZE_Y 5
#define BLOOD_LIFE 50


#include "billboard.h"
#include "particle.h"

class CBlood : public CParticle
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BLOOD,
		TYPE_MAX,
	}TYPE;
	CBlood(int nPriority = 5);
	~CBlood();
	static CBlood *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void BloodSplash(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col);
private:
	D3DXVECTOR3 m_pos;								// �ʒu���W
	D3DXVECTOR3 m_move;                             //�ړ���
	D3DXVECTOR3 m_rot;								// ����
	D3DXVECTOR3 m_size;								// �T�C�Y
	TYPE        m_type;                             //�^�C�v
	int         m_nPatternAnim; //�A�j���[�V�����J�E���^
	int         m_nCounterAnim;//�J�E���^
	D3DXCOLOR m_col;								// �J���[
	int       m_nLife; //���C�t
};
#endif