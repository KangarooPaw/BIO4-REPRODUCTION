#ifndef _FADE_H_
#define _FADE_H_

#include "renderer.h"
#include "manager.h"
#include "mode.h"
#include "scene2d.h"

class CFade :public CScene2D
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT
	}FADE;

	CFade(int nPriority);							//�R���X�g���N�^
	~CFade();										//�f�X�g���N�^
	HRESULT Init(void);								//����������
	void Uninit(void);								//�I������	
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	void SetFade(CManager::MODE mode);
	void FadeIn(void);
	void FadeOut(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �|���S���̈ʒu
	D3DXCOLOR				m_color;				//�F
	int						m_PolygonWidth;
	int						m_PolygonHeight;
	float					m_TexPos;
	static CManager::MODE	m_mode;
	static FADE				m_fade;
};
#endif // !_FADE_H_
