#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "model.h"

class CPlayer :public CModel
{
public:
	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);
	~CPlayer();

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size) {
		m_pos = pos; m_rot = rot; m_size = size;
		SetModel(pos,rot);
		SetObjType(OBJTYPE_PLAYER);
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
};

#endif