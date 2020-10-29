#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "model.h"

class CEnemy :public CModel
{
public:
	CEnemy(int nPriority = CScene::OBJTYPE_ENEMY);//�R���X�g���N�^
	~CEnemy();//�f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//��������
	static HRESULT Load(void);//�e�N�X�`���̓ǂݍ���
	static void Unload(void);//�e�N�X�`���̔j��

	HRESULT Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��

	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size) {
		m_pos = pos; m_rot = rot; m_size = size;
		SetModel(pos, rot);
		SetObjType(OBJTYPE_ENEMY);
	}

	//�󂯎�菈��
	D3DXVECTOR3 GetPos(void) { return m_pos; }	//�ꏊ
	D3DXVECTOR3 GetSize(void) { return m_size; }//�傫��
private:
	static LPD3DXMESH m_pMesh;
	static LPD3DXBUFFER m_pBuffMat;
	static DWORD m_nNumMat;
	D3DXVECTOR3 m_pos;		//�ꏊ
	D3DXVECTOR3 m_rot;		//�p�x
	D3DXVECTOR3 m_size;		//�傫��
	static bool m_bChase;	//�v���C���[��ǂ�������g���K�[
	float m_fPlayerDirection;//�v���C���[�̕���
};

#endif