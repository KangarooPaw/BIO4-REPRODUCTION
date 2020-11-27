//=============================================================================
//
// 数字の処理 [number.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "number.h"
#include "bullet_ui.h"
//****************************************************************************************************
// 静的メンバ変数初期化
//****************************************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_nPatternAnim = 0;
	m_type = TYPE_NONE;
	m_nAlpha = 255;
}
//=============================================================================
// デストラクタ
//=============================================================================
CNumber::~CNumber()
{
}
//=============================================================================
// 生成処理
//=============================================================================
CNumber * CNumber::Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight, TYPE type)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{
		pNumber = new CNumber;
		pNumber->m_type = type;
		pNumber->Init(pos, fSizeWidth, fSizeHeight);
	}

	return pNumber;
}
//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CNumber::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NUMBER, &m_pTexture);
	return S_OK;
}
//=============================================================================
// テクスチャアンロード
//=============================================================================
void CNumber::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x + (-fSizeWidth / 2), pos.y + (-fSizeHeight / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (fSizeWidth / 2), pos.y + (-fSizeHeight / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x + (-fSizeWidth / 2), pos.y + (fSizeHeight / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (fSizeWidth / 2), pos.y + (fSizeHeight / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	switch (m_type)
	{
	case TYPE_UI:
		pVtx[0].col = D3DCOLOR_RGBA(240, 255, 240, 150);
		pVtx[1].col = D3DCOLOR_RGBA(240, 255, 240, 150);
		pVtx[2].col = D3DCOLOR_RGBA(240, 255, 240, 150);
		pVtx[3].col = D3DCOLOR_RGBA(240, 255, 240, 150);
		break;
	case TYPE_POINTS:
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
		break;
	default:
		break;
	}

	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.1f + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void CNumber::Update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//加算

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, m_pTexture);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================================================================
// 数字をセット
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
}
