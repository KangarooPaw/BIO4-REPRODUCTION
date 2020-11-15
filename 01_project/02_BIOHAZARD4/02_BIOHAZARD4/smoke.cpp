//--------------------------------------------------------------------
// 煙
// smoke.cpp
// Author : 管原 司
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "smoke.h"
//--------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------
CSmoke::CSmoke()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fScale = 0.0f;
	m_fAddScale = 0.0f;
	m_fAddColor = 0.0f;
}
//--------------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------------
CSmoke::~CSmoke()
{
}
//--------------------------------------------------------------------
// 生成
//--------------------------------------------------------------------
CSmoke * CSmoke::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CExplosionクラスのポインタ
	CSmoke *pSmoke;

	// メモリ確保
	pSmoke = new CSmoke;

	// 初期化
	pSmoke->Init(pos, size, rot, col, TexType, move);

	// CExplosionクラスのポインタを返す
	return pSmoke;
}
//--------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------
HRESULT CSmoke::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CParticleクラスのInit
	CParticle::Init(pos, size, rot, col, TexType);

	// move代入
	m_move = move;

	// 拡大率を1,0fに
	m_fScale = 1.0f;

	// 拡大率加算値を 0.9fに
	m_fAddScale = 0.9f;

	// カラー加算値を0.006fに
	m_fAddColor = 0.006f;

	// m_moveに0.5掛ける
	m_move *= 0.5f;
	return S_OK;
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CSmoke::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CSmoke::Update(void)
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

	// 位置更新
	pos.x += m_move.x;
	pos.y += m_move.y;
	pos.z += m_move.z;

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
void CSmoke::Draw(void)
{
	// 描画
	CParticle::Draw();
}