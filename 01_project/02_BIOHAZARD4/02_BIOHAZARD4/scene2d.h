#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "scene.h"

class CScene2D :public CScene
{
public:
	CScene2D(int nPriority);
	~CScene2D();

	static CScene2D *Create(float nPosX, float nPosY);

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void SetPosition(D3DXVECTOR3 pos);		//�ʒu
	void SetSize(D3DXVECTOR3 size);			//�T�C�Y
	void SetColor(D3DXCOLOR color);
	void SetRotation(D3DXVECTOR3 rot);

	D3DXVECTOR3 GetPosition(void);
	D3DXCOLOR GetColor(void);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �|���S���̈ʒu
	D3DXVECTOR3				m_size;
	D3DXVECTOR3				m_rot;					// ����
	D3DXCOLOR				m_color;
	float					m_fAngle;				//�p�x
	float					m_fLength;				//���a
};

#endif // !_SCENE2D_H_
