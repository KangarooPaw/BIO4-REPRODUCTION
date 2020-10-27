#ifndef _LIGHT_H_
#define _LIGHT_H_

class CLight
{
public:
	CLight();
	~CLight();
	void Init(void);
	void Uninit(void);
private:
	D3DLIGHT9 m_light;
};


#endif