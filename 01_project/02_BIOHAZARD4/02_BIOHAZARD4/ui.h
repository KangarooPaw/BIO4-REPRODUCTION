#ifndef _UI_H_
#define _UI_H_

#include "scene2d.h"

//テクスチャ
#define TEXTURE_TITLE			"data/TEXTURE/gameover.png"
//テクスチャ
#define TEXTURE_TUTORIAL			"data/TEXTURE/gameover.png"
//テクスチャ
#define TEXTURE_GAMEOVER			"data/TEXTURE/gameover.png"
//テクスチャ
#define TEXTURE_RESULT			"data/TEXTURE/gameover.png"

class CUi :public CScene2D
{
public:
	CUi(int nPriority);
	~CUi();

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_TITLE,
		TYPE_TUTORIAL,
		TYPE_GAMEOVER,
		TYPE_RESULT,
		TYPE_MAX
	}TYPE;
	
	static CUi*Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
	D3DXVECTOR3				m_pos;					// ポリゴンの位置
	D3DXVECTOR3				m_size;
	TYPE                    m_type;
};
#endif // !_UI_H_
