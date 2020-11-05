//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PLAYER_PARTS (13) // �v���C���[�̃��f���̃p�[�c�̍ő吔
#define MAX_MATERIAL (50)
#define MOTION_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/motion.txt") // ���[�V�����̃e�L�X�g
#define LOAD_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/player.txt") // �e���f���p�[�c�̏����l
#define MAX_BULLET_ROT_X	(15)	//�e�̊p�x(X)�ő�l
#define MAX_BULLET_ROT_Y	(20)	//�e�̊p�x(Y)�ő�l
#define MIN_BULLET_ROT_X	(-15)	//�e�̊p�x(X)�ŏ��l
#define MIN_BULLET_ROT_Y	(-20)	//�e�̊p�x(Y)�ŏ��l

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;
class CModel;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer :public CScene
{
public:
	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);//�R���X�g���N�^
	~CPlayer();//�f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//��������
	static HRESULT Load(void);//���f���̓ǂݍ���
	static void Unload(void);//���f���̔j��
	static HRESULT LoadTexture(void);//�e�N�X�`���̓ǂݍ���

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
	static LPD3DXMESH m_pMesh[MAX_PLAYER_PARTS];	  // ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[MAX_PLAYER_PARTS]; // �}�e���A�����̃|�C���^
	static DWORD m_nNumMat[MAX_PLAYER_PARTS];		  // �}�e���A�����̐�
	static D3DXMATRIX m_mtxWorld[MAX_PLAYER_PARTS];	  // �s��v�Z�p
	static int m_nldxModelParent[MAX_PLAYER_PARTS];	  // �e���f���̃C���f�b�N�X
	static char* m_apFileName[MAX_PLAYER_PARTS];	  // �t�@�C���̖��O
	static char* m_apTextureFileName[MAX_PLAYER_PARTS]; //�e�N�X�`���̃t�@�C���̖��O
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PLAYER_PARTS][MAX_MATERIAL];

	D3DXVECTOR3 m_pos;					// �ꏊ
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXVECTOR3 m_size;					// �傫��

	D3DXVECTOR3 m_bulletRot;			// �e�̊p�x
	int m_bulletRotX;					// �e�̊p�x(X)�ύX���̃J�E���g
	int m_bulletRotY;					// �e�̊p�x(Y)�ύX���̃J�E���g

	CMotion *m_pMotion;					// ���[�V�����N���X�̃|�C���^
	CModel *m_pModel[MAX_PLAYER_PARTS]; // ���f���N���X�̃|�C���^

	int m_nMotionCnt;					// ���[�V�����̃J�E���g
	int m_nTurnCnt;						// �^�[���̃J�E���g
	bool m_bMotion;						// ���[�V�����̔���
	bool m_bTurn;						// �^�[���̔���
};

#endif