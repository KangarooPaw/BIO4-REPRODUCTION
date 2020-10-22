#ifndef _MODEL_H_
#define _MODEL_H_

#include "scene3d.h"

class CModel:public CScene3d
{
public:
	CModel();
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
private:
	static LPD3DXMESH m_pMesh;
	static LPD3DXBUFFER m_pBuffMat;
	static DWORD m_nNumMat;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
};

#endif