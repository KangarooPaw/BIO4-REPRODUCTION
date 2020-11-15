//--------------------------------------------------------------------
// 円を描くパーティクル
// circleparticle.cpp
// Author : 管原 司
//--------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
#include "circleparticle.h"
//--------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------
CCircleParticle::CCircleParticle(int nPriority) : CParticle(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ColorType = COLOR_NONE;
	m_fRadian = 0.0f;
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fAddColor = 0.0f;
}
//--------------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------------
CCircleParticle::~CCircleParticle()
{
}
//--------------------------------------------------------------------
// 生成
//--------------------------------------------------------------------
CCircleParticle * CCircleParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength)
{
	// CCircleParticleクラスのポインタ
	CCircleParticle *pCircleParticle;

	// メモリ確保
	pCircleParticle = new CCircleParticle(OBJTYPE_CIRCLE);

	// 初期化
	pCircleParticle->Init(pos, size, rot, col, TexType, fRadian, fLength);

	// CCircleParticleクラスのポインタを返す
	return pCircleParticle;
}
//--------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------
HRESULT CCircleParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, CParticle::TEX_TYPE TexType, float fRadian, float fLength)
{
	// CParticleクラスのInit
	CParticle::Init(pos, size, rot, col, TexType);

	m_pos = pos;

	// 弧度
	m_fRadian = fRadian;

	// 半径
	m_fLength = fLength;

	// カラー加算値を0.01fに
	m_fAddColor = 0.01f;

	// 角度0.1f
	m_fAngle = 0.1f;

	// カラータイプ
	m_ColorType = COLOR_ADD;

	// ラジアン計算
	m_fRadian = m_fRadian * D3DX_PI * 2;

	// アルファテストの数値設定
	SetAlpha(100);

	return S_OK;
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CCircleParticle::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//--------------------------------------------------------------------
// 終了
//--------------------------------------------------------------------
void CCircleParticle::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// カラー取得
	D3DXCOLOR col = GetColor();

	// ラジアンに角度を加算
	m_fRadian += m_fAngle;

	// 座標を求める
	pos.x = m_pos.x + cosf(m_fRadian) * m_fLength;
	pos.z = m_pos.z + sinf(m_fRadian) * m_fLength;

	// a値減算
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
void CCircleParticle::Draw(void)
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
// 円のパーティクル生成
//--------------------------------------------------------------------
void CCircleParticle::CircleCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, int nMax, float fLength)
{
	// nMax回繰り返す
	for (int nCnt = 0; nCnt < nMax; nCnt++)
	{
		// 弧度
		float fRadian = (float)nCnt / nMax;
		// パーティクル生成
		CCircleParticle::Create(pos, size, rot, col, CParticle::TEX_TYPE_2, fRadian, fLength);
	}
}