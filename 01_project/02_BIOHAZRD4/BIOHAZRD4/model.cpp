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
#include "model.h"

//----------------------------------------
//�ÓI�����o�ϐ�
//----------------------------------------
LPD3DXMESH CModel::m_pMesh = NULL;
LPD3DXBUFFER CModel::m_pBuffMat = NULL;
DWORD CModel::m_nNumMat = 0;

//----------------------------------------
//�C���N�������g
//----------------------------------------
CModel::CModel()
{

}

//----------------------------------------
//�f�N�������g
//----------------------------------------
CModel::~CModel()
{

}

//----------------------------------------
//��������
//----------------------------------------
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pModel;
	pModel = new CModel;
	pModel->m_pos = pos;
	pModel->m_rot = rot;
	pModel->Init();
	return pModel;
}

//----------------------------------------
//���f���̓ǂݍ���
//----------------------------------------
HRESULT CModel::Load(void)
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

	return E_NOTIMPL;
}

//----------------------------------------
//���f���̔j��
//----------------------------------------
void CModel::Unload(void)
{
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CModel::Init(void)
{	
	return S_OK;
}

//----------------------------------------
//�I������
//----------------------------------------
void CModel::Uninit(void)
{
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	CScene3d::Uninit();
}

//----------------------------------------
//�X�V����
//----------------------------------------
void CModel::Update(void)
{
	//�R���g���[���[�̎擾����
	DIJOYSTATE pStick;
	CInputJoystick *pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 pJoystickDevice = CInputJoystick::GetDevice();
	if (pJoystickDevice != NULL)
	{
		pJoystickDevice->Poll();
		pJoystickDevice->GetDeviceState(sizeof(DIJOYSTATE), &pStick);
	}
	//--------------------------
	//�ړ�
	//--------------------------
	//���X�e�B�b�N�����ɓ|��
	if (pStick.lX <= -500)
	{
		m_rot.x -= 0.01f;
	}
	//���X�e�B�b�N���E�ɓ|��
	if (pStick.lX >= 500)
	{
		m_rot.x += 0.01f;
	}
	//���X�e�B�b�N��O�ɓ|��	
	if (pStick.lY <= -500)
	{
		m_pos.z -= 0.5f;
	}
	//���X�e�B�b�N�����ɓ|��
	if (pStick.lY >= 500)
	{
		m_pos.z += 0.5f;
	}
}

//----------------------------------------
//�`�揈��
//----------------------------------------
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL*pMat;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.x, m_rot.y, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		m_pMesh->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);
}
