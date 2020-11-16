//****************************************************************************************************
// 木箱破壊エフェクト
// boxeffect.cpp
// Author : 林川紗梨夏
//****************************************************************************************************

//****************************************************************************************************
//インクルードファイル
//****************************************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "boxeffect.h"
#include "box.h"
#include "circleparticle.h"

//****************************************************************************************************
//マクロ定義
//****************************************************************************************************
#define SHARD_VALUE 20				//木片の量
#define SHARD_SPEED 0.5f			//木片の飛び散る速さ
#define SHARD_UP_VALUE 1.5f		//木片の上に上がる力
#define SMOKE_ANIM_PATTERN 25	//煙のアニメーションパターン
#define SMOKE_ANIM_COUNT 1		//このフレーム毎で更新
#define SMOKE_SIZE 60.0f				//煙サイズ
#define FALL_SPEED 0.08f				//落下スピード

//****************************************************************************************************
//静的メンバ変数宣言
//****************************************************************************************************
LPDIRECT3DTEXTURE9 CBoxEffect::m_pTexture[TYPE_MAX] = {};

//****************************************************************************************************
//コンストラクタ
//****************************************************************************************************
CBoxEffect::CBoxEffect(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_nPatternAnim = 0;
	m_nCounterAnim = 0;
	m_nLife = EFFECT_LIFE;
}

//****************************************************************************************************
//デストラクタ
//****************************************************************************************************
CBoxEffect::~CBoxEffect()
{
}

//****************************************************************************************************
//生成
//****************************************************************************************************
CBoxEffect * CBoxEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TYPE type)
{
	//CReticleポインタ
	CBoxEffect *pBoxEffect;

	//メモリ確保
	pBoxEffect = new CBoxEffect(OBJTYPE_BOX);

	//タイプ
	pBoxEffect->m_type = type;

	//初期化
	pBoxEffect->Init(pos, size, rot, col);

	//移動量
	pBoxEffect->m_move = move;

	//ポインタを返す
	return pBoxEffect;
}

//****************************************************************************************************
// テクスチャ読み込み
//****************************************************************************************************
HRESULT CBoxEffect::Load(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/wood_shard.png", &m_pTexture[TYPE_SHARD]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/smoke03.png", &m_pTexture[TYPE_SMOKE]);

	return S_OK;
}
//****************************************************************************************************
//テクスチャ破棄
//****************************************************************************************************
void CBoxEffect::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			//テクスチャRelease
			m_pTexture[nCount]->Release();

			//m_pTextureをNULLに
			m_pTexture[nCount] = NULL;
		}
	}
}
//****************************************************************************************************
//初期化処理
//****************************************************************************************************
HRESULT CBoxEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	//代入
	//位置座標
	m_pos = pos;
	//サイズ
	m_size = size;
	//向き
	m_rot = rot;
	//カラー
	m_col = col;

	//初期化
	CBillboard::Init();

	//位置座標設定
	SetPosition(m_pos);

	//サイズ設定
	SetSize(size);

	//向き設定
	SetRotation(m_rot);

	//カラー設定
	SetColor(m_col);

	//煙
	if (m_type == TYPE_SMOKE)
	{
		//テクスチャ座標のセット
		SetTexture(
			m_nPatternAnim * 0.04f,
			0.0f,
			m_nPatternAnim * 0.04f + 0.04f,
			1.0f);
	}

	//テクスチャ受け渡し
	BindTexture(m_pTexture[m_type]);

	return S_OK;
}

//****************************************************************************************************
//終了処理
//****************************************************************************************************
void CBoxEffect::Uninit(void)
{
	//終了
	CBillboard::Uninit();
}
//****************************************************************************************************
//更新処理
//****************************************************************************************************
void CBoxEffect::Update(void)
{
	//ビルボード更新
	CBillboard::Update();

	if (m_type == TYPE_SHARD)
	{
		m_move.y += -FALL_SPEED;
	}

	//位置更新
	m_pos += m_move;
	//ライフ減算
	m_nLife--;

	//カラー設定
	SetColor(m_col);

	//位置座標設定
	SetPosition(m_pos);

	//煙のテクスチャアニメーション更新
	if (m_type == TYPE_SMOKE)
	{
		m_nCounterAnim++;
		if (m_nCounterAnim > SMOKE_ANIM_COUNT)
		{
			m_nCounterAnim = 0;
			m_nPatternAnim++;
		}

		if (m_nPatternAnim >= SMOKE_ANIM_PATTERN)
		{
			CCircleParticle::CircleCreate(m_pos, D3DXVECTOR3(PARTICLE_CIRCLE_SIZE_X, PARTICLE_CIRCLE_SIZE_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_CIRCLE, 7.5f);
			Uninit();
			return;
		}

		//テクスチャ座標のセット
		SetTexture(
			m_nPatternAnim * 0.04f,
			0.0f,
			m_nPatternAnim * 0.04f + 0.04f,
			1.0f);

	}

	//ライフ０で消す
	if (m_nLife < 0)
	{
		Uninit();
		return;
	}

}
//****************************************************************************************************
//描画
//****************************************************************************************************
void CBoxEffect::Draw(void)
{
	// 描画
	CBillboard::Draw();
}

void CBoxEffect::BreakBox(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{

	CBoxEffect::Create(D3DXVECTOR3(pos.x, pos.y + (BOX_SIZE / 2), pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SMOKE_SIZE, SMOKE_SIZE, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_SMOKE);
	for (int nCount = 0; nCount < SHARD_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		CBoxEffect::Create(D3DXVECTOR3(pos.x, pos.y + (BOX_SIZE / 2), pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*SHARD_SPEED, sinf(D3DXToRadian(fRandRotY))*-(SHARD_SPEED + SHARD_UP_VALUE), cosf(D3DXToRadian(fRandRotZ))*SHARD_SPEED), D3DXVECTOR3(EFFECT_SIZE_X, EFFECT_SIZE_Y, 0.0f), D3DXVECTOR3(fRandRot, fRandRotY, fRandRotZ), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_SHARD);
	}
}
