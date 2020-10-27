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
LPD3DXMESH CPlayer::m_pMesh = NULL;
LPD3DXBUFFER CPlayer::m_pBuffMat = NULL;
DWORD CPlayer::m_nNumMat = 0;

//----------------------------------------
//インクリメント
//----------------------------------------
CPlayer::CPlayer(int nPriority) :CModel(nPriority)
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

	D3DXLoadMeshFromX("data/MODEL/playermodel_test001.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	);

	return S_OK;
}

//----------------------------------------
//モデルの破棄
//----------------------------------------
void CPlayer::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
}

//----------------------------------------
//初期化処理
//----------------------------------------
HRESULT CPlayer::Init(void)
{
	CModel::BindModel(m_pMesh, m_pBuffMat, m_nNumMat);
	return S_OK;
}

//----------------------------------------
//終了処理
//----------------------------------------
void CPlayer::Uninit(void)
{
	CModel::Uninit();
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
	if (pInputJoystick->GetJoystickTrigger(0))
	{
		CBullet::Create(D3DXVECTOR3(m_pos.x+ cosf(m_rot.x), m_pos.y+20.0f, m_pos.z+ sinf(m_rot.x) ), D3DXVECTOR3(20.0f, 0.0f, 20.0f),
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
	CModel::Update();
}

//----------------------------------------
//描画処理
//----------------------------------------
void CPlayer::Draw(void)
{
	CModel::Draw();
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
