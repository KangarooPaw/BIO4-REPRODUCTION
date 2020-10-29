//=============================================================================
//
// ���f���̊K�w�\���̏��� [model_hierarchy.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _MODEL_HIERARCHY_H_
#define _MODEL_HIERARCHY_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene3d.h"

//=============================================================================
// ���f���q�G�����L�[�N���X
//=============================================================================
class CModelhierarchy :public CScene3d
{
public:
	CModelhierarchy(int nPriority = CScene::OBJTYPE_NONE);
	~CModelhierarchy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat, int nldxModelParent);
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void SetModelParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCount);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	typedef struct
	{
		LPD3DXMESH m_pMeshParts;	  // ���b�V�����̃|�C���^
		LPD3DXBUFFER m_pBuffMatParts; // �}�e���A�����̃|�C���^
		DWORD m_nNumMatParts;		  // �}�e���A�����̐�
		D3DXMATRIX m_mtxWorldParts;	  // �s��v�Z�p
		int m_nldxModelParent;		  // �e���f���̃C���f�b�N�X
	}MODEL;

	typedef struct {
		D3DXVECTOR3 m_pos;	   // �ʒu
		D3DXVECTOR3 m_rot;	   // �p�x
	}MODELPARENT;

	D3DXVECTOR3 m_pos;	   // ���W
	D3DXVECTOR3 m_rot;	   // ��]
	D3DXVECTOR3 m_size;	   // �T�C�Y
	D3DXMATRIX m_mtxWorld; // �s��v�Z�p
	int m_nNumModel;	   // ���f���̐�
	MODEL m_Model[13];	   // ���f���̃p�[�c���Ƃ̏��
	MODELPARENT m_modelParent[13];
};

#endif