//=============================================================================
//
// ���[�V�����̏��� [motion.cpp]
// Author : �ɓ��z��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "motion.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMotion::CMotion()
{
	for (int nCount = 0; nCount < 13; nCount++)
	{
		m_modelParent[nCount].m_nIndex = 0;
		m_modelParent[nCount].m_nParents = 0;
		m_modelParent[nCount].m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int nCountMotion = 0; nCountMotion < MOTION_MAX; nCountMotion++)
	{
		m_motion[nCountMotion].m_nLoop = false;
		m_motion[nCountMotion].m_nNumKey = 0;
		
		for (int nCountKey = 0; nCountKey < MOTION_KEYSET_MAX; nCountKey++)
		{
			m_motion[nCountMotion].m_KeyInfo[nCountKey].m_nFrame = 0;
			for (int nCountParts = 0; nCountParts < MAX_PARTS; nCountParts++)
			{
				m_motion[nCountMotion].m_KeyInfo[nCountKey].m_pos[nCountParts] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_motion[nCountMotion].m_KeyInfo[nCountKey].m_rot[nCountParts] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	m_motionState = MOTION_IDLE;
	m_motionOldState = MOTION_IDLE;

	m_nFreme = 0;
	m_nCntKey = 1;

	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_NumPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_NumRot[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_NumRotDest[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMotion::~CMotion()
{

}

//=============================================================================
// ���[�V�����N���X�̃C���X�^���X����
//=============================================================================
CMotion * CMotion::Create()
{
	CMotion *pMotion;
	pMotion = new CMotion;

	return pMotion;
}

//=============================================================================
// ���[�V�����N���X�̃��[�V�����̓ǂݍ���
//=============================================================================
void CMotion::LoadMotion(const char *cText)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	// �ϐ��錾
	int  nCntLoad = 0;
	int	 nCntKey = 0;
	int	 nCntMotion = 0;

	char cReedText[1024];	// �����Ƃ��ēǂݎ��p
	char cHeadText[1024];	//
	char cDie[1024];

	// �t�@�C���J
	pFile = fopen(cText, "r");

	// �J����
	if (pFile != NULL)
	{
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReedText, sizeof(cReedText), pFile);
			sscanf(cReedText, "%s", &cHeadText);
		}

		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReedText, sizeof(cReedText), pFile);
				sscanf(cReedText, "%s", &cHeadText);

				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{

					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReedText, sizeof(cReedText), pFile);
						sscanf(cReedText, "%s", &cHeadText);

						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_motion[nCntMotion].m_nLoop);
						}

						if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_motion[nCntMotion].m_nNumKey);
						}

						//if (strcmp(cHeadText, "COLLISION") == 0)
						//{
						//	sscanf(cReedText, "%s %s %d %f %f %f %f %d %d", &cDie, &cDie, &g_PlayerCollision.nPartsInfo, &g_PlayerCollision.CollisionPos.x, &g_PlayerCollision.CollisionPos.y, &g_PlayerCollision.CollisionPos.z, &g_PlayerCollision.fLength, &g_PlayerCollision.nFirstFlame[nCntMotion], &g_PlayerCollision.nLastFlame);
						//}

						if (strcmp(cHeadText, "KEYSET") == 0)
						{

							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReedText, sizeof(cReedText), pFile);
								sscanf(cReedText, "%s", &cHeadText);

								if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_motion[nCntMotion].m_KeyInfo[nCntKey].m_nFrame);
								}
								if (strcmp(cHeadText, "KEY") == 0)
								{
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReedText, sizeof(cReedText), pFile);
										sscanf(cReedText, "%s", &cHeadText);

										if (strcmp(cHeadText, "POS") == 0)
										{
											sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_pos[nCntLoad].x,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_pos[nCntLoad].y,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_pos[nCntLoad].z);
										}

										if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_rot[nCntLoad].x,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_rot[nCntLoad].y,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_rot[nCntLoad].z);
										}
									}
									nCntLoad++;
								}
							}
							nCntLoad = 0;
							nCntKey++;
						}
					}
					nCntKey = 0;
					nCntMotion++;
				}
			}
			// �t�@�C����
			fclose(pFile);
		}
		// �J���Ȃ�
		else
		{
			printf("�J����܂���ł���\n");
		}
	}
}

//=============================================================================
// ���[�V�����N���X�̏����l�̓ǂݍ���
//=============================================================================
void CMotion::Load(const char *cText)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	// �ϐ��錾
	int  nCntLoad = 0;	 // ������ǂݍ��񂾃J�E���g
	char cReedText[128]; // �����Ƃ��ēǂݎ��p
	char cHeadText[256]; // �����̔��ʗp
	char cDie[128];		 // �g��Ȃ�����

	// �t�@�C�����J��
	pFile = fopen(cText, "r");

	// �J����
	if (pFile != NULL)
	{
		// CHARACTERSET�̕�����������܂�
		while (strcmp(cHeadText, "CHARACTERSET") != 0)
		{
			// �e�L�X�g����cReedText���������󂯎��
			fgets(cReedText, sizeof(cReedText), pFile);

			// cReedText��cHeadText�Ɋi�[
			sscanf(cReedText, "%s", &cHeadText);
		}

		// cHeadText��CHARACTERSET�̎�
		if (strcmp(cHeadText, "CHARACTERSET") == 0)
		{
			// cHeadText��END_CHARACTERSET�ɂȂ�܂�
			while (strcmp(cHeadText, "END_CHARACTERSET") != 0)
			{
				// �e�L�X�g����cReedText���������󂯎��
				fgets(cReedText, sizeof(cReedText), pFile);

				// cReedText��cHeadText�Ɋi�[
				sscanf(cReedText, "%s", &cHeadText);

				// cHeadText�����s�̎�
				if (strcmp(cHeadText, "\n") == 0)
				{
				}
				// cHeadText��PARTSSET�̎�
				else if (strcmp(cHeadText, "PARTSSET") == 0)
				{
					// cHeadText��END_PARTSSET�ɂȂ�܂�
					while (strcmp(cHeadText, "END_PARTSSET") != 0)
					{
						// �e�L�X�g����cReedText���������󂯎��
						fgets(cReedText, sizeof(cReedText), pFile);

						// cReedText��cHeadText�Ɋi�[
						sscanf(cReedText, "%s", &cHeadText);

						// cHeadText��INDEX�ɂȂ�܂�
						if (strcmp(cHeadText, "INDEX") == 0)
						{
							// �e�L�X�g��INDEX�̒l��m_nIndex�Ɋi�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_modelParent[nCntLoad].m_nIndex);
						}

						// cHeadText��PARENT�ɂȂ�܂�
						if (strcmp(cHeadText, "PARENT") == 0)
						{
							// �e�L�X�g��PARENT�̒l��m_nParents�Ɋi�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_modelParent[nCntLoad].m_nParents);
						}

						// cHeadText��POS�ɂȂ�܂�
						if (strcmp(cHeadText, "POS") == 0)
						{
							// �e�L�X�g��POS�̒l��m_posOrigin�Ɋi�[
							sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
								&m_modelParent[nCntLoad].m_posOrigin.x,
								&m_modelParent[nCntLoad].m_posOrigin.y,
								&m_modelParent[nCntLoad].m_posOrigin.z);

							// m_posOrigin�̒l��m_pos�ɑ��
							m_modelParent[nCntLoad].m_pos = m_modelParent[nCntLoad].m_posOrigin;
						}

						// cHeadText��ROT�ɂȂ�܂�
						if (strcmp(cHeadText, "ROT") == 0)
						{
							// �e�L�X�g��ROT�̒l��m_rot�Ɋi�[
							sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
								&m_modelParent[nCntLoad].m_rot.x,
								&m_modelParent[nCntLoad].m_rot.y,
								&m_modelParent[nCntLoad].m_rot.z);
						}
					}
					// �J�E���g���Z
					nCntLoad++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}

	// �J���Ȃ�
	else
	{
		printf("�J����܂���ł���\n");
	}
}

//=============================================================================
// ���[�V�����N���X�̍X�V����
//=============================================================================
void CMotion::UpdatePlayerMotion(void)
{
	// ���[�V������1F�O�̃��[�V�����ƈ������
	if (m_motionOldState != m_motionState) {
		m_nFreme = 0;
		m_nCntKey = 0;
	}
	for (int nCntMotion = 0; nCntMotion < MAX_PARTS; nCntMotion++)
	{
		//�t���[���J�n���ɁA�ύX��̉�]�̒l��ʒu�̒l�Ȃǂ�ݒ�
		if (m_nFreme == 0)
		{
			m_NumPos[nCntMotion] = ((m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_pos[nCntMotion] -
				(m_modelParent[nCntMotion].m_pos - m_modelParent[nCntMotion].m_posOrigin))
				/ float(m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_nFrame));
			//m_NumPos[nCntMotion].x = ((m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_pos[nCntMotion].x -
			//	(m_modelParent[nCntMotion].m_pos.x - m_modelParent[nCntMotion].m_posOrigin.x)) 
			//	/ float(m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_nFrame));
			//m_NumPos[nCntMotion].y = ((m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_pos[nCntMotion].y -
			//	(m_modelParent[nCntMotion].m_pos.y - m_modelParent[nCntMotion].m_posOrigin.y)) 
			//	/ float(m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_nFrame));
			//m_NumPos[nCntMotion].z = ((m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_pos[nCntMotion].z -
			//	(m_modelParent[nCntMotion].m_pos.z - m_modelParent[nCntMotion].m_posOrigin.z)) 
			//	/ float(m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_nFrame));

			m_NumRotDest[nCntMotion] =
				m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_rot[nCntMotion] - m_modelParent[nCntMotion].m_rot;
			m_NumRot[nCntMotion] = (m_NumRotDest[nCntMotion] / float(m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_nFrame));
		}

		// �ύX��̉�]�̒l��ʒu�̒l�����Z
		m_modelParent[nCntMotion].m_pos += m_NumPos[nCntMotion];
		m_modelParent[nCntMotion].m_rot += m_NumRot[nCntMotion];
	}

	// ���݂̃��[�V�����̋L�^
	m_motionOldState = m_motionState;

	// ���[�v����Ƃ�
	if (m_nFreme >= m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_nFrame && m_motion[m_motionState].m_nLoop == 1)
	{
		m_nFreme = 0;
		m_nCntKey++;

		// �L�[���L�^����Ă���L�[���傫���Ȃ�����
		if (m_nCntKey >= m_motion[m_motionState].m_nNumKey)
		{
			m_nCntKey = 0;
		}

	}
	// ���[�v���Ȃ��Ƃ�
	else if (m_nFreme >= m_motion[m_motionState].m_KeyInfo[m_nCntKey].m_nFrame && m_motion[m_motionState].m_nLoop == 0)
	{
		m_nFreme = 0;
		m_nCntKey++;

		// �L�[���L�^����Ă���L�[���傫���Ȃ�����
		if (m_nCntKey >= m_motion[m_motionState].m_nNumKey)
		{
			for (int nCntMotion = 0; nCntMotion < MAX_PARTS; nCntMotion++)
			{
				m_NumPos[nCntMotion] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_NumRot[nCntMotion] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			//		g_nCntKey = g_aPMotion[g_MotionState].nNum_Key;
			m_motionState = MOTION_IDLE;
		}
	}
	else
	{
		m_nFreme++;
	}
}

//=============================================================================
// ���[�V�����N���X�̂ǂ̃��[�V�������Đ����邩�̃Z�b�g
//=============================================================================
void CMotion::SetMotion(MOTIONSTATE motionstate)
{
	m_motionState = motionstate;
}