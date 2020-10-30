#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "model_hierarchy.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ENEMY_PARTS (13) // �v���C���[�̃��f���̃p�[�c�̍ő吔
#define MOTION_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/motion.txt") // ���[�V�����̃e�L�X�g
#define LOAD_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/enemy.txt") // �e���f���p�[�c�̏����l

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy :public CModelhierarchy
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
		SetModel(pos, rot, size);
		SetObjType(OBJTYPE_ENEMY);
	}

private:
	typedef struct {
		char* pFileName;	   // �ǂݍ��݃t�@�C����
		int nIndex;			   // ���f���i���o�[
		int nParents;		   // ���f���̐e�q�֌W
		D3DXVECTOR3 pos;	   // �ʒu
		D3DXVECTOR3 rot;	   // �p�x
	}MODELPARENT;

	static LPD3DXMESH m_pMesh[MAX_ENEMY_PARTS];
	static LPD3DXBUFFER m_pBuffMat[MAX_ENEMY_PARTS];
	static DWORD m_nNumMat[MAX_ENEMY_PARTS];
	static MODELPARENT m_modelParent[MAX_ENEMY_PARTS];
	D3DXVECTOR3 m_pos;			//�ꏊ
	D3DXVECTOR3 m_rot;			//�p�x
	D3DXVECTOR3 m_size;			//�傫��
	CMotion *m_pMotion;
	static bool m_bChase;
};

#endif