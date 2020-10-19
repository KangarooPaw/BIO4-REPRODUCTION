#include "scene.h"
#include "scene2d.h"


CScene *CScene::m_pTop[PRIORITY] = {};
CScene *CScene::m_pCur[PRIORITY] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nCount = 0;
CScene::CScene(int nPriority)
{
			m_pNext = NULL;
			m_pPrev = NULL;
			//トップがNULLの時
			if (m_pTop[nPriority] == NULL)
			{
				m_pTop[nPriority] = this;
			}
			//トップがNULLじゃないとき
			else
			{
				m_pPrev = m_pCur[nPriority];
				m_pCur[nPriority]->m_pNext = this;
			}
			m_pNext = NULL;
			m_pCur[nPriority] = this;
			m_objType = OBJTYPE_NONE;
			m_nPriority = nPriority;
			m_bDeath = false;
			
}

CScene::~CScene()
{

}

void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}


CScene * CScene::GetScene(int nPriority)
{
	return  m_pCur[nPriority];
}

void CScene::ReleaseAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		CScene *pScene = m_pTop[nCountpriority];
		CScene *pSceneNext = NULL;
		while (pScene != NULL)
		{
			//消える前に保存しておく
			pSceneNext = pScene->m_pNext;
			pScene->Release();
			pScene = pSceneNext;
		}
	}
	for (int nCountPriority = 0; nCountPriority < PRIORITY; nCountPriority++)
	{
		CScene*pScene = m_pTop[nCountPriority];
		CScene*pSceneNext = NULL;
		while (pScene != NULL)
		{
			pSceneNext = pScene->m_pNext;
			if (pScene->m_bDeath == true)
			{
				pScene->Release();
			}
			pScene = pSceneNext;
		}
	}
}

void CScene::UpdateAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		CScene*pScene = m_pTop[nCountpriority];
		CScene *pSceneNext = NULL;
		while (pScene != NULL)
		{
			pSceneNext = pScene->m_pNext;
			pScene->Update();
			pScene = pSceneNext;
		}
	}
	for (int nCountPriority = 0; nCountPriority < PRIORITY; nCountPriority++)
	{
		CScene*pScene = m_pTop[nCountPriority];
		CScene*pSceneNext = NULL;
		while (pScene != NULL)
		{
			pSceneNext = pScene->m_pNext;
			if (pScene->m_bDeath == true)
			{
				pScene->Release();
			}
			pScene = pSceneNext;
		}
	}
}

void CScene::DrawAll(void)
{	
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		CScene*pScene = m_pTop[nCountpriority];
		CScene*pSceneNext = NULL;
		while (pScene != NULL)
		{
			pSceneNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pSceneNext;
		}
	}
}

void CScene::Release(void)
{
	if (m_bDeath == true)
	{
		delete this;
	}
	else
	{
		//トップじゃない場合
		if (m_pPrev != NULL)
		{
			//前の次を自身の次にする
			m_pPrev->m_pNext = m_pNext;
		}
		//ボトムじゃない場合
		if (m_pNext != NULL)
		{
			//次の前を自身の前にする
			m_pNext->m_pPrev = m_pPrev;
		}
		//自身がトップなら
		if (this == m_pTop[m_nPriority])
		{
			//次をトップにする
			m_pTop[m_nPriority] = m_pNext;
		}
		//自身がボトムなら
		if (this == m_pCur[m_nPriority])
		{
			//前をボトムにする
			m_pCur[m_nPriority] = m_pPrev;
		}
		//死亡フラグを立てる
		m_bDeath = true;
	}
}