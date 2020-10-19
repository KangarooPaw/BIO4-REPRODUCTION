#ifndef _DEBUG_H_
#define _DEBUG_H_

class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);
	static void Print(char *fmt, ...);
	static void Draw(void);
private:
	static LPD3DXFONT m_pFont;
	static char m_astr[1024];
};
#endif // !_DEBUG_H_
