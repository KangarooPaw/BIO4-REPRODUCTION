#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "scene.h"

class CScene3d :public CScene
{
public:
	CScene3d(int nPriority);//�C���N�������g
	~CScene3d();//�f�N�������g
	static CScene3d *Create(float nPosX, float nPosY);//��������
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);		//�`�揈��

	//�e��ݒ�
	void SetPosition(D3DXVECTOR3 pos);		//�ʒu
	void SetRotation(D3DXVECTOR3 rot);		//�p�x
	void SetSize(D3DXVECTOR3 size);			//�T�C�Y	
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//�e�N�X�`��


private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
	int m_nType;
};
#endif //_SCENE3D_H_