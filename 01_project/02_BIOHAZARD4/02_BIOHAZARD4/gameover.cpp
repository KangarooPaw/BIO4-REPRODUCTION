//=============================================================================
//
// ゲームオーバー処理 [gameover.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "gameover.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "time.h"
//#include "sound.h"
#include "ui.h"
#include "mode.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGameover::m_pTexture = NULL;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGameover::CGameover()
{
	m_pVtxBuff = NULL;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CGameover::~CGameover()
{
}
//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CGameover::Load(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAMEOVER, &m_pTexture);
	return S_OK;
}
//=============================================================================
// テクスチャアンロード
//=============================================================================
void CGameover::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CGameover::Init(void)
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

	pVtx[0].pos = D3DXVECTOR3(SCREEN_CENTER_X + (-SCREEN_WIDTH / 2), SCREEN_CENTER_Y + (-SCREEN_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_CENTER_X + (SCREEN_WIDTH / 2), SCREEN_CENTER_Y + (-SCREEN_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_CENTER_X + (-SCREEN_WIDTH / 2), SCREEN_CENTER_Y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_CENTER_X + (SCREEN_WIDTH / 2), SCREEN_CENTER_Y + (SCREEN_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CGameover::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CGameover::Update(void)
{
	if (CScene::GetUpdateStop() == false)
	{
		if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_RETURN) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
		{ //Enterキー または Bボタンを押したとき
		  //フェードの生成
			CManager::CreateFade(CManager::MODE_TITLE);
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CGameover::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetTexture(0, m_pTexture);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}