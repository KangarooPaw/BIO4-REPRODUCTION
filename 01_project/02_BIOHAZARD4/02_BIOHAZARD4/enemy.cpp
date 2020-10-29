//****************************************
//���f������
//****************************************

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "enemy.h"
#include "motion.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CEnemy::m_pMesh[MAX_ENEMY_PARTS] = {};
LPD3DXBUFFER CEnemy::m_pBuffMat[MAX_ENEMY_PARTS] = {};
DWORD CEnemy::m_nNumMat[MAX_ENEMY_PARTS] = {};
CEnemy::MODELPARENT CEnemy::m_modelParent[MAX_ENEMY_PARTS] = {
    { "data/MODEL/ENEMY/body.x" },			// �㔼�g
    { "data/MODEL/ENEMY/bodyUnder.x" },	// �����g
    { "data/MODEL/ENEMY/head.x" },			// ��
    { "data/MODEL/ENEMY/legMomoLeft.x" },	// ������
    { "data/MODEL/ENEMY/legLeft.x" },		// ����
    { "data/MODEL/ENEMY/legMomoRight.x" }, // �E����
    { "data/MODEL/ENEMY/legRight.x" },		// �E��
    { "data/MODEL/ENEMY/upArmLeft.x" },    // ����r
    { "data/MODEL/ENEMY/downArmLeft.x" },  // ���O�r
    { "data/MODEL/ENEMY/handLeft.x" },	    // ����
    { "data/MODEL/ENEMY/upArmRight.x" },   // �E��r
    { "data/MODEL/ENEMY/downArmRight.x" }, // �E�O�r
    { "data/MODEL/ENEMY/handRight.x" },    // �E��
};


//----------------------------------------
//�C���N�������g
//----------------------------------------
CEnemy::CEnemy(int nPriority) :CModelhierarchy(nPriority)
{
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CEnemy::~CEnemy()
{

}

//----------------------------------------
//��������
//----------------------------------------
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
    CEnemy *pEnemy;
    pEnemy = new CEnemy;
    pEnemy->SetEnemy(pos, rot, size);
    pEnemy->Init();
    return pEnemy;
}

//----------------------------------------
//���f���̓ǂݍ���
//----------------------------------------
HRESULT CEnemy::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
    {
        // X�t�@�C���̓ǂݍ���
        D3DXLoadMeshFromX(m_modelParent[nCount].pFileName,
            D3DXMESH_SYSTEMMEM,
            pDevice,
            NULL,
            &m_pBuffMat[nCount],
            NULL,
            &m_nNumMat[nCount],
            &m_pMesh[nCount]
        );
    }

    return E_NOTIMPL;
}

//----------------------------------------
//���f���̔j��
//----------------------------------------
void CEnemy::Unload(void)
{
    for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
    {
        // ���b�V���̔j��
        if (m_pMesh[nCount] != NULL)
        {
            m_pMesh[nCount]->Release();
            m_pMesh[nCount] = NULL;
        }

        // �}�e���A���̔j��
        if (m_pBuffMat[nCount] != NULL)
        {
            m_pBuffMat[nCount]->Release();
            m_pBuffMat[nCount] = NULL;
        }

        if (m_nNumMat[nCount] != NULL)
        {
            m_nNumMat[nCount] = NULL;
        }
    }

}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CEnemy::Init(void)
{
    m_pMotion = CMotion::Create();
    m_pMotion->Load(LOAD_ENEMY_TEXT);
    m_pMotion->LoadMotion(MOTION_ENEMY_TEXT);

    for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
    {
        m_modelParent[nCount].nIndex = m_pMotion->GetIndex(nCount);
        m_modelParent[nCount].nParents = m_pMotion->GetParents(nCount);
        m_modelParent[nCount].pos = m_pMotion->GetPos(nCount);
        m_modelParent[nCount].rot = m_pMotion->GetRot(nCount);

        // ���f���q�G�����L�[�N���X�̃��f���̃p�[�c���Ƃ̐ݒ�
        CModelhierarchy::BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_modelParent[nCount].nParents);

        SetModelParts(m_modelParent[nCount].pos, m_modelParent[nCount].rot, nCount);
    }
    m_bChase = false;
    return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CEnemy::Uninit(void)
{
    // ���f���N���X�̏I������
    CModelhierarchy::Uninit();
    m_pMotion = NULL;
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CEnemy::Update(void)
{
    // ���f���N���X�̍X�V����
    CModelhierarchy::Update();

    // ���[�V�����̍X�V����
    m_pMotion->UpdatePlayerMotion();

    // ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
    for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
    {
		m_modelParent[nCount].pos = m_pMotion->GetPos(nCount);
		m_modelParent[nCount].rot = m_pMotion->GetRot(nCount);
    }

    // ���W�A��]�A�T�C�Y�̎󂯎��
    m_pos = GetPos();
    m_rot = GetRot();
    m_size = GetSize();

    // ���W�A��]�A�T�C�Y�̃Z�b�g
    SetModel(m_pos, m_rot, m_size);

    for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
    {
        // ���f���̃p�[�c���Ƃ̃Z�b�g
        SetModelParts(m_modelParent[nCount].pos, m_modelParent[nCount].rot, nCount);
    }
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CEnemy::Draw(void)
{
    // ���f���N���X�̕`�揈��
    CModelhierarchy::Draw();
}