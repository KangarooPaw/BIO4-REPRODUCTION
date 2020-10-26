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

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_POLYGON,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
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

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;        
	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,m_Alpha);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{	
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{

	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
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

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_Alpha);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_Alpha);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_Alpha);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_Alpha);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CScene2D::SetAnimation(int nPatternAnim)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f+(nPatternAnim*0.125f ), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f+(nPatternAnim*0.125f) , 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f+(nPatternAnim *0.125f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f+(nPatternAnim *0.125f) , 1.0f);
	pVtx += 4;
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CScene2D::SetAlpha(int alpha)
{
 	m_Alpha = alpha;
}

//=============================================================
// �V�[�����2D�|���S���̉�]���钸�_���W��ݒ�
//=============================================================
void CScene2D::SetRotVertex(float sizeX, float sizeY, float fAngle)
{
    // �ϐ��錾
    // �e���_
    D3DXVECTOR3 vertex1;
    D3DXVECTOR3 vertex2;
    D3DXVECTOR3 vertex3;
    D3DXVECTOR3 vertex4;

    //==========================================================================================================
    //�摜���A�摜�̒��S�����ɉ�]������
    //����̒��_
    vertex1.x = -(sizeX / 2)*cosf(fAngle)
        - (-(sizeY / 2))*sinf(fAngle);
    vertex1.y = -(sizeX / 2)*sinf(fAngle)
        + (-(sizeY / 2))*cosf(fAngle);
    vertex1.z = 0.0f;

    //�E��̒��_
    vertex2.x = (sizeX / 2)*cosf(fAngle)
        - (-(sizeY / 2))*sinf(fAngle);
    vertex2.y = (sizeX / 2)*sinf(fAngle)
        + (-(sizeY / 2))*cosf(fAngle);
    vertex2.z = 0.0f;

    //�����̒��_
    vertex3.x = -(sizeX / 2)*cosf(fAngle)
        - (sizeY / 2)*sinf(fAngle);
    vertex3.y = -(sizeX / 2)*sinf(fAngle)
        + (sizeY / 2)*cosf(fAngle);
    vertex3.z = 0.0f;

    //�E���̒��_
    vertex4.x = (sizeX / 2)*cosf(fAngle)
        - (sizeY / 2)*sinf(fAngle);
    vertex4.y = (sizeX / 2)*sinf(fAngle)
        + (sizeY / 2)*cosf(fAngle);
    vertex4.z = 0.0f;
    //==========================================================================================================

    VERTEX_2D *pVtx = NULL;	// ���_���ւ̃|�C���^

    // ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

   // ���_���W�̐ݒ�
    pVtx[0].pos = m_pos + vertex1;
    pVtx[1].pos = m_pos + vertex2;
    pVtx[2].pos = m_pos + vertex3;
    pVtx[3].pos = m_pos + vertex4;

    //���_�f�[�^���A�����b�N����
    m_pVtxBuff->Unlock();
}

void CScene2D::SetEnemyTex(float texX1, float texX2, float texY1, float texY2)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(texX1, texY1);
	pVtx[1].tex = D3DXVECTOR2(texX2, texY1);
	pVtx[2].tex = D3DXVECTOR2(texX1, texY2);
	pVtx[3].tex = D3DXVECTOR2(texX2, texY2);
	// ���_�o�b�t�@���A�����b�N����
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
