//--------------------------------------------------------------------
// 爆発
// explosion.cpp
// Author : 管原 司
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "explosion.h"
//--------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------
CExplosion::CExplosion()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fScale = 0.0f;
	m_fAddScale = 0.0f;
	m_fAddColor = 0.0f;
	m_nCount = 0;
}
//--------------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------------
CExplosion::~CExplosion()
{
}
//--------------------------------------------------------------------
// 生成
//--------------------------------------------------------------------
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CExplosionクラスのポインタ
	CExplosion *pExplosion;

	// メモリ確保
	pExplosion = new CExplosion;

	// 初期化
	pExplosion->Init(pos, size, rot, col, TexType, move);

	// CExplosionクラスのポインタを返す
	return pExplosion;
}
//--------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, D3DXVECTOR3 move)
{
	// CParticleクラスのInit
	CParticle::Init(pos, size, rot, col, TexType);

	// move代入
	m_move = move;

	// 拡大率を1,0fに
	m_fScale = 1.0f;

	// 拡大率加算値を8.5fに
	m_fAddScale = 8.5f;

	// カラー加算値を0.02fに
	m_fAddColor = 0.02f;

	// m_moveに0.5掛ける
	m_move *= 0.5f;

	return S_OK;
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CExplosion::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CExplosion::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// カラー取得
	D3DXCOLOR col = GetColor();

	// 拡大縮小
	m_fScale += m_fAddScale;

	// インクリメント
	m_nCount++;

	// カウントが5以上の場合
	if (m_nCount >= 10)
	{
		// Scaleの加算値を1.5fに
		m_fAddScale = 0.5f;
	}
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
void CExplosion::Draw(void)
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