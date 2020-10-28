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
#include "player.h"
#include "bullet.h"

//----------------------------------------
//静的メンバ変数
//----------------------------------------
LPD3DXMESH CPlayer::m_pMesh[MAX_PLAYER_PARTS] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[MAX_PLAYER_PARTS] = {};
DWORD CPlayer::m_nNumMat[MAX_PLAYER_PARTS] = {};
CPlayer::MODELPARENT CPlayer::m_modelParent[MAX_PLAYER_PARTS] = {
	{ "data/MODEL/PLAYER/body.x" },			// 上半身
	{ "data/MODEL/PLAYER/bodyUnder.x" },	// 下半身
	{ "data/MODEL/PLAYER/head.x" },			// 頭
	{ "data/MODEL/PLAYER/legLeft.x" },		// 左足
	{ "data/MODEL/PLAYER/legMomoLeft.x" },	// 左もも
	{ "data/MODEL/PLAYER/legRight.x" },		// 右足
	{ "data/MODEL/PLAYER/legMomoRight.x" }, // 右もも
	{ "data/MODEL/PLAYER/upArmLeft.x" },    // 左上腕
	{ "data/MODEL/PLAYER/downArmLeft.x" },   // 左前腕
	{ "data/MODEL/PLAYER/handLeft.x" },	    // 左手
	{ "data/MODEL/PLAYER/upArmRight.x" },    // 右上腕
	{ "data/MODEL/PLAYER/downArmRight.x" }, // 右前腕
	{ "data/MODEL/PLAYER/handRight.x" },    // 右手
};

//----------------------------------------
//インクリメント
//----------------------------------------
CPlayer::CPlayer(int nPriority) :CModelhierarchy(nPriority)
{

}

//----------------------------------------
//デクリメント
//----------------------------------------
CPlayer::~CPlayer()
{

}

//----------------------------------------
//生成処理
//----------------------------------------
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->SetPlayer(pos, rot, size);
	pPlayer->Init();
	return pPlayer;
}

//----------------------------------------
//モデルの読み込み
//----------------------------------------
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
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

	return S_OK;
}

//----------------------------------------
//モデルの破棄
//----------------------------------------
void CPlayer::Unload(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
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
	}
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CPlayer::Init(void)
{
	for (int nCount = 0; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		CModelhierarchy::BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], nCount - 1);
	}

	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CPlayer::Uninit(void)
{
	CModelhierarchy::Uninit();
}

//----------------------------------------
//更新処理
//----------------------------------------
void CPlayer::Update(void)
{
	//コントローラーの取得処理
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	// Xボタンを押したら弾を発射
	if (pInputJoystick->GetJoystickTrigger(CInputJoystick::BUTTON_X))
	{
		CBullet::Create(D3DXVECTOR3(m_pos.x + cosf(m_rot.x), m_pos.y + 20.0f, m_pos.z + sinf(m_rot.x)), D3DXVECTOR3(20.0f, 0.0f, 20.0f),
			D3DXVECTOR3(-sinf(m_rot.x)*2.0f, 0, -cosf(m_rot.x)*2.0f), 100, 10, CBullet::BULLETTYPE_PLAYER);
	}
	//--------------------------
	//移動
	//--------------------------
	if (pStick.lX <= -500)
	{
		m_rot.x -= D3DXToRadian(1);
	}
	//左スティックを右に倒す
	if (pStick.lX >= 500)
	{
		m_rot.x += D3DXToRadian(1);
	}
	//左スティックを前に倒す	
	if (pStick.lY <= -500)
	{
		m_pos.x += -sin(m_rot.x)*1.0f;
		m_pos.z += -cos(m_rot.x)*1.0f;
	}
	//左スティックを後ろに倒す
	if (pStick.lY >= 500)
	{
		m_pos.x += sin(m_rot.x)*1.0f;
		m_pos.z += cos(m_rot.x)*1.0f;
	}
	SetModel(m_pos, m_rot);
	CModelhierarchy::Update();
}

//----------------------------------------
//描画処理
//----------------------------------------
void CPlayer::Draw(void)
{
	CModelhierarchy::Draw();
}

//----------------------------------------
//初期設定
//----------------------------------------
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;//場所
	m_rot = rot;//角度
	m_size = size;//大きさ
	SetModel(pos, rot);//モデルの設定
	SetObjType(OBJTYPE_PLAYER);//オブジェクトタイプの設定
}
