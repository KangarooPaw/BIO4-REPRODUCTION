//--------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------
#include "scene.h"
#include "scene2d.h"

//--------------------------------
//�ÓI�����o�ϐ�
//--------------------------------
CScene *CScene::m_pTop[PRIORITY] = {};
CScene *CScene::m_pCur[PRIORITY] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nCount = 0;
int CScene::m_nNext = 0;

//--------------------------------
//�R���X�g���N�^
//--------------------------------
CScene::CScene(int nPriority)
{
			m_pNext = NULL;
			m_pPrev = NULL;
			//�g�b�v��NULL�̎�
			if (m_pTop[nPriority] == NULL)
			{
				m_pTop[nPriority] = this;
			}
			//�g�b�v��NULL����Ȃ��Ƃ�
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
//�R���X�g���N�^
//--------------------------------
CScene::~CScene()
{

}

//--------------------------------
//�I�u�W�F�N�g�^�C�v�ݒ�
//--------------------------------
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//--------------------------------
//�V�[���̎擾
//--------------------------------
CScene * CScene::GetScene(int nPriority)
{
	CScene *pScene = m_pTop[nPriority];

	// m_nNext�̕�������
	for (int nCount = 0; nCount < m_nNext; nCount++)
	{
		if (pScene != NULL)
		{
			// Next�̏��̕ێ�
			CScene *pSceneNext = pScene->m_pNext;

			// Next�̏���pScene�ɓ����
			pScene = pSceneNext;
		}
	}

	// m_nNext�̉��Z
	m_nNext++;

	// pScene��NULL�̎�
	if (pScene == NULL)
	{
		m_nNext = 0;
	}
	return pScene;
}

//--------------------------------
//�����[�X�����܂Ƃ�
//--------------------------------
void CScene::ReleaseAll(void)
{
	for (int nCountpriority = 0; nCountpriority < PRIORITY; nCountpriority++)
	{
		CScene *pScene = m_pTop[nCountpriority];
		CScene *pSceneNext = NULL;
		while (pScene != NULL)
		{
			//������O�ɕۑ����Ă���
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
//�X�V�����܂Ƃ�
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
//�`�揈��
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
//�����[�X����
//--------------------------------
void CScene::Release(void)
{
	if (m_bDeath == true)
	{
		delete this;
	}
	else
	{
		//�g�b�v����Ȃ��ꍇ
		if (m_pPrev != NULL)
		{
			//�O�̎������g�̎��ɂ���
			m_pPrev->m_pNext = m_pNext;
		}
		//�{�g������Ȃ��ꍇ
		if (m_pNext != NULL)
		{
			//���̑O�����g�̑O�ɂ���
			m_pNext->m_pPrev = m_pPrev;
		}
		//���g���g�b�v�Ȃ�
		if (this == m_pTop[m_nPriority])
		{
			//�����g�b�v�ɂ���
			m_pTop[m_nPriority] = m_pNext;
		}
		//���g���{�g���Ȃ�
		if (this == m_pCur[m_nPriority])
		{
			//�O���{�g���ɂ���
			m_pCur[m_nPriority] = m_pPrev;
		}
		//���S�t���O�𗧂Ă�
		m_bDeath = true;
	}
}