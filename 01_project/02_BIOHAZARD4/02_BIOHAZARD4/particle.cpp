//-----------------------------------------------------------
// Particle
// particle.cpp
// Author : 管原　司
//-----------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"
//-----------------------------------------------------------
//静的メンバ変数宣言
//-----------------------------------------------------------
LPDIRECT3DTEXTURE9 CParticle::m_pTexture[TYPE_MAX] = {};
//-----------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------
CParticle::CParticle(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Type = TYPE_NONE;
	m_TexType = TEX_TYPE_NONE;
	m_ColorType = COLOR_NONE;
	m_fRadian = 0.0f;
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fScale = 0.0f;
	m_fAddScale = 0.0f;
	m_fAddColor = 0.0f;
	m_nCount = 0;
}
//-----------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------
CParticle::~CParticle()
{
}
//-----------------------------------------------------------
// 生成
//-----------------------------------------------------------
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, float fRadian, float fLength, TYPE Type, TEX_TYPE TexType)
{
	// CParticleポインタ
	CParticle *pParticle;

	// メモリ確保
	pParticle = new CParticle(7);

	//初期化
	pParticle->Init(pos, size, rot, col, move, fRadian, fLength, Type, TexType);

	// ポインタを返す
	return pParticle;
}
//----------------------------------------------------------
// テクスチャの読み込み
//----------------------------------------------------------
HRESULT CParticle::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/particle001.png", &m_pTexture[TEX_TYPE_1]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/particle002.png", &m_pTexture[TEX_TYPE_2]);
	return S_OK;
}
//----------------------------------------------------------
// テクスチャの破棄
//----------------------------------------------------------
void CParticle::Unload(void)
{
	// 3回繰り返す
	for (int nCnt = 0; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			// テクスチャRelease
			m_pTexture[nCnt]->Release();

			// m_pTextureをNULLに
			m_pTexture[nCnt] = NULL;
		}
	}
}
//-----------------------------------------------------------
// 初期化
//-----------------------------------------------------------
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, float fRadian, float fLength, TYPE Type, TEX_TYPE TexType)
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
	// 移動量
	m_move = move;
	// 弧度
	m_fRadian = fRadian;
	// 半径
	m_fLength = fLength;
	// タイプ設定
	m_Type = Type;
	// テクスチャタイプ
	m_TexType = TexType;

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
	BindTexture(m_pTexture[m_TexType]);

	// 拡大率を1,0fに
	m_fScale = 1.0f;

	// タイプが爆発の場合
	if (m_Type == TYPE_EXPLOSION)
	{
		// 拡大率加算値を1.5fに
		m_fAddScale = 8.5f;

		// カラー加算値を0.02fに
		m_fAddColor = 0.02f;
	}
	// タイプが火花の場合
	if (m_Type == TYPE_SPARK)
	{
		// 拡大率加算値を0.0fに
		m_fAddScale = 0.0f;

		// カラー加算値を0.002fに
		m_fAddColor = 0.005f;
	}

	// タイプが煙の場合
	if (m_Type == TYPE_SMOKE)
	{
		// 拡大率加算値を 0.9fに
		m_fAddScale = 0.9f;

		// カラー加算値を0.006fに
		m_fAddColor = 0.006f;
	}

	// TypeHitの場合
	if (m_Type == TYPE_HIT)
	{
		// 拡大加算値0.0fに
		m_fAddScale = 0.0f;

		// カラー加算値を0.006fに
		m_fAddColor = 0.1f;
	}

	// タイプがマズルフラッシュの場合
	if (m_Type == TYPE_MAZLE_FLASH)
	{
		// 拡大率加算値を0.5fに
		m_fAddScale = 0.5f;

		// カラー加算値を0.08fに
		m_fAddColor = 0.08f;
	}
	// 
	if (m_Type == TYPE_CIRCLE)
	{
		// 拡大率加算値を0.0fに
		m_fAddScale = 0.0f;

		// カラー加算値を0.01fに
		m_fAddColor = 0.05f;

		m_fAngle = 0.01f;

		// カラータイプ
		m_ColorType = COLOR_ADD;

		m_fRadian = m_fRadian * D3DX_PI * 2;

	}
	// タイプが火花でない場合
	if (m_Type != TYPE_SPARK)
	{
		// m_moveに0.5掛ける
		m_move *= 0.5f;
	}
	return S_OK;
}
//-----------------------------------------------------------
// 終了
//-----------------------------------------------------------
void CParticle::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}
//-----------------------------------------------------------
// 更新
//-----------------------------------------------------------
void CParticle::Update(void)
{
	// 更新
	CBillboard::Update();

	// 拡大縮小
	m_fScale += m_fAddScale;

	if (m_Type != TYPE_CIRCLE)
	{
		// α減算
		m_col.a -= m_fAddColor;
	}


	// タイプがExplosionの場合
	if (m_Type == TYPE_EXPLOSION)
	{
		// インクリメント
		m_nCount++;
		// カウントが5以上の場合
		if (m_nCount >= 10)
		{
			// Scaleの加算値を1.5fに
			m_fAddScale = 0.5f;
		}
	}
	// タイプがSPARKの場合
	if (m_Type == TYPE_SPARK)
	{
		// インクリメント
		m_nCount++;
		// カウントが5以上の場合
		if (m_nCount >= 2)
		{
			// Scaleの加算値を1.5fに
			m_move.y -= 0.015f;
		}
	}
	// タイプがCIRCLEの場合
	if (m_Type == TYPE_CIRCLE)
	{
		m_fRadian += m_fAngle;

		// 座標を求める
		m_pos.x = /*m_pos.x +*/ cosf(m_fRadian) * m_fLength;
		m_pos.z = /*m_pos.z +*/ sinf(m_fRadian) * m_fLength;

		if (m_ColorType != COLOR_NONE)
		{
			if (m_ColorType == COLOR_ADD)
			{
				// a値加算
				m_col.a += m_fAddColor;
				// a値が1.0f以上の場合
				if (m_col.a >= PARTICLE_CIRCLE_COL_MAX)
				{
					m_col.a = PARTICLE_CIRCLE_COL_MAX;
					m_ColorType = COLOR_MIN;
				}
			}
			if (m_ColorType == COLOR_MIN)
			{
				// a値減算
				m_col.a -= m_fAddColor;
				// a値が0.5以下の場合
				if (m_col.a <= PARTICLE_CIRCLE_COL_MIN)
				{
					m_col.a = PARTICLE_CIRCLE_COL_MIN;
					m_ColorType = COLOR_ADD;
				}
			}
		}
	}
	// カラー設定
	SetColor(m_col);

	// 拡大率設定
	SetScale(m_fScale);

	// 位置更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	// 位置座標設定
	SetPosition(m_pos);

	// α値が0以下の場合
	if (m_col.a < 0.0f)
	{
		// 終了
		Uninit();
		// 処理を通らないように
		return;
	}
}
//-----------------------------------------------------------
// 描画
//-----------------------------------------------------------
void CParticle::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// タイプがEXPLOSIONの場合
	if (m_Type == TYPE_EXPLOSION || m_Type == TYPE_SPARK || m_Type == TYPE_CIRCLE)
	{
		// 加算合成の設定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// 描画
	CBillboard::Draw();

	// タイプが爆発の場合
	if (m_Type == TYPE_EXPLOSION || m_Type == TYPE_SPARK || m_Type == TYPE_CIRCLE)
	{
		// 元に戻す
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}