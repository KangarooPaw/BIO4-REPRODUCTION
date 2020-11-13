//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : 
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MATERIAL (50)

//=============================================================================
// �O���錾
//=============================================================================
class CModel;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CMap :public CScene
{
public:
	CMap(int nPriority = CScene::OBJTYPE_NONE);//�R���X�g���N�^
	~CMap();//�f�X�g���N�^

	static CMap *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);//��������
	static HRESULT Load(void);//�e�N�X�`���̓ǂݍ���
	static void Unload(void);//�e�N�X�`���̔j��
	static HRESULT LoadTexture(void);
	HRESULT Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��

					//�����ݒ�
	void SetMap(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	//�󂯓n������
	D3DXVECTOR3 GetPos(void) { return m_pos; }//�ꏊ
	D3DXVECTOR3 GetRot(void) { return m_rot; }//�p�x
	LPD3DXMESH GetMapMesh(void) { return m_pMesh; }
private:
	static LPD3DXMESH m_pMesh;	  // ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat; // �}�e���A�����̃|�C���^
	static DWORD m_nNumMat;		  // �}�e���A�����̐�
	static D3DXMATRIX m_mtxWorld;	  // �s��v�Z�p
	static char* m_apFileName;	  // �t�@�C���̖��O
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_MATERIAL];

	D3DXVECTOR3 m_pos;					// �ꏊ
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXVECTOR3 m_size;					// �傫��
	CModel *m_pModel; // ���f���N���X�̃|�C���^
};

#endif