#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "scene3d.h"

//****************************************************************************************************
//�}�N����`
//****************************************************************************************************
#define MAX_TYPE_POLYGON 2

class CPolygon:public CScene3d
{
public:
	CPolygon(int nPriority = CScene::OBJTYPE_NONE);			//�C���N�������g
	~CPolygon();		//�f�N�������g

	static CPolygon*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int type);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TYPE_POLYGON];
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
	D3DXVECTOR3 m_pos;	
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;
	int m_nType;
};

#endif