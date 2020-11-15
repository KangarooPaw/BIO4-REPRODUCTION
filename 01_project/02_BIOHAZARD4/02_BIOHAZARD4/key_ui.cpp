//=============================================================================
//
// 鍵UI [key_ui.cpp]
// Author : 林川紗梨夏
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "key_ui.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CKeyUi::m_pTexture = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CKeyUi::CKeyUi()
{
	m_pVtxBuff = NULL;
	m_nPatternAnim = TYPE_NOGLOW;
}
//=============================================================================
// デストラクタ
//=============================================================================
CKeyUi::~CKeyUi()
{
}
//=============================================================================
// 生成
//=============================================================================
CKeyUi * CKeyUi::Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight)
{
	CKeyUi *pKey = NULL;

	if (pKey == NULL)
	{
		pKey = new CKeyUi;
		pKey->Init(pos, fSizeWidth, fSizeHeight);
	}

	return pKey;
}
//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CKeyUi::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_KEY, &m_pTexture);
	return S_OK;
}
//=============================================================================
// テクスチャアンロード
//=============================================================================
void CKeyUi::Unload(void)
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
HRESULT CKeyUi::Init(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
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

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(m_nPatternAnim * 0.5f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_nPatternAnim * 0.5f + 0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_nPatternAnim * 0.5f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_nPatternAnim * 0.5f + 0.5f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CKeyUi::Uninit(void)
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
void CKeyUi::Update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void CKeyUi::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, m_pTexture);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=============================================================================
// 星セット処理
//=============================================================================
void CKeyUi::SetKey(TYPE type)
{

	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(type * 0.5f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(type * 0.5f + 0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(type * 0.5f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(type * 0.5f + 0.5f, 1.0f);

	m_pVtxBuff->Unlock();
}
