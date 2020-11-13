//=============================================================================
//
// �����蔻��̏��� [collision.h]
// Author:�ɓ��z��
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"

class CCollision
{
public:
	static bool RectangleCollision(D3DXVECTOR3 pPos1, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2);
	static bool SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2);
private:

};
#endif
