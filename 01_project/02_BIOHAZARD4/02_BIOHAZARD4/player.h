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
#define MAX_PLAYER_PARTS (15) // �v���C���[�̃��f���̃p�[�c�̍ő吔
#define MAX_MATERIAL (50)
#define MOTION_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/motion.txt") // ���[�V�����̃e�L�X�g
#define LOAD_PLAYER_TEXT ("data/MODEL/PLAYER/MOTION/player.txt") // �e���f���p�[�c�̏����l

#define MAX_BULLET_ROT_X	(15)	//�e�̊p�x(X)�ő�l
#define MAX_BULLET_ROT_Y	(20)	//�e�̊p�x(Y)�ő�l
#define MIN_BULLET_ROT_X	(-15)	//�e�̊p�x(X)�ŏ��l
#define MIN_BULLET_ROT_Y	(-20)	//�e�̊p�x(Y)�ŏ��l

#define MAX_MAGAZINE_BULLET	(15)	//�ő呕�e��

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;
class CModel;
class CReticle;
class CEnemy;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer :public CScene
{
public:
	typedef enum {
		MOTION_IDLE = 0,	 // �ҋ@���[�V����
		MOTION_RUN,			 // �������[�V����
		MOTION_HOLDGUN,		 // �e�\�����[�V����
		MOTION_SHOT,		 // �ˌ����[�V����
		MOTION_HOLDKNIFE,	 // �i�C�t�\�����[�V����
		MOTION_SLASH,		 // �i�C�t��U�郂�[�V����
		MOTION_DAMAGE,		 // �_���[�W���󂯂郂�[�V����
		MOTION_BACK,		 // ���ɉ����郂�[�V����
		MOTION_DYINGNEUTRAL, // �m����Ԃ̑ҋ@���[�V����
		MOTION_DYINGRUNNING, // �m����Ԃ̕������[�V����
		MOTION_DEATH,		 // ���ʃ��[�V����
		MOTION_HOLDENEMY,	 // �G�����ރ��[�V����
		MOTION_SPIN,		 // �G���񂷃��[�V����
		MOTION_SPINEND,		 // �񂷂̂��~�߂郂�[�V����
		MOTION_RELOAD,		 // �����[�h���[�V����
		MOTION_MAX
	}MOTIONSTATE;

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
	
	void Keyboard(void);//�L�[�{�[�h�̏���
	void GamePad(void);//�Q�[���p�b�h����
	void spin(void); // �G���񂷏���

	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//�e��ݒ�
	void HitDamage(int nDamage);	//�_���[�W����
	void PickUpItem(void);			//�A�C�e���擾����
	static void DeathFlag(void);	//���S�t���O

	//�󂯓n������
	D3DXVECTOR3 GetPos(void) { return m_pos; }//�ꏊ
	D3DXVECTOR3 GetRot(void) { return m_rot; }//�p�x
	D3DXVECTOR3 GetSize(void) { return m_size; }//�T�C�Y
	bool GetDeath(void) { return m_bDeath; }//���S�t���O
	bool GetMotion(void) { return m_bAllMotion; }
	bool GetHasKeyAll(void) { return m_bHasKeyAll; }
private:
	bool CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2);

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
	D3DXVECTOR3 m_Getpos;				// �󂯎�����ꏊ
	D3DXVECTOR3 m_Getrot;				// �󂯎�����p�x
	D3DXVECTOR3 m_Getsize;				// �󂯎�����傫��

	D3DXVECTOR3 m_bulletRot;			// �e�̊p�x
	int m_bulletRotX;					// �e�̊p�x(X)�ύX���̃J�E���g
	int m_bulletRotY;					// �e�̊p�x(Y)�ύX���̃J�E���g

	int m_nMagazineBullet;				//�}�K�W���̑��e��
	int m_nHaveBullet;					//�����e��
	int m_nKey;//��������

	bool m_bAllMotion;					//�S���[�V�����̔���

	int m_nKnifeMotionCnt;				// �i�C�t���[�V�����̃J�E���g	
	bool m_bKnifeMotion;				// �i�C�t���[�V�����̔���

	int m_nReloadMotionCnt;				//�����[�h���[�V�����̃J�E���g
	bool m_bReloadMotion;				//�����[�h���[�V�����̔���

	int m_nDamageMotionCnt;				// �_���[�W���[�V�����̃J�E���g
	bool m_bDamageMotion;				// �_���[�W���[�V�����̔���

	int m_nDeathMotionCnt;				//���S���[�V�����̃J�E���g
	bool m_bDeathMotion;				//���S���[�V�����̔���
	static bool m_bDeath;				//���S�t���O

	int m_nTurnCnt;						// �^�[���̃J�E���g
	bool m_bTurn;						// �^�[���̔���

	bool m_bReticle;					// ���e�B�N���̐�������

	static bool m_bHasKeyAll;				// ����S�Ď����Ă��邩�̔���
	int m_nSpinCnt;						//�X�s���̃J�E���g
	bool m_bspin;						// �G����]�����锻��
	
	CEnemy *m_pEnemy;					// �G�N���X�̃|�C���^
	CMotion *m_pMotion;					// ���[�V�����N���X�̃|�C���^
	CModel *m_pModel[MAX_PLAYER_PARTS]; // ���f���N���X�̃|�C���^

};

#endif