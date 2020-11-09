//-----------------------------------------------------------
// 木箱破壊エフェクト
// boxeffect.cpp
// Author : 林川紗梨夏
//-----------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "boxeffect.h"
#include "box.h"

#define SHARD_VALUE 20//木片の量
#define SHARD_SPEED 1.5f//木片の飛び散る速さ
#define SHARD_UP_VALUE 1.5f//木片の上に上がる力
#define FALL_SPEED 0.08f //落下スピード
//-----------------------------------------------------------
//静的メンバ変数宣言
//-----------------------------------------------------------
LPDIRECT3DTEXTURE9 CBoxEffect::m_pTexture = NULL;
//-----------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------
CBoxEffect::CBoxEffect(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = EFFECT_LIFE;
}
//-----------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------
CBoxEffect::~CBoxEffect()
{
}
//-----------------------------------------------------------
// 生成
//-----------------------------------------------------------
CBoxEffect * CBoxEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	// CReticleポインタ
	CBoxEffect *pBoxEffect;

	// メモリ確保
	pBoxEffect = new CBoxEffect(5);
	
	// 初期化
	pBoxEffect->Init(pos, size, rot, col);
	//移動量
	pBoxEffect->m_move = move;

	// ポインタを返す
	return pBoxEffect;
}
//-----------------------------------------------------------
// テクスチャ読み込み
//-----------------------------------------------------------
HRESULT CBoxEffect::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	 //テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wood_shard.png", &m_pTexture);

	return S_OK;
}
//-----------------------------------------------------------
// テクスチャ破棄
//-----------------------------------------------------------
void CBoxEffect::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		// テクスチャRelease
		m_pTexture->Release();

		// m_pTextureをNULLに
		m_pTexture = NULL;
	}
}
//-----------------------------------------------------------
// 初期化
//-----------------------------------------------------------
HRESULT CBoxEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
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
	CBillboard::Init();

	// 位置座標設定
	SetPosition(m_pos);

	// サイズ設定
	SetSize(size);

	// 向き設定
	SetRotation(m_rot);

	// カラー設定
	SetColor(m_col);

	// テクスチャ受け渡し
	BindTexture(m_pTexture);

	return S_OK;
}
//-----------------------------------------------------------
// 終了
//-----------------------------------------------------------
void CBoxEffect::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}
//-----------------------------------------------------------
// 更新
//-----------------------------------------------------------
void CBoxEffect::Update(void)
{
	// 更新
	CBillboard::Update();

	m_move.y += -FALL_SPEED;
	//位置更新
	m_pos += m_move;
	//ライフ減算
	m_nLife--;

	if (m_nLife < 0)
	{
		Uninit();
		return;
	}

	// カラー設定
	SetColor(m_col);

	// 位置座標設定
	SetPosition(m_pos);

}
//-----------------------------------------------------------
// 描画
//-----------------------------------------------------------
void CBoxEffect::Draw(void)
{
	// 描画
	CBillboard::Draw();
}

void CBoxEffect::BreakBox(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	for (int nCount = 0; nCount < SHARD_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		CBoxEffect::Create(D3DXVECTOR3(pos.x,pos.y + (BOX_SIZE / 2),pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*SHARD_SPEED, sinf(D3DXToRadian(fRandRot))*-(SHARD_SPEED + SHARD_UP_VALUE), sinf(D3DXToRadian(fRandRot))*SHARD_SPEED), D3DXVECTOR3(EFFECT_SIZE_X,EFFECT_SIZE_Y,0.0f), D3DXVECTOR3(fRandRot, fRandRotY, fRandRotZ), D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}
