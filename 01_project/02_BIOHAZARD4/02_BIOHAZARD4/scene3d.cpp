//--------------------------------------
//インクルードファイル
//--------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"

//--------------------------------------
//コンストラクタ
//--------------------------------------
CScene3d::CScene3d(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//--------------------------------------
//デストラクタ
//--------------------------------------
CScene3d::~CScene3d()
{
}

//--------------------------------------
//コンストラクタ
//--------------------------------------
CScene3d * CScene3d::Create(float nPosX, float nPosY)
{
	CScene3d *pScene3d;
	pScene3d = new CScene3d(0);

	pScene3d->Init();
	return pScene3d;

}

//--------------------------------------
//初期化処理
//--------------------------------------
HRESULT CScene3d::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice= CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_POLYGON,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_3D *pVtx = NULL;

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//場所の設定
	pVtx[0].pos = D3DXVECTOR3(- (m_size.x / 2),m_size.y, + (m_size.z / 2));
	pVtx[1].pos = D3DXVECTOR3(+ (m_size.x / 2),m_size.y, + (m_size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(- (m_size.x / 2),m_size.y, - (m_size.z / 2));
	pVtx[3].pos = D3DXVECTOR3(+ (m_size.x / 2),m_size.y, - (m_size.z / 2));

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

	//カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255,0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255,0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255,0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255,0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//--------------------------------------
//終了処理
//--------------------------------------
void CScene3d::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//--------------------------------------
//更新処理
//--------------------------------------
void CScene3d::Update(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx = NULL;

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//場所の設定
	pVtx[0].pos = D3DXVECTOR3(- (m_size.x / 2), m_pos.y,  + (m_size.z / 2));
	pVtx[1].pos = D3DXVECTOR3(+ (m_size.x / 2), m_pos.y,  + (m_size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(- (m_size.x / 2), m_pos.y,  - (m_size.z / 2));
	pVtx[3].pos = D3DXVECTOR3(+ (m_size.x / 2), m_pos.y,  - (m_size.z / 2));

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//--------------------------------------
//描画処理
//--------------------------------------
void CScene3d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->SetTexture(0, m_pTexture);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//================================================================================
//各種設定
//================================================================================
//----------------------------------------
//場所
//----------------------------------------
void CScene3d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//----------------------------------------
//角度
//----------------------------------------
void CScene3d::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//----------------------------------------
//サイズ
//----------------------------------------
void CScene3d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//----------------------------------------
//テクスチャ
//----------------------------------------
void CScene3d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}