//=============================================================================
//
// ライフ処理 [life.cpp]
// Author : 林川紗梨夏
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "key.h"
#include <cmath>
#include "fade.h"
#include "game.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CKey::CKey(int nPriority) : CScene(nPriority)
{
	memset(m_apKeyUi, 0, sizeof(m_apKeyUi));
	m_nKey = 0;
	m_fSizeWidth = 0;
	m_fSizeHeight = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CKey::~CKey()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CKey::Init(void)
{
	SetObjType(CScene::OBJTYPE_NONE);

	for (int nCntNum = 0; nCntNum < MAX_KEY; nCntNum++)
	{
		m_apKeyUi[nCntNum] = CKeyUi::Create(D3DXVECTOR3(m_pos.x + (m_fSizeWidth * nCntNum), m_pos.y, 0.0f), m_fSizeWidth, m_fSizeHeight);
	}
	SetKeyUi(m_nKey);
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CKey::Uninit(void)
{
	for (int nCntNum = 0; nCntNum < MAX_KEY; nCntNum++)
	{
		if (m_apKeyUi[nCntNum] != NULL)
		{
			m_apKeyUi[nCntNum]->Uninit();
			delete m_apKeyUi[nCntNum];
			m_apKeyUi[nCntNum] = NULL;
		}
	}

	Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CKey::Update(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void CKey::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_KEY; nCntNum++)
	{
		if (m_apKeyUi[nCntNum] != NULL)
		{
			m_apKeyUi[nCntNum]->Draw();
		}
	}
}
//=============================================================================
// 生成処理
//=============================================================================
CKey * CKey::Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight)
{
	CKey *pKey = NULL;


		if (pKey == NULL)
		{
			pKey = new CKey;
			pKey->m_pos = pos;
			pKey->m_fSizeWidth = fSizeWidth;
			pKey->m_fSizeHeight = fSizeHeight;
			pKey->Init();
		}


	return pKey;
}
//=============================================================================
// ライフのセット処理
//=============================================================================
void CKey::SetKeyUi(int nLife)
{
	m_nKey = nLife;

	if (m_nKey <= MAX_KEY)
	{
		for (int nCntStar = m_nKey; nCntStar < MAX_KEY; nCntStar++)
		{
			m_apKeyUi[nCntStar]->SetKey(CKeyUi::TYPE_NOGLOW);//ライフの数以降の星を暗くする
		}
		for (int nCntStar = 0; nCntStar < m_nKey; nCntStar++) //ライフの数までの星を光らせる
		{
			m_apKeyUi[nCntStar]->SetKey(CKeyUi::TYPE_GLOW);
		}

	}
}