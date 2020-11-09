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
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

CFade::~CFade()
{
}

HRESULT CFade::Init(void)
{
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
	SetPosition(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f));
	SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	BindTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_FADE);
	m_fade = FADE_IN;
	m_mode = mode;
	SetUpdateStop(true);
}

void CFade::FadeIn(void)
{
	//D3DXCOLOR color = GetColor();
	m_color.a += 0.02f;
	if (m_color.a >= 1.0f)
	{
		m_color.a = 1.0f;
		m_fade = FADE_OUT;
		GetManager()->SetMode(m_mode);
		return;
	}
	SetColor(m_color);
	CScene2D::Update();
}

void CFade::FadeOut(void)
{	
	//D3DXCOLOR color = GetColor();
	m_color.a -= 0.02f;
	if (m_color.a <= 0.0f)
	{
		m_color.a = 0.0f;
		m_fade = FADE_NONE;
		SetUpdateStop(false);
		return;
	}
	SetColor(m_color);
	CScene2D::Update();
}