#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"
//�����_�����O�N���X
class CRenderer
{
public:

	CRenderer();	//�R���X�g���N�^
	~CRenderer();	//�f�X�g���N�^
	HRESULT Init(HWND hWnd, bool bWindow);	//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

#ifdef _DEBUG
	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }
#endif

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
private:

	void DrawFPS(void);

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
	int						m_nCountFPS;			// FPS�J�E���^
#endif
};
#endif // !_RENDERER_H_
