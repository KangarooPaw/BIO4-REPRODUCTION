//--------------------------------------------------------------------
// Smoke
// smoke.cpp
// Author : 管原 司
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "spark.h"
//--------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------
CSpark::CSpark()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAddColor = 0.0f;
	m_nCount = 0;
}
//--------------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------------
CSpark::~CSpark()
{
}
//--------------------------------------------------------------------
// 生成
//--------------------------------------------------------------------
CSpark * CSpark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CExplosionクラスのポインタ
	CSpark *pSmoke;

	// メモリ確保
	pSmoke = new CSpark;

	// 初期化
	pSmoke->Init(pos, size, rot, col, TexType, move);

	// CExplosionクラスのポインタを返す
	return pSmoke;
}
//--------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------
HRESULT CSpark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CParticleクラスのInit
	CParticle::Init(pos, size, rot, col, TexType);

	// move代入
	m_move = move;

	// カラー加算値を0.005fに
	m_fAddColor = 0.005f;

	return S_OK;
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CSpark::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CSpark::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// カラー取得
	D3DXCOLOR col = GetColor();

	// インクリメント
	m_nCount++;

	// カウントが2以上の場合
	if (m_nCount >= 2)
	{
		// Scaleの加算値を1.5fに
		m_move.y -= 0.015f;
	}

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
void CSpark::Draw(void)
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