//****************************************
//���f������
//****************************************

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "skybox.h"
#include "model.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CSkyBox::m_pMesh = NULL;
LPD3DXBUFFER CSkyBox::m_pBuffMat = NULL;
DWORD CSkyBox::m_nNumMat = NULL;
D3DXMATRIX CSkyBox::m_mtxWorld = {};	 // �s��v�Z�p
char* CSkyBox::m_apFileName = { "data/MODEL/MAP/sky.x" };// �}�b�v
LPDIRECT3DTEXTURE9 CSkyBox::m_pTexture[MAX_MATERIAL] = {};

//----------------------------------------
//�C���N�������g
//----------------------------------------
CSkyBox::CSkyBox(int nPriority) :CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pModel = NULL;
}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CSkyBox::~CSkyBox()
{
}

//----------------------------------------
//��������
//----------------------------------------
CSkyBox * CSkyBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CSkyBox *pMap;
	pMap = new CSkyBox;
	pMap->Init();
	pMap->SetSky(pos, rot, size);
	return pMap;
}

//----------------------------------------
//���f���̓ǂݍ���
//----------------------------------------
HRESULT CSkyBox::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_apFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	);

	// �e�N�X�`���̓ǂݍ���
	LoadTexture();

	return E_NOTIMPL;
}

//----------------------------------------
//���f���̔j��
//----------------------------------------
void CSkyBox::Unload(void)
{
	// ���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		m_nNumMat = NULL;
	}
}

//----------------------------------------
// �e�N�X�`���̓ǂݍ���
//----------------------------------------
HRESULT CSkyBox::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �}�e���A���������o��
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// �g�p���Ă���e�N�X�`��������Γǂݍ���
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// �e�N�X�`���ǂݍ���
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat])))
			{
				return E_FAIL;
			}
		}
	}

	return E_NOTIMPL;
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CSkyBox::Init(void)
{
	// ���f���̐���
	m_pModel = CModel::Create();

	// ���f���̃o�C���h
	m_pModel->BindModel(m_pMesh, m_pBuffMat, m_nNumMat, 0);

	for (int nCntMat = 0; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// �e�N�X�`���̃o�C���h
		m_pModel->BindTexture(m_pTexture[nCntMat], nCntMat);
	}
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CSkyBox::Uninit(void)
{
	// ���f���N���X�̏I������
	m_pModel->Uninit();
	m_pModel = NULL;
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CSkyBox::Update(void)
{

}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CSkyBox::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	//m_pModel[nCount]->SetWorldMatrix(m_mtxWorld[nCount]);

	//�A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���f���N���X�̕`�揈��
	m_pModel->Draw();

	//�A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//----------------------------------------
//�����ݒ�
//----------------------------------------
void CSkyBox::SetSky(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos;				//�ꏊ
	m_rot = rot;				//�p�x
	m_size = size;				//�傫��
	SetObjType(OBJTYPE_SKYBOX); //�I�u�W�F�N�g�^�C�v�̐ݒ�
}
