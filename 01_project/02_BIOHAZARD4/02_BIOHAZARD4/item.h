#pragma once
//=============================================================================
//
// �A�C�e���̏��� [item.h]
// Author : �ѐ�ї���
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CModel;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CItem :public CScene
{
public:
	CItem(int nPriority = CScene::OBJTYPE_ITEM);//�R���X�g���N�^
	~CItem();//�f�X�g���N�^

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_HABU,//�n�[�u
		TYPE_SUPURE,//�X�v���[
		TYPE_AMMO,//�e��
		TYPE_MAX
	}TYPE;
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type);//��������
	static HRESULT Load(void);//���f���̓ǂݍ���
	static void Unload(void);//���f���̔j��
	static HRESULT LoadTexture(void);//�e�N�X�`���̓ǂݍ���
	HRESULT Init(void);//����������
	void Uninit(void);//�I������
	void Update(void);//�X�V����
	void Draw(void);//�`�揈��
	void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	//�󂯓n������
	D3DXVECTOR3 GetPos(void) { return m_pos; }//�ꏊ
	D3DXVECTOR3 GetRot(void) { return m_rot; }//�p�x
private:
	bool CItem::CollisionItem(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2);
	static LPD3DXMESH m_pMesh[TYPE_MAX];	  // ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX]; // �}�e���A�����̃|�C���^
	static DWORD m_nNumMat[TYPE_MAX];	 // �}�e���A�����̐�
	D3DXMATRIX m_mtxWorld;	     // �s��v�Z�p
	static char* m_apFileName[TYPE_MAX]; // �t�@�C���̖��O
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX][50];

	D3DXVECTOR3 m_pos;					// �ꏊ
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXVECTOR3 m_size;					// �傫��
	int         m_type;                 //���
	CModel *m_pModel; // ���f���N���X�̃|�C���^
};

#endif