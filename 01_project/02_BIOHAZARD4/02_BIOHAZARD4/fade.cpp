#include "fade.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;
CFade::FADE CFade::m_fade = FADE_NONE;
//CManager::MODE CFade::m_mode = CManager::MODE_TITLE;

CFade::CFade()
{
	m_pScene2D = NULL;
	m_TexPos = 0;
	m_nFade = 255;

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
		"TEXTURE_FADE",					// ファイルの名前
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

CFade * CFade::Create(float nPosX, float nPosY)
{
	CFade *pFade;
	pFade = new CFade;
	pFade->Init();
	return pFade;
}

HRESULT CFade::Init()
{
	m_pScene2D = new CScene2D(0);
	m_pScene2D->Init();
	m_pScene2D->BindTexture(m_pTexture);
	m_pScene2D->SetObjType(m_pScene2D->OBJTYPE_FADE);

	return S_OK;
}

void CFade::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

}

void CFade::Update(void)
{

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			FadeIn();
		}
		if (m_fade == FADE_OUT)
		{
			FadeOut();
		}
	}	
	m_pScene2D->Update();
}

void CFade::Draw(void)
{
	m_pScene2D->Draw();
}

void CFade::SetFade(/*CManager::MODE mode*/)
{
	m_fade = FADE_IN;
	//m_mode = mode;
}

void CFade::FadeIn(void)
{
	m_nFade+=4;
	if (m_nFade >= 255)
	{
		m_nFade = 255;
		m_fade = FADE_OUT;
		//CManager::SetMode(m_mode);
	}	
	m_pScene2D->SetAlpha(m_nFade);
	m_pScene2D->Update();
}

void CFade::FadeOut(void)
{	
	m_nFade-=4;	
	if (m_nFade <=0)
	{
		m_nFade = 0;
		m_fade = FADE_NONE;
		
	}
	m_pScene2D->SetAlpha(m_nFade);
	m_pScene2D->Update();
}