#ifndef _FADE_H_
#define _FADE_H_

#include "renderer.h"
#include "manager.h"

//�O���錾
class CScene2D;

class CFade
{
public:
	typedef enum
	{
		FADE_NONE=0,
		FADE_IN,
		FADE_OUT
	}FADE;

	CFade();										//�R���X�g���N�^
	~CFade();										//�f�X�g���N�^
	static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						//�e�N�X�`���̔j��
	static CFade *Create(float nPosX, float nPosY);	//��������
	HRESULT Init(void);								//����������
	void Uninit(void);								//�I������	
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	static void SetFade(/*CManager::MODE mode*/void);
	void FadeIn(void);
	void FadeOut(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �|���S���̈ʒu
	int						m_PolygonWidth;
	int						m_PolygonHeight;
	CScene2D				*m_pScene2D;
	float					m_TexPos;
	int						m_nFade;
	//static CManager::MODE	m_mode;
	static FADE				m_fade;
};
#endif // !_FADE_H_