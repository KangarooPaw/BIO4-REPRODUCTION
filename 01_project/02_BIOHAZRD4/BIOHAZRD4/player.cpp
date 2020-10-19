//----------------------------------------
//プレイヤー処理
//----------------------------------------

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "player.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//----------------------------------------
//インクリメント
//----------------------------------------
CPlayer::CPlayer(int nPriority):CScene2D(nPriority)
{

}

//----------------------------------------
//デクリメント
//----------------------------------------
CPlayer::~CPlayer()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CPlayer *CPlayer::Create(float nPosX, float nPosY)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init(nPosX, nPosY);
	return pPlayer;
}

//----------------------------------------
//読み込み処理
//----------------------------------------
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_PLAYER,					// ファイルの名前
		&m_pTexture);

	return S_OK;
}

//----------------------------------------
//テクスチャの破棄
//----------------------------------------
void CPlayer::Unload(void)
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
HRESULT CPlayer::Init(float nPosX, float nPosY)
{
	CScene2D::Init(nPosX, nPosY,PLAYER_WIDTH,PLAYER_HEIGHT);
	CScene2D::BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//----------------------------------------
//更新処理
//----------------------------------------
void CPlayer::Update(void)
{

}

//----------------------------------------
//描画処理
//----------------------------------------
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}