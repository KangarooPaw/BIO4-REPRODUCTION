//-----------------------------------------------------------
// Reticle
// reticle.cpp
// Author : 管原　司
//-----------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "joystick.h"
#include "billboard.h"
#include "reticle.h"
//-----------------------------------------------------------
//静的メンバ変数宣言
//-----------------------------------------------------------
LPDIRECT3DTEXTURE9 CReticle::m_pTexture = NULL;
//-----------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------
CReticle::CReticle(int nPriority) : CBillboard(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//-----------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------
CReticle::~CReticle()
{
}
//-----------------------------------------------------------
// 生成
//-----------------------------------------------------------
CReticle * CReticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
{
	// CReticleポインタ
	CReticle *pReticle;

	// メモリ確保
	pReticle = new CReticle(OBJTYPE_UI);

	// 初期化
	pReticle->Init(pos, size, rot, col);

	// ポインタを返す
	return pReticle;
}
//-----------------------------------------------------------
// テクスチャ読み込み
//-----------------------------------------------------------
HRESULT CReticle::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/reticle.png", &m_pTexture);

	return S_OK;
}
//-----------------------------------------------------------
// テクスチャ破棄
//-----------------------------------------------------------
void CReticle::Unload(void)
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
//-----------------------------------------------------------
// 初期化
//-----------------------------------------------------------
HRESULT CReticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col)
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

	// 初期化
	CBillboard::Init();

	// 位置座標設定
	SetPosition(m_pos);

	// サイズ設定
	SetSize(m_size);

	// 向き設定
	SetRotation(m_rot);

	// カラー設定
	SetColor(m_col);

	// テクスチャ受け渡し
	BindTexture(m_pTexture);

	return S_OK;
}
//-----------------------------------------------------------
// 終了
//-----------------------------------------------------------
void CReticle::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}
//-----------------------------------------------------------
// 更新
//-----------------------------------------------------------
void CReticle::Update(void)
{
	// 更新
	CBillboard::Update();

	// 位置座標
	D3DXVECTOR3 pos;

	// 注視点取得
	pos = CManager::GetCamera()->GetPosR();
	//コントローラーの取得処理
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	// L2を離したら
	if (pInputJoystick->GetJoystickRelease(pInputJoystick->BUTTON_L2))
	{
		// 終了
		Uninit();
		return;
	}

	m_pos.x = pos.x;
	m_pos.y = pos.y + 10;
	m_pos.z = pos.z;
	// カラー設定
	SetColor(m_col);

	// 位置座標設定
	SetPosition(m_pos);

}
//-----------------------------------------------------------
// 描画
//-----------------------------------------------------------
void CReticle::Draw(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ライトの効果を無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 描画
	CBillboard::Draw();

	// ライトの効果を有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
