//=============================================================================
//
// UI [ui.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "ui.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPDIRECT3DTEXTURE9 CUi::m_pTexture[TYPE_MAX] = {};

//----------------------------------------
//インクリメント
//----------------------------------------
CUi::CUi(int nPriority):CScene2D(nPriority)

{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NONE;
}

//----------------------------------------
//デクリメント
//----------------------------------------
CUi::~CUi()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CUi *CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	CUi *pUi;
	pUi = new CUi(OBJTYPE_UI);
	pUi->m_pos = pos;
	pUi->m_size = size;
	pUi->m_type = type;
	pUi->Init();
	return pUi;
}

//----------------------------------------
//読み込み処理
//----------------------------------------
HRESULT CUi::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TITLE,								// ファイルの名前
		&m_pTexture[TYPE_TITLE]);
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_TUTORIAL,								// ファイルの名前
		&m_pTexture[TYPE_TUTORIAL]);
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_GAMEOVER,								// ファイルの名前
		&m_pTexture[TYPE_GAMEOVER]);
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RESULT,								// ファイルの名前
		&m_pTexture[TYPE_RESULT]);

	return S_OK;
}

//----------------------------------------
//テクスチャの破棄
//----------------------------------------
void CUi::Unload(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CUi::Init(void)
{	
	CScene2D::Init();
	SetObjType(CScene::OBJTYPE_UI);
	SetPosition(m_pos);		//位置
	SetSize(m_size);		//サイズ
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	BindTexture(m_pTexture[m_type]);

	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//----------------------------------------
//更新処理
//----------------------------------------
void CUi::Update(void)
{
	CScene2D::Update();

	SetPosition(m_pos);		//位置
	SetSize(m_size);			//サイズ
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//----------------------------------------
//描画処理
//----------------------------------------
void CUi::Draw(void)
{
	CScene2D::Draw();
}