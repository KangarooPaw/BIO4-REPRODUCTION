//=============================================================================
//
// �X�R�A���� [life.h]
// Author : 
//
//=============================================================================
#ifndef _KEY_H_
#define _KEY_H_
#include "key_ui.h"
#define MAX_KEY 4 //�ő包��
#define PLAYER_LIFE 1 //�v���C���[�̃��C�t
//2D�I�u�W�F�N�g�N���X
class CKey : public CScene
{
public:

	CKey(int nPriority = 8);
	~CKey();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CKey * Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight);
	void SetKeyUi(int nLife);

private:
	CKeyUi                           *m_apKeyUi[MAX_KEY];//���i�ő包�����j
	D3DXVECTOR3                        m_pos;//�ʒu
	int                                m_nKey; //�X�R�A�̐��l
	float                              m_fSizeWidth;//��
	float                              m_fSizeHeight;//����
};
#endif // !_LIFE_H_
