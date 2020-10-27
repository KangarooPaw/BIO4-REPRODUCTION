//--------------------------------
//インクルードファイル
//--------------------------------
#include "scene.h"
#include "scene2d.h"

//--------------------------------
//静的メンバ変数
//--------------------------------
CScene *CScene::m_pTop[PRIORITY] = {};
CScene *CScene::m_pCur[PRIORITY] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nCount = 0;
int CScene::m_nNext = 0;

//--------------------------------
//コンストラクタ
//--------------------------------
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

//--------------------------------
//コンストラクタ
//--------------------------------
CScene::~CScene()
{

}

//--------------------------------
//オブジェクトタイプ設定
//--------------------------------
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//--------------------------------
//シーンの取得
//--------------------------------
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

//--------------------------------
//リリース処理まとめ
//--------------------------------
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

//--------------------------------
//更新処理まとめ
//--------------------------------
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

//--------------------------------
//描画処理
//--------------------------------
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

//--------------------------------
//リリース処理
//--------------------------------
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