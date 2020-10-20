#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2d.h"

class CPlayer :public CScene2D
{
public:
	CPlayer(int nPriority = 9);
	~CPlayer();
	
	static CPlayer*Create(float nPosX, float nPosY);
	
	static HRESULT Load(void);
	static void Unload(void);
	
	HRESULT Init(float nPosX, float nPosY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif // !_PLAYER_H_
