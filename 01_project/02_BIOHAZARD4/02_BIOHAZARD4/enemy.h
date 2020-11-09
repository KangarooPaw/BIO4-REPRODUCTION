#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ENEMY_PARTS (13) // �v���C���[�̃��f���̃p�[�c�̍ő吔
#define MAX_MATERIAL (50)
#define MOTION_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/motion.txt") // ���[�V�����̃e�L�X�g
#define LOAD_ENEMY_TEXT ("data/MODEL/ENEMY/MOTION/enemy.txt") // �e���f���p�[�c�̏����l

//=============================================================================
// �O���錾
//=============================================================================
class CMotion;
class CModel;

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy :public CScene
{
public:
	CEnemy(int nPriority = CScene::OBJTYPE_ENEMY);//�R���X�g���N�^
	~CEnemy();//�f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//��������
	static HRESULT Load(void);//���f���̓ǂݍ���
	static void Unload(void);//���f���̔j��
	static HRESULT LoadTexture(void);//�e�N�X�`���̓ǂݍ���

	HRESULT Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void HitBullet(int nDamage);

	static void SetChase(bool bChase);
	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	static LPD3DXMESH m_pMesh[MAX_ENEMY_PARTS];		 // ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[MAX_ENEMY_PARTS]; // �}�e���A�����̃|�C���^
	static DWORD m_nNumMat[MAX_ENEMY_PARTS];		 // �}�e���A�����̐�
	static D3DXMATRIX m_mtxWorld[MAX_ENEMY_PARTS];	 // �s��v�Z�p
	static int m_nldxModelParent[MAX_ENEMY_PARTS];	 // �e���f���̃C���f�b�N�X
	static char* m_apFileName[MAX_ENEMY_PARTS];		 // �t�@�C���̖��O
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ENEMY_PARTS][MAX_MATERIAL];
	static char* m_apTextureFileName[MAX_ENEMY_PARTS];

	D3DXVECTOR3 m_pos;					// �ꏊ
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXVECTOR3 m_size;					// �傫��
	CMotion *m_pMotion;					// ���[�V�����N���X�̃|�C���^
	CModel *m_pModel[MAX_ENEMY_PARTS];	// ���f���N���X�̃|�C���^
	static bool m_bChase;				// �`�F�C�X����
	bool m_bHit;						// �_���[�W���󂯂Ă��锻��
	bool m_bAttack;						// �U������
	int m_nCntAttack;					// �U�����x
	int m_nEnemyLife;					// �G�̗̑�
	int m_nCntFrame;					// �t���[���J�E���g
	int m_nDamageCnt;					// �_���[�W���[�V�����t���[��
};

#endif