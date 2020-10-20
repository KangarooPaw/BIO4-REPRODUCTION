#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "scene3d.h"

//----------------------------------------
//�}�N����`
//----------------------------------------
#define MAX_TYPE_POLYGON 2

class CPolygon:public CScene3d
{
public:

	CPolygon();			//�C���N�������g
	~CPolygon();		//�f�N�������g
	void Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TYPE_POLYGON] = {};
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;

};

#endif