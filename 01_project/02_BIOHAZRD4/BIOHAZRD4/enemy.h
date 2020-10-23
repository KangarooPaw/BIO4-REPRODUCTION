#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene3d.h"

class CEnemy :public CScene3d
{
public:
	CEnemy(int nPriority = CScene::OBJTYPE_ENEMY);
	~CEnemy();

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size) {
		m_pos = pos; m_rot = rot; m_size = size;
		SetPosition(pos); SetRotation(rot); SetSize(size);
		SetObjType(OBJTYPE_ENEMY);
	}

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
private:
	static LPD3DXMESH m_pMesh;
	static LPD3DXBUFFER m_pBuffMat;
	static DWORD m_nNumMat;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;
};

#endif