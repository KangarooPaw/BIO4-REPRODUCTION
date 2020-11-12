//---------------------------------------------------
// Life
// Life.cpp
// Author:	管原 司
//---------------------------------------------------

//---------------------------------------------------
//インクルードファイル
//---------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "input.h"
#include "keyboard.h"
#include "life.h"
#include "player.h"

//--------------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
int CLife::m_nDamageCnt = 0;
bool CLife::m_bHit = false;
bool CLife::m_bHerb = false;
//--------------------------------------------------
//コンストラクタ
//--------------------------------------------------
CLife::CLife(int nPriority) : CScene(nPriority)
{
	memset(m_apScene2D, 0, sizeof(m_apScene2D));
	m_col = D3DCOLOR((0.0f, 0.0f, 0.0f, 0.0f));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Fade = FADE_NONE;
	m_State = STATE_NONE;
	m_fRadian = 0.0f;
	m_fLengh = 0.0f;
	m_nCnt = 0;
}

//--------------------------------------------------
//デストラクタ
//--------------------------------------------------
CLife::~CLife()
{

}

//--------------------------------------------------
//生成関数
//--------------------------------------------------
CLife * CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float Length)
{
	//CPolygonクラスのポインタ
	CLife * pLife;

	//メモリ確保
	pLife = new CLife;

	// pos代入
	pLife->m_pos = pos;
	// サイズ代入
	pLife->m_size = size;
	// 半径代入
	pLife->m_fLengh = Length;

	//初期化
	pLife->Init();

	//CPolygonのポインタを返す
	return pLife;
}

//----------------------------------------------------------
// テクスチャの読み込み
//----------------------------------------------------------
HRESULT CLife::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/tezyo.png", &m_pTexture);
	return S_OK;
}

//----------------------------------------------------------
// テクスチャの破棄
//----------------------------------------------------------
void CLife::Unload(void)
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

//--------------------------------------------------
//初期化
//--------------------------------------------------
HRESULT CLife::Init(void)
{
	// カラー
	m_col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	// 角度
	float fAngle = 0.01f;

	m_pScene2D = new CScene2D(5);
	// 初期化
	m_pScene2D->Init();
	// サイズ設定
	m_pScene2D->SetSize(D3DXVECTOR3(440.0f, 440.0f, 0.0f));
	// カラー設定
	m_pScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	// 向きの設定
	m_pScene2D->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// 位置設定
	m_pScene2D->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y + 128, m_pos.z));
	// テクスチャ受け渡し
	m_pScene2D->BindTexture(m_pTexture);

	// 100回繰り返す
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		// メモリ確保
		m_apScene2D[nCnt] = new CScene2D(5);
		// 初期化
		m_apScene2D[nCnt]->Init();
		// サイズ設定
		m_apScene2D[nCnt]->SetSize(m_size);
		// カラー設定
		m_apScene2D[nCnt]->SetColor(m_col);
		// 向きの設定
		m_apScene2D[nCnt]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(3.6f * nCnt)));
		// 孤度
		m_fRadian = (float)nCnt / MAX_LIFE;
		m_fRadian = m_fRadian * D3DX_PI * 2 + fAngle;
		// 座標を求める
		m_pos.x = m_pos.x - cosf(m_fRadian) * m_fLengh;
		m_pos.y = m_pos.y + sinf(m_fRadian) * m_fLengh;
		// 位置設定
		m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(m_pos));
	}
	//点滅
	m_Fade = FADE_OUT;
	//緑に設定
	m_State = STATE_GREEN;

	return S_OK;
}

//--------------------------------------------------
//終了
//--------------------------------------------------
void CLife::Uninit(void)
{
	//破棄
	Release();
}

//--------------------------------------------------
//更新
//--------------------------------------------------
void CLife::Update(void)
{
	//100回繰り返す
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		//更新
		m_apScene2D[nCnt]->Update();
		if (nCnt >= m_nCnt)
		{
			//カラー設定
			m_apScene2D[nCnt]->SetColor(m_col);
		}
	}
	if (m_Fade != FADE_NONE)
	{
		//フェードイン
		if (m_Fade == FADE_IN)
		{
			//緑の場合
			if (m_State == STATE_GREEN)
			{
				//g値を加算
				m_col.r = 0.0f;
				m_col.g += FADE_RATE;
				//画面が黒くなったら
				if (m_col.g >= 1.0f)
				{
					//フェード終了処理
					m_col.g = 1.0f;
					m_Fade = FADE_OUT;
				}
			}
			//黄色の場合
			if (m_State == STATE_YELLOW)
			{
				m_col.r = 1.0f;
				m_col.g = 1.0f;
				m_col.r += FADE_RATE;
				//g値を加算
				m_col.g += FADE_RATE;
				//画面が黒くなったら
				if (m_col.g >= 1.0f && m_col.r >= 1.0f)
				{
					//フェード終了処理
					m_col.r = 1.0f;
					m_col.g = 1.0f;
					m_Fade = FADE_OUT;
				}
			}
			//赤の場合
			if (m_State == STATE_RED)
			{
				m_col.g = 0.0f;
				//g値を加算
				m_col.r += FADE_RATE;
				//画面が黒くなったら
				if (m_col.r >= 1.0f)
				{
					//フェード終了処理
					m_col.r = 1.0f;
					m_Fade = FADE_OUT;
				}
			}
		}
		//フェードアウト
		if (m_Fade == FADE_OUT)
		{
			//緑の場合
			if (m_State == STATE_GREEN)
			{
				m_col.r = 0.0f;
				//g値を減算
				m_col.g -= FADE_RATE;
				//画面の透過
				if (m_col.g <= 0.5f)
				{
					//フェード処理切り替え
					m_col.g = 0.5f;
					//モード設定
					m_Fade = FADE_IN;
				}
			}
			//緑の場合
			if (m_State == STATE_YELLOW)
			{
				//g値を減算
				m_col.r -= FADE_RATE;
				m_col.g -= FADE_RATE;
				//画面の透過
				if (m_col.g <= 0.5f || m_col.r <= 0.5f)
				{
					//col設定
					m_col.r = 0.5f;
					m_col.g = 0.5f;
					//フェード処理切り替え
					m_Fade = FADE_IN;
				}
			}
			//緑の場合
			if (m_State == STATE_RED)
			{
				m_col.g = 0.0f;
				//r値を減算
				m_col.r -= FADE_RATE;
				//画面の透過
				if (m_col.r <= 0.5f)
				{
					//フェード処理切り替え
					m_col.r = 0.5f;
					//モード設定
					m_Fade = FADE_IN;
				}
			}
		}
	}

	//カウントを0以上の場合
	if (m_nCnt > 0 && m_nCnt < 100)
	{
		if (m_State == STATE_GREEN)
		{
			//カラー設定
			m_apScene2D[m_nCnt]->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		if (m_State == STATE_YELLOW)
		{
			//カラー設定
			m_apScene2D[m_nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
		if (m_State == STATE_RED)
		{
			//カラー設定
			m_apScene2D[m_nCnt]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	//100より低い場合
	if (m_nCnt < MAX_LIFE && m_nCnt >= 0)
	{
		//カラー設定
		m_apScene2D[m_nCnt]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	//ダメージを受けているなら
	if (m_bHit == true)
	{
		//体力減少
		m_nCnt++;
		m_nDamageCnt--;
		//ダメージ分減らしたら
		if (m_nDamageCnt == 0)
		{
			m_bHit = false;
		}
	}

	if (m_bHerb == true)
	{
		if (m_nCnt != 0)
		{
			//体力増加
			m_nCnt--;
		}
		m_nDamageCnt--;
		//ダメージ分回復するか全回復したら
		if (m_nDamageCnt == 0)
		{
			m_bHerb = false;
			m_nDamageCnt = 0;
		}

	}
	//カウントが50より低い場合
	if (m_nCnt < 50)
	{
		//StateをGreenに
		m_State = STATE_GREEN;
	}
	//カウントが50以上かつ80より低い場合
	if (m_nCnt >= 50 && m_nCnt < 80)
	{
		//StateをYellowに
		m_State = STATE_YELLOW;
	}
	//カウントが80以上の場合
	if (m_nCnt >= 80)
	{
		//StateをRedに
		m_State = STATE_RED;
	}
	//カウントが最大体力に達した場合
	if (m_nCnt >= MAX_LIFE)
	{
		CPlayer::DeathFlag();
	}
}

//--------------------------------------------------
//描画
//--------------------------------------------------
void CLife::Draw(void)
{

}

//--------------------------------------------------
//体力の減少処理
//--------------------------------------------------
void CLife::LifeDecrement(int nDamage)
{
	m_nDamageCnt = nDamage;
	m_bHit = true;
}

//--------------------------------------------------
//体力の増加処理
//--------------------------------------------------
void CLife::LifeIncrement(int nDamage)
{
	m_nDamageCnt = nDamage;
	m_bHerb = true;
}
