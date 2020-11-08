//=============================================================================
//
// ���C������ [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION 0x0800
#define _CRT_SECURE_NO_WARNINGS 

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "windows.h"
#include "d3dx9.h"
#include <dinput.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CManager;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"OBJECT"	// �E�C���h�E�̃L���v�V������

#define SCREEN_WIDTH	(1280)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

#define PRIORITY		(10)
#define NUM_VERTEX		(4)
#define NUM_POLYGON		(2)

#define MAX_POLYGON		(2048)
#define MAX_NUMBER		(4)

#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//�|���S���T�C�Y
#define PLAYER_WIDTH	(50)
#define PLAYER_HEIGHT	(50)
#define BULLET_WIDHT	(25)
#define BULLET_HEIGHT	(25)

//�e�N�X�`��
#define TEXTURE_PLAYER			"data/TEXTURE/player.png"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

typedef struct {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_3D;

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
CManager *GetManager(void);

#endif