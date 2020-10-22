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
	void SetAnimation(int nPatternAnim);
	void SetAlpha(int alpha);
	void SetRotVertex(float sizeX,float sizeY,float fAngle);
	void SetEnemyTex(float texX1,float texX2,float texY1, float texY2);
	
	D3DXVECTOR3 GetPosition(void);
private:	
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;					// �|���S���̈ʒu
	D3DXVECTOR3				m_size;
	int						m_PolygonWidth;
	int						m_PolygonHeight;
	int 					m_Alpha;
	float					m_angleX, m_angleY;
};

#endif // !_SCENE2D_H_
