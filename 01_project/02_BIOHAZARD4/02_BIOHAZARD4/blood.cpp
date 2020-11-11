//-----------------------------------------------------------
// 血しぶきエフェクト
// blood.cpp
// Author : 林川紗梨夏
//-----------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "particle.h"
#include "blood.h"

#define BLOOD_VALUE 50//血の量
#define BLOOD_SPEED 2.5f//血の飛び散る速さ
#define BLOOD_UP_VALUE 5.5f//血の上に上がる力
#define BLOOD_FALL_SPEED 0.5f //落下スピード

//-----------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------
CBlood::CBlood(int nPriority) : CParticle(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_nPatternAnim = 0;
	m_nCounterAnim = 0;
	m_nLife = BLOOD_LIFE;
}
//-----------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------
CBlood::~CBlood()
{
}
//-----------------------------------------------------------
// 生成
//-----------------------------------------------------------
CBlood * CBlood::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TYPE type)
{
	// CReticleポインタ
	CBlood *pBoxEffect;

	// メモリ確保
	pBoxEffect = new CBlood(5);
	//タイプ
	pBoxEffect->m_type = type;
	// 初期化
	pBoxEffect->Init(pos, size, rot, col);
	//移動量
	pBoxEffect->m_move = move;

	// ポインタを返す
	return pBoxEffect;
}

//-----------------------------------------------------------
// 初期化
//-----------------------------------------------------------
HRESULT CBlood::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	// 代入
	// 位置座標
	m_pos = pos;
	// サイズ
	m_size = size;
	// 向き
	m_rot = rot;
	// カラー
	m_col = col;

	// 初期化
	CParticle::Init(pos, size, rot, col, TEX_TYPE_BLOOD);

	return S_OK;
}
//-----------------------------------------------------------
// 終了
//-----------------------------------------------------------
void CBlood::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//-----------------------------------------------------------
// 更新
//-----------------------------------------------------------
void CBlood::Update(void)
{
	// 更新
	CParticle::Update();

	m_move.y += -BLOOD_FALL_SPEED;


	//位置更新
	m_pos += m_move;
	//ライフ減算
	m_nLife--;

	// カラー設定
	SetColor(m_col);

	// 位置座標設定
	SetPosition(m_pos);

	//ライフ０で消す
	if (m_nLife < 0)
	{
		Uninit();
		return;
	}

}
//-----------------------------------------------------------
// 描画
//-----------------------------------------------------------
void CBlood::Draw(void)
{
	// 描画
	CParticle::Draw();
}
//-----------------------------------------------------------
// 血しぶき生成
//-----------------------------------------------------------
void CBlood::BloodSplash(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	for (int nCount = 0; nCount < BLOOD_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360 + -360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		float fRandSize = float(rand() % SPLACH_BLOOD_SIZE_X);
		float fRandSpeed = float(rand() % int(BLOOD_SPEED * 10));//十倍にしてランダムにする
		//元の値の倍率に戻す
		fRandSpeed = fRandSpeed / 10;
		CBlood::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*fRandSpeed, sinf(D3DXToRadian(fRandRotY))*-(fRandSpeed + BLOOD_UP_VALUE), cosf(D3DXToRadian(fRandRotZ))*fRandSpeed), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_BLOOD);
	}
	for (int nCount = 0; nCount < BLOOD_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360 + -360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		float fRandSize = float(rand() % SPLACH_BLOOD_SIZE_X);
		float fRandSpeed = float(rand() % int(BLOOD_SPEED * 10));//十倍にしてランダムにする
																 //元の値の倍率に戻す
		fRandSpeed = (fRandSpeed / 10) / 2;
		CBlood::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*fRandSpeed, sinf(D3DXToRadian(fRandRotY))*-(fRandSpeed + BLOOD_UP_VALUE), cosf(D3DXToRadian(fRandRotZ))*fRandSpeed), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_BLOOD);
	}
}
