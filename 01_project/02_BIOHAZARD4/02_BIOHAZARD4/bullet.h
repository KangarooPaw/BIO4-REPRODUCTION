//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene3d.h"

class CBullet :public CScene3d
{
public:
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,	// �v���C���[�̒e
		BULLETTYPE_ENEMY,		// �G�̒e
		BULLETTYPE_MAX
	}BULLETTYPE;

	CBullet(int nPriority = CScene3d::OBJTYPE_BULLET);
	~CBullet();

	static CBullet*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		D3DXVECTOR3 move, int nLife, int nDamage, BULLETTYPE type);

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, 
		int nLife, int nDamage, BULLETTYPE type) {
		m_pos = pos; m_size = size; m_move = move; 
		m_nLife = nLife; m_nDamage = nDamage; m_type = type;
		SetPosition(m_pos); SetSize(m_size);
		SetObjType(OBJTYPE_BULLET);
	}

	BULLETTYPE GetBulletType(void);
	bool CollisionBullet(D3DXVECTOR3 pPos1, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos;	   //���݂̈ʒu
	D3DXVECTOR3 m_size;    //�傫��
	D3DXVECTOR3 m_move;	   //�ړ���
	D3DXVECTOR3 m_Getpos;  // �󂯎�������W
	D3DXVECTOR3 m_Getsize; // �󂯎�����T�C�Y
	BULLETTYPE m_type;	   //���
	int m_nLife;		   //����
	int m_nDamage;		   //�_���[�W
};
#endif