#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"

CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_PolygonWidth = 0;
	m_PolygonHeight = 0;
	m_Alpha = 255;
	m_angleX = 1.0f;
	m_angleY = 1.0f;
}

CScene2D::~CScene2D()
{

}

CScene2D *CScene2D::Create(float nPosX, float nPosY)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D(3);
	
	pScene2D->Init();
	return pScene2D;
}

HRESULT CScene2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_POLYGON,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = m_pos.x - (m_size.x / 2);
	pVtx[0].pos.y = m_pos.y - (m_size.y / 2);
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + (m_size.x / 2);
	pVtx[1].pos.y = m_pos.y - (m_size.y / 2);
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - (m_size.x / 2);
	pVtx[2].pos.y = m_pos.y + (m_size.y / 2);
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + (m_size.x / 2);
	pVtx[3].pos.y = m_pos.y + (m_size.y / 2);
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;        
	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,m_Alpha);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{	
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{

	// 頂点情報を設定
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = m_pos.x - (m_size.x / 2)	;
	pVtx[0].pos.y = m_pos.y - (m_size.y / 2)	;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + (m_size.x / 2)	;
	pVtx[1].pos.y = m_pos.y - (m_size.y / 2)	;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - (m_size.x / 2)	;
	pVtx[2].pos.y = m_pos.y + (m_size.y / 2)	;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + (m_size.x / 2)	;
	pVtx[3].pos.y = m_pos.y + (m_size.y / 2)	;
	pVtx[3].pos.z = 0.0f;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_Alpha);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_Alpha);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_Alpha);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_Alpha);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CScene2D::SetAnimation(int nPatternAnim)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f+(nPatternAnim*0.125f ), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f+(nPatternAnim*0.125f) , 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f+(nPatternAnim *0.125f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f+(nPatternAnim *0.125f) , 1.0f);
	pVtx += 4;
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CScene2D::SetAlpha(int alpha)
{
 	m_Alpha = alpha;
}

//=============================================================
// シーン上の2Dポリゴンの回転する頂点座標を設定
//=============================================================
void CScene2D::SetRotVertex(float sizeX, float sizeY, float fAngle)
{
    // 変数宣言
    // 各頂点
    D3DXVECTOR3 vertex1;
    D3DXVECTOR3 vertex2;
    D3DXVECTOR3 vertex3;
    D3DXVECTOR3 vertex4;

    //==========================================================================================================
    //画像を、画像の中心を軸に回転させる
    //左上の頂点
    vertex1.x = -(sizeX / 2)*cosf(fAngle)
        - (-(sizeY / 2))*sinf(fAngle);
    vertex1.y = -(sizeX / 2)*sinf(fAngle)
        + (-(sizeY / 2))*cosf(fAngle);
    vertex1.z = 0.0f;

    //右上の頂点
    vertex2.x = (sizeX / 2)*cosf(fAngle)
        - (-(sizeY / 2))*sinf(fAngle);
    vertex2.y = (sizeX / 2)*sinf(fAngle)
        + (-(sizeY / 2))*cosf(fAngle);
    vertex2.z = 0.0f;

    //左下の頂点
    vertex3.x = -(sizeX / 2)*cosf(fAngle)
        - (sizeY / 2)*sinf(fAngle);
    vertex3.y = -(sizeX / 2)*sinf(fAngle)
        + (sizeY / 2)*cosf(fAngle);
    vertex3.z = 0.0f;

    //右下の頂点
    vertex4.x = (sizeX / 2)*cosf(fAngle)
        - (sizeY / 2)*sinf(fAngle);
    vertex4.y = (sizeX / 2)*sinf(fAngle)
        + (sizeY / 2)*cosf(fAngle);
    vertex4.z = 0.0f;
    //==========================================================================================================

    VERTEX_2D *pVtx = NULL;	// 頂点情報へのポインタ

    // 頂点データの範囲をロックし、頂点バッファへのポインタを取得
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

   // 頂点座標の設定
    pVtx[0].pos = m_pos + vertex1;
    pVtx[1].pos = m_pos + vertex2;
    pVtx[2].pos = m_pos + vertex3;
    pVtx[3].pos = m_pos + vertex4;

    //頂点データをアンロックする
    m_pVtxBuff->Unlock();
}

void CScene2D::SetEnemyTex(float texX1, float texX2, float texY1, float texY2)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(texX1, texY1);
	pVtx[1].tex = D3DXVECTOR2(texX2, texY1);
	pVtx[2].tex = D3DXVECTOR2(texX1, texY2);
	pVtx[3].tex = D3DXVECTOR2(texX2, texY2);
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CScene2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}
