#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene2d.h"

class CPlayer :public CScene2D
{
public:
	CPlayer(int nPriority = 9);
	~CPlayer();
	
	static CPlayer*Create(D3DXVECTOR3 pos,D3DXVECTOR3 size);
	
	static HRESULT Load(void);
	static void Unload(void);
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3				m_pos;					// ƒ|ƒŠƒSƒ“‚ÌˆÊ’u
	D3DXVECTOR3				m_size;
};
#endif // !_PLAYER_H_
