#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "model_hierarchy.h"

#define MAX_PLAYER_PARTS (13)

class CPlayer :public CModelhierarchy
{
public:
	typedef struct {
		char* pFileName;	   //�ǂݍ��݃t�@�C����
		int modelparentIndex;  //���f���̐e�q�֌W
		int nIndex;
		int nParents;		   // ���f���i���o�[
		D3DXVECTOR3 pos;	   // �ʒu
		D3DXVECTOR3 posOrigin; // �n�܂�̈ʒu
		D3DXVECTOR3 rot;	   // �p�x
	}MODELPARENT;

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
	static LPD3DXMESH m_pMesh[MAX_PLAYER_PARTS];
	static LPD3DXBUFFER m_pBuffMat[MAX_PLAYER_PARTS];
	static DWORD m_nNumMat[MAX_PLAYER_PARTS];
	D3DXVECTOR3 m_pos;			//�ꏊ
	D3DXVECTOR3 m_rot;			//�p�x
	D3DXVECTOR3 m_size;			//�傫��
	static MODELPARENT m_modelParent[MAX_PLAYER_PARTS];
};

#endif