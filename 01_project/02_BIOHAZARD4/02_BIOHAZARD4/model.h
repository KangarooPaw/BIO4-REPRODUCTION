#ifndef _MODEL_H_
#define _MODEL_H_

#include "scene3d.h"

class CModel :public CScene3d
{
public:
	CModel(int nPriority = CScene::OBJTYPE_PLAYER);
	~CModel();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat);
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

private:
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_nNumMat;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
};

#endif