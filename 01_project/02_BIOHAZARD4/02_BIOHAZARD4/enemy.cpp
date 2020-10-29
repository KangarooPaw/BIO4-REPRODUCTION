//****************************************
//モデル処理
//****************************************

//----------------------------------------
//インクルードファイル
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "enemy.h"
#include "motion.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CEnemy::m_pMesh[MAX_ENEMY_PARTS] = {};
LPD3DXBUFFER CEnemy::m_pBuffMat[MAX_ENEMY_PARTS] = {};
DWORD CEnemy::m_nNumMat[MAX_ENEMY_PARTS] = {};
CEnemy::MODELPARENT CEnemy::m_modelParent[MAX_ENEMY_PARTS] = {
    { "data/MODEL/ENEMY/body.x" },			// 上半身
    { "data/MODEL/ENEMY/bodyUnder.x" },	// 下半身
    { "data/MODEL/ENEMY/head.x" },			// 頭
    { "data/MODEL/ENEMY/legMomoLeft.x" },	// 左もも
    { "data/MODEL/ENEMY/legLeft.x" },		// 左足
    { "data/MODEL/ENEMY/legMomoRight.x" }, // 右もも
    { "data/MODEL/ENEMY/legRight.x" },		// 右足
    { "data/MODEL/ENEMY/upArmLeft.x" },    // 左上腕
    { "data/MODEL/ENEMY/downArmLeft.x" },  // 左前腕
    { "data/MODEL/ENEMY/handLeft.x" },	    // 左手
    { "data/MODEL/ENEMY/upArmRight.x" },   // 右上腕
    { "data/MODEL/ENEMY/downArmRight.x" }, // 右前腕
    { "data/MODEL/ENEMY/handRight.x" },    // 右手
};


//----------------------------------------
//インクリメント
//----------------------------------------
CEnemy::CEnemy(int nPriority) :CModelhierarchy(nPriority)
{
    m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//----------------------------------------
//デクリメント
//----------------------------------------
CEnemy::~CEnemy()
{

}

//----------------------------------------
//生成処理
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
//モデルの読み込み
//----------------------------------------
HRESULT CEnemy::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
    {
        // Xファイルの読み込み
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
//モデルの破棄
//----------------------------------------
void CEnemy::Unload(void)
{
    for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
    {
        // メッシュの破棄
        if (m_pMesh[nCount] != NULL)
        {
            m_pMesh[nCount]->Release();
            m_pMesh[nCount] = NULL;
        }

        // マテリアルの破棄
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
//初期化処理
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

        // モデルヒエラルキークラスのモデルのパーツごとの設定
        CModelhierarchy::BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_modelParent[nCount].nParents);

        SetModelParts(m_modelParent[nCount].pos, m_modelParent[nCount].rot, nCount);
    }
    m_bChase = false;
    return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CEnemy::Uninit(void)
{
    // モデルクラスの終了処理
    CModelhierarchy::Uninit();
    m_pMotion = NULL;
}

//----------------------------------------
//更新処理
//----------------------------------------
void CEnemy::Update(void)
{
    // モデルクラスの更新処理
    CModelhierarchy::Update();

    // モーションの更新処理
    m_pMotion->UpdatePlayerMotion();

    // モデルのパーツごとの座標と回転を受け取る
    for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
    {
		m_modelParent[nCount].pos = m_pMotion->GetPos(nCount);
		m_modelParent[nCount].rot = m_pMotion->GetRot(nCount);
    }

    // 座標、回転、サイズの受け取り
    m_pos = GetPos();
    m_rot = GetRot();
    m_size = GetSize();

    // 座標、回転、サイズのセット
    SetModel(m_pos, m_rot, m_size);

    for (int nCount = 0; nCount < MAX_ENEMY_PARTS; nCount++)
    {
        // モデルのパーツごとのセット
        SetModelParts(m_modelParent[nCount].pos, m_modelParent[nCount].rot, nCount);
    }
}

//----------------------------------------
//描画処理
//----------------------------------------
void CEnemy::Draw(void)
{
    // モデルクラスの描画処理
    CModelhierarchy::Draw();
}