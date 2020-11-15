//--------------------------------------------------------------------
// 回復エフェクト
// heal.cpp
// Author : 管原 司
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "heal.h"
//--------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------
CHeal::CHeal(int nPriority) : CParticle(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAddColor = 0.0f;
}
//--------------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------------
CHeal::~CHeal()
{
}
//--------------------------------------------------------------------
// 生成
//--------------------------------------------------------------------
CHeal * CHeal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CHealクラスのポインタ
	CHeal *pHeal;

	// メモリ確保
	pHeal = new CHeal(OBJTYPE_PARTICLE);

	// 初期化
	pHeal->Init(pos, size, rot, col, TexType);

	// CHealクラスのポインタを返す
	return pHeal;
}
//--------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------
HRESULT CHeal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CParticleクラスのInit
	CParticle::Init(pos, size, rot, col, TexType);

	// アルファテストの数値設定
	SetAlpha(100);

	// カラー加算値を0.02fに
	m_fAddColor = 0.02f;

	m_move.y = 0.1f;
	return S_OK;
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CHeal::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CHeal::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// カラー取得
	D3DXCOLOR col = GetColor();

	// α減算
	col.a -= m_fAddColor;

	// カラー設定
	SetColor(col);

	pos.y += m_move.y;

	// 位置座標設定
	SetPosition(pos);

	// α値が0以下の場合
	if (col.a <= 0.0f)
	{
		// 終了
		Uninit();
		// 処理を通らないように
		return;
	}
}
//--------------------------------------------------------------------
// 描画
//--------------------------------------------------------------------
void CHeal::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CParticle::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//--------------------------------------------------------------------
// 回復effect生成
//--------------------------------------------------------------------
void CHeal::HealCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < 30; nCnt++)
	{
		float fPosX = float(rand() % (int)15.5f * 10 - (int)7.0f * 10);
		float fPosY = float(rand() % (int)15.5f * 10 - (int)7.0f * 10);
		float fPosZ = float(rand() % (int)15.5f * 10 - (int)7.0f * 10);
		fPosX = fPosX / 10;
		fPosY = fPosY / 10;
		fPosZ = fPosZ / 10;
		CHeal::Create(D3DXVECTOR3(pos.x + cosf(rot.y) + fPosX, pos.y + 40.0f + fPosY, pos.z + sinf(rot.y) + fPosZ),
			D3DXVECTOR3(3.0f, 3.0f, 0.0f),
			D3DXVECTOR3(cosf(rot.y), 0.0f, sinf(rot.y)),
			col,
			CParticle::TEX_TYPE_3);
	}
}
