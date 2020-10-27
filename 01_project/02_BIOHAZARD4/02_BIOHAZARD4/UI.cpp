//----------------------------------------
//プレイヤー処理
//----------------------------------------

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
LPDIRECT3DTEXTURE9 CUi::m_pTexture = NULL;

//----------------------------------------
//インクリメント
//----------------------------------------
CUi::CUi(int nPriority):CScene2D(nPriority)
{

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
CUi *CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CUi *pUi;
	pUi = new CUi(OBJTYPE_UI);
	pUi->SetPosition(pos);
	pUi->SetSize(size);
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
		TEXTURE_PLAYER,								// ファイルの名前
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
//テクスチャの破棄
//----------------------------------------
void CUi::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CUi::Init(void)
{	
	CScene2D::Init();
	CScene2D::BindTexture(m_pTexture);

	SetObjType(CScene::OBJTYPE_UI);
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
}

//----------------------------------------
//描画処理
//----------------------------------------
void CUi::Draw(void)
{
	CScene2D::Draw();
}