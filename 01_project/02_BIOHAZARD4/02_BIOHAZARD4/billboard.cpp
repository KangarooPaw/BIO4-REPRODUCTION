#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "billboard.h"
//---------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------
CBillboard::CBillboard(int nPriority) :  CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fScale = 0.0f;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);
	m_fTexX = 0.0f;
	m_fTexX2 = 1.0f;
	m_fTexY = 0.0f;
	m_fTexY2 = 1.0f;
	m_nAlpha = 0;
}
//---------------------------------------------
//�@�f�X�g���N�^
//---------------------------------------------
CBillboard::~CBillboard()
{
}
//---------------------------------------------
//�@������
//---------------------------------------------
HRESULT CBillboard::Init(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_3D *pVtx;
	//�X�P�[��1.0f
	m_fScale = 1.0f;
	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / 2), (m_size.y / 2), (m_size.z / 2)) * m_fScale;
	pVtx[1].pos = D3DXVECTOR3((+m_size.x / 2), (m_size.y / 2), (m_size.z / 2)) * m_fScale;
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / 2), (-m_size.y / 2), (m_size.z / 2)) * m_fScale;
	pVtx[3].pos = D3DXVECTOR3((+m_size.x / 2), (-m_size.y / 2), (m_size.z / 2)) * m_fScale;

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col ;
	pVtx[2].col = m_col ;
	pVtx[3].col = m_col ;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	//pVtx += 4;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//---------------------------------------------
//�@�I��
//---------------------------------------------
void CBillboard::Uninit(void)
{
	//�j��
	Release();
}
//---------------------------------------------
//�@�X�V
//---------------------------------------------
void CBillboard::Update(void)
{
	// ���_����ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-m_size.x / 2), (m_size.y / 2), (m_size.z / 2)) * m_fScale;
	pVtx[1].pos = D3DXVECTOR3((+m_size.x / 2), (m_size.y / 2), (m_size.z / 2)) * m_fScale;
	pVtx[2].pos = D3DXVECTOR3((-m_size.x / 2), (-m_size.y / 2), (m_size.z / 2)) * m_fScale;
	pVtx[3].pos = D3DXVECTOR3((+m_size.x / 2), (-m_size.y / 2), (m_size.z / 2)) * m_fScale;

	//�@���̐ݒ� //�ǂ����猩�Ă��Â��Ȃ�Ȃ��悤�ɂ��Ă܂�
	pVtx[0].nor = D3DXVECTOR3( 1 ,1, -1);
	pVtx[1].nor = D3DXVECTOR3( 1 ,1, -1);
	pVtx[2].nor = D3DXVECTOR3( 1 ,1, -1);
	pVtx[3].nor = D3DXVECTOR3( 1 ,1, -1);

	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	//pVtx += 4;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//---------------------------------------------
//�@�`��
//---------------------------------------------
void CBillboard::Draw(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�s��v�Z�p�̃}�g���N�X

	//���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlpha);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�Z�b�g�e�N�X�`��
	pDevice->SetTexture(0, m_pTexture);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�̋t�s��
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;
	// �������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x,
		m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld,
		&mtxTrans);
	
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);   //���l
	//�A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//���C�g�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//---------------------------------------------
//�@�ʒu���W�ݒ�
//---------------------------------------------
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	//���
	m_pos = pos;
}
//---------------------------------------------
//�@�����ݒ�
//---------------------------------------------
void CBillboard::SetRotation(D3DXVECTOR3 rot)
{
	//���
	m_rot = rot;
}
//---------------------------------------------
//�@�T�C�Y�ݒ�
//---------------------------------------------
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	//���
	m_size = size;
}
//---------------------------------------------
//�@�J���[�ݒ�
//---------------------------------------------
void CBillboard::SetColor(D3DXCOLOR col)
{
	//���
	m_col = col;
}
void CBillboard::SetTexture(float fTexX, float fTexY, float fTexX2, float fTexY2)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexX2 = fTexX2;
	m_fTexY2 = fTexY2;
}
//---------------------------------------------
//�@�g�嗦�ݒ�
//---------------------------------------------
void CBillboard::SetScale(float fScale)
{
	//���
	m_fScale = fScale;
}
//---------------------------------------------
//�@�e�N�X�`���󂯓n��
//---------------------------------------------
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//���
	m_pTexture = pTexture;
}
//---------------------------------------------
// �A���t�@�e�X�g�̐��l�ݒ�
//---------------------------------------------
void CBillboard::SetAlpha(int nAlpha)
{
	m_nAlpha = nAlpha;
}