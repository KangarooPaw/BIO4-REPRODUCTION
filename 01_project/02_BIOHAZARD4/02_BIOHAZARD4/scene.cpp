#include "scene.h"
#include "scene2d.h"


CScene *CScene::m_pTop[PRIORITY] = {};
CScene *CScene::m_pCur[PRIORITY] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nCount = 0;
int CScene::m_nNext = 0;
bool CScene::m_bUpdateStop = false;

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
	CScene *pScene = m_pTop[nPriority];

	// m_nNextの分だけ回す
	for (int nCount = 0; nCount < m_nNext; nCount++)
	{
		if (pScene != NULL)
		{
			// Nextの情報の保持
			CScene *pSceneNext = pScene->m_pNext;

			// Nextの情報をpSceneに入れる
			pScene = pSceneNext;
		}
	}

	// m_nNextの加算
	m_nNext++;

	// pSceneがNULLの時
	if (pScene == NULL)
	{
		m_nNext = 0;
	}

	return pScene;
}

void CScene::ReleaseAll(void)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			//終了処理
			CScene *pSave = pScene->m_pNext;
			pScene->Release();
			pScene = pSave;
		}
	}

	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				if (pScene->m_pPrev != NULL)
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				if (pScene->m_pNext != NULL)
				{
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				if (m_pTop[nCount] == pScene)
				{
					m_pTop[nCount] = pScene->m_pNext;
				}

				if (m_pCur[nCount] == pScene)
				{
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//オブジェクトを破棄
				delete pScene;
			}

			pScene = pSave;
		}
	}
}

void CScene::DesignationReleaseAll(OBJTYPE type)
{
	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		if (nCount != type)
		{
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				//終了処理
				CScene *pSave = pScene->m_pNext;
				pScene->Release();
				pScene = pSave;
			}
		}
	}

	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				if (pScene->m_pPrev != NULL)
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				if (pScene->m_pNext != NULL)
				{
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				if (m_pTop[nCount] == pScene)
				{
					m_pTop[nCount] = pScene->m_pNext;
				}

				if (m_pCur[nCount] == pScene)
				{
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//オブジェクトを破棄
				delete pScene;
			}

			pScene = pSave;
		}
	}
}

void CScene::SetUpdateStop(bool bUpdateStop)
{
	m_bUpdateStop = bUpdateStop;
}

void CScene::UpdateAll(void)
{
	if (m_bUpdateStop == false)
	{
		for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
		{
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				CScene *pSave = pScene->m_pNext;

				if (pScene->m_bDeath == false)
				{
					//更新処理
					pScene->Update();
				}

				pScene = pSave;
			}
		}
	}
	else
	{
		CScene *pScene = m_pTop[OBJTYPE_FADE];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == false)
			{
				//更新処理
				pScene->Update();
			}

			pScene = pSave;
		}
	}

	for (int nCount = 0; nCount < OBJTYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			CScene *pSave = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				if (pScene->m_pPrev != NULL)
				{
					pScene->m_pPrev->m_pNext = pScene->m_pNext;
				}

				if (pScene->m_pNext != NULL)
				{
					pScene->m_pNext->m_pPrev = pScene->m_pPrev;
				}

				if (m_pTop[nCount] == pScene)
				{
					m_pTop[nCount] = pScene->m_pNext;
				}

				if (m_pCur[nCount] == pScene)
				{
					m_pCur[nCount] = pScene->m_pPrev;
				}

				//オブジェクトを破棄
				delete pScene;
			}

			pScene = pSave;
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
	//死亡フラグを立てる
	m_bDeath = true;
}