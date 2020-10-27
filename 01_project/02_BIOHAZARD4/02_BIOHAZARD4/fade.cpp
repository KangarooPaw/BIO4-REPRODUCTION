#include "fade.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;
CFade::FADE CFade::m_fade = FADE_NONE;
CManager::MODE CFade::m_mode = CManager::MODE_NONE;

CFade::CFade(int nPriority) :CScene2D(nPriority)
{
	m_TexPos = 0;
	m_nFade = 0;
}

CFade::~CFade()
{
}

HRESULT CFade::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"data/TEXTURES/fade.jpg",					// ファイルの名前
		&m_pTexture);
	return S_OK;
}

void CFade::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

HRESULT CFade::Init(void)
{
	SetPosition(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f));
	SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	SetAlpha(m_nFade);
	BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_FADE);
	CScene2D::Init();

	return S_OK;
}

void CFade::Uninit(void)
{
	CScene2D::Uninit();
}

void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			FadeIn();
		}
		else if (m_fade == FADE_OUT)
		{
			FadeOut();
		}
	}
}

void CFade::Draw(void)
{
	CScene2D::Draw();
}

void CFade::SetFade(CManager::MODE mode)
{
	m_fade = FADE_IN;
	m_mode = mode;
	SetUpdateStop(true);
}

void CFade::FadeIn(void)
{
	m_nFade += 4;
	if (m_nFade >= 255)
	{
		m_nFade = 255;
		m_fade = FADE_OUT;
		GetManager()->SetMode(m_mode);
		return;
	}
	SetAlpha(m_nFade);
	CScene2D::Update();
}

void CFade::FadeOut(void)
{	
	m_nFade -= 4;
	if (m_nFade <= 0)
	{
		m_nFade = 0;
		m_fade = FADE_NONE;
		SetUpdateStop(false);
		return;
	}
	SetAlpha(m_nFade);
	CScene2D::Update();
}