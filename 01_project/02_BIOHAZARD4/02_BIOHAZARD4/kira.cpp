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
#include "kira.h"

#define KIRA_VALUE 50//木片の量
#define KIRA_SPEED 2.5f//木片の飛び散る速さ
#define KIRA_UP_VALUE 5.5f//木片の上に上がる力
#define KIRA_FALL_SPEED 0.5f //落下スピード
//-----------------------------------------------------------
//静的メンバ変数宣言
//-----------------------------------------------------------
LPDIRECT3DTEXTURE9 CKira::m_pTexture[TYPE_MAX] = {};
//-----------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------
CKira::CKira(int nPriority) : CParticle(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
	m_nPatternAnim = 0;
	m_nCounterAnim = 0;
	m_nLife = KIRA_LIFE;
}
//-----------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------
CKira::~CKira()
{
}
//-----------------------------------------------------------
// 生成
//-----------------------------------------------------------
CKira * CKira::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TYPE type)
{
	// CReticleポインタ
	CKira *pBoxEffect;

	// メモリ確保
	pBoxEffect = new CKira(5);
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
// テクスチャ読み込み
//-----------------------------------------------------------
HRESULT CKira::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/blood.png", &m_pTexture[TYPE_BLOOD]);

	return S_OK;
}
//-----------------------------------------------------------
// テクスチャ破棄
//-----------------------------------------------------------
void CKira::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			// テクスチャRelease
			m_pTexture[nCount]->Release();

			// m_pTextureをNULLに
			m_pTexture[nCount] = NULL;
		}
	}
}
//-----------------------------------------------------------
// 初期化
//-----------------------------------------------------------
HRESULT CKira::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
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

	//テクスチャ座標のセット
	SetTexture(
		m_nPatternAnim * 0.25f,
		0.0f,
		m_nPatternAnim * 0.25f + 0.25f,
		1.0f);

	//// テクスチャ受け渡し
	//BindTexture(m_pTexture[m_type]);

	return S_OK;
}
//-----------------------------------------------------------
// 終了
//-----------------------------------------------------------
void CKira::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//-----------------------------------------------------------
// 更新
//-----------------------------------------------------------
void CKira::Update(void)
{
	// 更新
	CParticle::Update();

	m_move.y += -KIRA_FALL_SPEED;

	//テクスチャアニメーション更新
		m_nCounterAnim++;
		if (m_nCounterAnim > 3)
		{
			m_nCounterAnim = 0;
			m_nPatternAnim++;
		}

		if (m_nPatternAnim >= 8)
		{
			Uninit();
			return;
		}

		//テクスチャ座標のセット
		SetTexture(
			m_nPatternAnim * 0.25f,
			0.0f,
			m_nPatternAnim * 0.25f + 0.25f,
			1.0f);

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
void CKira::Draw(void)
{
	// 描画
	CParticle::Draw();
}
//-----------------------------------------------------------
// 血しぶき生成
//-----------------------------------------------------------
void CKira::EffectKira(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	for (int nCount = 0; nCount < KIRA_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360 + -360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		float fRandSize = float(rand() % KIRA_SIZE_X);
		float fRandSpeed = float(rand() % int(KIRA_SPEED * 10));//十倍にしてランダムにする
																 //元の値の倍率に戻す
		fRandSpeed = fRandSpeed / 10;
		CKira::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*fRandSpeed, sinf(D3DXToRadian(fRandRotY))*-(fRandSpeed + KIRA_UP_VALUE), cosf(D3DXToRadian(fRandRotZ))*fRandSpeed), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_BLOOD);
	}
	for (int nCount = 0; nCount < KIRA_VALUE; nCount++)
	{
		float fRandRot = float(rand() % 360 + -360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		float fRandSize = float(rand() % KIRA_SIZE_X);
		float fRandSpeed = float(rand() % int(KIRA_SPEED * 10));//十倍にしてランダムにする
																 //元の値の倍率に戻す
		fRandSpeed = (fRandSpeed / 10) / 2;
		CKira::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*fRandSpeed, sinf(D3DXToRadian(fRandRotY))*-(fRandSpeed + KIRA_UP_VALUE), cosf(D3DXToRadian(fRandRotZ))*fRandSpeed), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), TYPE_BLOOD);
	}
}
