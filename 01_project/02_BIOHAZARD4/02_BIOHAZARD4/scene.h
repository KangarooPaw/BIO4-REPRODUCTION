#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"
//�I�u�W�F�N�g�N���X
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_FENCE,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_SCORE,
		OBJTYPE_NUMBER,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority=2);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority);

	//�������z�֐�
	virtual HRESULT Init(void)=0;	//����������
	virtual void Uninit(void)=0;	//�I������
	virtual void Update(void)=0;	//�X�V����
	virtual void Draw(void)=0;		//�`�揈��

	static void UpdateAll(void);	//�X�V�܂Ƃ�
	static void DrawAll(void);		//�`��܂Ƃ�
	static void ReleaseAll(void);	//�I���܂Ƃ�

protected:	
	void Release(void);

private:
	OBJTYPE m_objType;							//�I�u�W�F�N�g�̎��
	static CScene *m_pTop[PRIORITY];//�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur[PRIORITY];//���݂̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pPrev;//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;//���̃I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumAll;
	int m_nPriority;
	int m_nID;
	static int	m_nCount;
	static int m_nNext;
	static bool m_bRelease;
	bool m_bDeath;
};

#endif // !_RENDERER_H_