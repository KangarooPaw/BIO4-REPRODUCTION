//----------------------------------------------------------------
// ButtonUI
// button_ui.cpp
// Author : 管原 司
//----------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "button_ui.h"
//----------------------------------------------------------------
// 静的メンバ変数宣言
//----------------------------------------------------------------
LPDIRECT3DTEXTURE9 CButton_UI::m_apTexture[TYPE_MAX] = {};

bool CButton_UI::m_bUse = true;
//----------------------------------------------------------------
// コンストラクタ
//----------------------------------------------------------------
CButton_UI::CButton_UI(int nPriority) : CScene2D(nPriority)
{
	m_Type = TYPE_NONE;
	m_bUse = true;
}
//----------------------------------------------------------------
// デストラクタ
//----------------------------------------------------------------
CButton_UI::~CButton_UI()
{
}
//----------------------------------------------------------------
// 生成
//----------------------------------------------------------------
CButton_UI * CButton_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	// CButton_UIのポインタ
	CButton_UI *pButton_UI;
	// メモリ確保
	pButton_UI = new CButton_UI(OBJTYPE_UI);
	// 初期化処理
	pButton_UI->Init(pos, size, nType);
	return pButton_UI;
}
//----------------------------------------------------------------
// テクスチャ読み込み
//----------------------------------------------------------------
HRESULT CButton_UI::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pickupUI.png", &m_apTexture[TYPE_PICKUP]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/turn.png", &m_apTexture[TYPE_SPIN]);

	return S_OK;
}
//----------------------------------------------------------------
// テクスチャ破棄
//----------------------------------------------------------------
void CButton_UI::Unload(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			// テクスチャRelease
			m_apTexture[nCnt]->Release();

			// m_pTextureをNULLに
			m_apTexture[nCnt] = NULL;
		}
	}
}
//----------------------------------------------------------------
// 初期化
//----------------------------------------------------------------
HRESULT CButton_UI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	// タイプ代入
	m_Type = nType;
	// 初期化
	CScene2D::Init();
	// 位置座標設定
	SetPosition(pos);
	// サイズ設定
	SetSize(size);
	// 向きの設定
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// 色設定
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	// テクスチャ受け渡し
	BindTexture(m_apTexture[m_Type]);

	return S_OK;
}
//----------------------------------------------------------------
// 終了
//----------------------------------------------------------------
void CButton_UI::Uninit(void)
{
	// 終了
	CScene2D::Uninit();
}
//----------------------------------------------------------------
// 更新
//----------------------------------------------------------------
void CButton_UI::Update(void)
{
	// 更新
	CScene2D::Update();
	// m_bUseがfalseの場合
	if (m_bUse == false)
	{
		// 終了
		Uninit();
		return;
	}
}
//----------------------------------------------------------------
// 描画
//----------------------------------------------------------------
void CButton_UI::Draw(void)
{
	// 描画
	CScene2D::Draw();
}
//----------------------------------------------------------------
// 使用判定
//----------------------------------------------------------------
void CButton_UI::SetbUse(bool bUse)
{
	// 判定代入
	m_bUse = bUse;
}