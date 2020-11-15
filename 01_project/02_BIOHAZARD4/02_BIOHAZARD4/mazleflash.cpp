//--------------------------------------------------------------------
// マズルフラッシュ
// mazleflash.cpp
// Author : 管原 司
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "mazleflash.h"
//--------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------
CMazleFlash::CMazleFlash(int nPriority) : CParticle(nPriority)
{
	m_fScale = 0.0f;
	m_fAddScale = 0.0f;
	m_fAddColor = 0.0f;
}
//--------------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------------
CMazleFlash::~CMazleFlash()
{
}
//--------------------------------------------------------------------
// 生成
//--------------------------------------------------------------------
CMazleFlash * CMazleFlash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CMazleFlashクラスのポインタ
	CMazleFlash *pMazleFlash;

	// メモリ確保
	pMazleFlash = new CMazleFlash(OBJTYPE_PARTICLE);

	// 初期化
	pMazleFlash->Init(pos, size, rot, col, TexType);

	// CMazleFlashクラスのポインタを返す
	return pMazleFlash;
}
//--------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------
HRESULT CMazleFlash::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType)
{
	// CParticleクラスのInit
	CParticle::Init(pos, size, rot, col, TexType);

	// 拡大率を1,0fに
	m_fScale = 1.0f;

	// 拡大率加算値を0.5fに
	m_fAddScale = 0.5f;

	// カラー加算値を0.08fに
	m_fAddColor = 0.08f;

	return S_OK;
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CMazleFlash::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CMazleFlash::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// カラー取得
	D3DXCOLOR col = GetColor();

	// 拡大縮小
	m_fScale += m_fAddScale;

	// 拡大率設定
	SetScale(m_fScale);

	// α減算
	col.a -= m_fAddColor;

	// カラー設定
	SetColor(col);

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
void CMazleFlash::Draw(void)
{
	// 描画
	CParticle::Draw();
}