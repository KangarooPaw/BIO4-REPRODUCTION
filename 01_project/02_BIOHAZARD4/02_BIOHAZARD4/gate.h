//=============================================================================
//
// ���̏��� [gate.h]
// Author : �ǌ��@�i
//
//=============================================================================
#ifndef _GATE_H_
#define _GATE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CModel;

//�}�N����`
#define GATE_SIZE 50.0f
//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CGate :public CScene
{
public:
	CGate(int nPriority = CScene::OBJTYPE_GATE);//�R���X�g���N�^
	~CGate();//�f�X�g���N�^

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_LEFT,// �E
		TYPE_RIGHT,//��
		TYPE_MAX
	}TYPE;
	static CGate *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//��������
	static HRESULT Load(void);//���f���̓ǂݍ���
	static void Unload(void);//���f���̔j��
	static HRESULT LoadTexture(void);//�e�N�X�`���̓ǂݍ���
	HRESULT Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void SetGate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	//�󂯓n������
	D3DXVECTOR3 GetPos(void) { return m_pos; }//�ꏊ
	D3DXVECTOR3 GetRot(void) { return m_rot; }//�p�x
	D3DXVECTOR3 GetSize(void) { return m_size; };//�T�C�Y
	bool GetOpen(void) { return m_bOpen; }
private:
	static LPD3DXMESH m_pMesh[TYPE_MAX];	  // ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX]; // �}�e���A�����̃|�C���^
	static DWORD m_nNumMat[TYPE_MAX];	 // �}�e���A�����̐�
	D3DXMATRIX m_mtxWorld[TYPE_MAX];	     // �s��v�Z�p
	static char* m_apFileName[TYPE_MAX]; // �t�@�C���̖��O
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX][50];

	D3DXVECTOR3 m_pos;					// �ꏊ
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXVECTOR3 m_size;					// �傫��
	CModel *m_pModel[TYPE_MAX]; // ���f���N���X�̃|�C���^
	bool m_bOpen;
	bool m_bmove;
	int m_nCount;						//	�J�E���g
	bool m_bSoundGateOpen;				//�Q�[�g���J����T�E���h���Đ�����Ă��邩�̔���
};

#endif