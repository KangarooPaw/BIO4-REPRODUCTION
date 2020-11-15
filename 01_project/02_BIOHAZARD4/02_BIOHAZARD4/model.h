//=============================================================================
//
// ���f���̊K�w�\���̏��� [model.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

class CModel
{
public:
	CModel();
	~CModel();

	static CModel*Create();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat, 
		int nldxModelParent);
	void BindTexture(LPDIRECT3DTEXTURE9 Texture, int nCount);
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	void SetParent(CModel *cmodel);
	void SetWorldMatrix(D3DXMATRIX mtxWorld);
	void SetBoolFog(bool bFog);
	void SetBoolShow(bool bShow);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
private:
	LPD3DXMESH m_pMesh;		 // ���b�V�����̃|�C���^
	LPD3DXBUFFER m_pBuffMat; // �}�e���A�����̃|�C���^
	DWORD m_nNumMat;		 // �}�e���A�����̐�
	D3DXMATRIX m_mtxWorld;	 // �s��v�Z�p
	int m_nldxModelParent;	 // �e���f���̃C���f�b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture[50]; // �e�N�X�`���̏��

	D3DXVECTOR3 m_pos;		 // �ʒu
	D3DXVECTOR3 m_rot;		 // �p�x
	D3DXVECTOR3 m_size;	   // �T�C�Y
	bool        m_bIsFog;//�t�H�O�`�悷�邩
	bool		m_bShow; // ���f����\�����邩
	CModel *m_pParent;
};

#endif