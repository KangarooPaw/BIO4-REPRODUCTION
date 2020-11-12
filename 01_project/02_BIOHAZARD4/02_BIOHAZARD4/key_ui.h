#ifndef _KEY_UI_H_
#define _KEY_UI_H_

#define TEXTURE_KEY	 "data/TEXTURE/key.png"

class CKeyUi
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_GLOW,
		TYPE_NOGLOW,
		TYPE_MAX
	}TYPE;

	CKeyUi();
	~CKeyUi();
	static CKeyUi * Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetKey(TYPE type);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;
	int                       m_nPatternAnim;
};

#endif // !_KEY_UI_H_