#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "model.h"

class CPlayer :public CModel
{
public:
	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);//�R���X�g���N�^
	~CPlayer();//�f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//��������
	static HRESULT Load(void);//�e�N�X�`���̓ǂݍ���
	static void Unload(void);//�e�N�X�`���̔j��

	HRESULT Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	//�����ݒ�
	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	//�󂯓n������
	D3DXVECTOR3 GetPos(void) { return m_pos; }//�ꏊ
	D3DXVECTOR3 GetRot(void) { return m_rot; }//�p�x
private:
	static LPD3DXMESH m_pMesh;
	static LPD3DXBUFFER m_pBuffMat;
	static DWORD m_nNumMat;
	D3DXVECTOR3 m_pos;			//�ꏊ
	D3DXVECTOR3 m_rot;			//�p�x
	D3DXVECTOR3 m_size;			//�傫��
};

#endif