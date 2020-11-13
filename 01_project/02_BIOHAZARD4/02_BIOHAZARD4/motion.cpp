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
	// ���f���p�[�c�̏�����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_modelParent[nCount].m_nIndex = 0;
		m_modelParent[nCount].m_nParents = 0;
		m_modelParent[nCount].m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���[�V�����̏�����
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

	// ���[�V�����̏�Ԃ�MOTION_IDLE��
	m_motionState = MOTION_IDLE;
	m_motionOldState = MOTION_IDLE;

	// �t���[�����ƃL�[���̏�����
	m_nFreme = 0;
	m_nCntKey = 1;

	// 
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
// ���[�V�����N���X�̏I������
//=============================================================================
void CMotion::Uninit(void)
{
	// ���f���p�[�c�̏�����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_modelParent[nCount].m_nIndex = 0;
		m_modelParent[nCount].m_nParents = 0;
		m_modelParent[nCount].m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_posOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_modelParent[nCount].m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���[�V�����̏�����
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

	// ���[�V�����̏�Ԃ�MOTION_IDLE��
	m_motionState = MOTION_IDLE;
	m_motionOldState = MOTION_IDLE;

	// �t���[�����ƃL�[���̏�����
	m_nFreme = 0;
	m_nCntKey = 1;

	// 
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_NumPos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_NumRot[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_NumRotDest[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// ���[�V�����N���X�̃��[�V�����̓ǂݍ���
//=============================================================================
void CMotion::LoadMotion(const char *cText)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	// �ϐ��錾
	int  nCntLoad = 0;		// �ǂݍ��񂾃J�E���g
	int	 nCntKey = 0;		// �L�[�̐��̃J�E���g
	int	 nCntMotion = 0;	// ���[�V�����̐��̃J�E���g
	char cReedText[NUM_TEXT];	// �����Ƃ��ēǂݎ��p
	char cHeadText[NUM_TEXT];	// �����̔��ʗp
	char cDie[NUM_TEXT];		// �g��Ȃ�����

	// �t�@�C�����J��
	pFile = fopen(cText, "r");

	// �J��������
	if (pFile != NULL)
	{
		// SCRIPT�̕�����������܂�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			// �e�L�X�g����cReedText��������ǂݍ���
			fgets(cReedText, sizeof(cReedText), pFile);
			// �ǂݍ��񂾕�������cHeadText�Ɋi�[
			sscanf(cReedText, "%s", &cHeadText);
		}

		// cHeadText��SCRIPT��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPT�̕�����������܂�
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				// �e�L�X�g����cReedText��������ǂݍ���
				fgets(cReedText, sizeof(cReedText), pFile);
				// �ǂݍ��񂾕�������cHeadText�Ɋi�[
				sscanf(cReedText, "%s", &cHeadText);

				// cHeadText��MOTIONSET��������
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					// END_MOTIONSET�̕�����������܂�
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						// �e�L�X�g����cReedText��������ǂݍ���
						fgets(cReedText, sizeof(cReedText), pFile);
						// �ǂݍ��񂾕�������cHeadText�Ɋi�[
						sscanf(cReedText, "%s", &cHeadText);

						// cHeadText��MOTIONSET��������
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							// m_nLoop�Ƀ��[�v�����邩�i�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_motion[nCntMotion].m_nLoop);
						}

						// cHeadText��NUM_KEY��������
						if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							// m_nNumKey�ɃL�[�̐����i�[
							sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_motion[nCntMotion].m_nNumKey);
						}

						// cHeadText��KEYSET��������
						if (strcmp(cHeadText, "KEYSET") == 0)
						{
							// END_KEYSET�̕�����������܂�
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								// �e�L�X�g����cReedText��������ǂݍ���
								fgets(cReedText, sizeof(cReedText), pFile);
								// �ǂݍ��񂾕�������cHeadText�Ɋi�[
								sscanf(cReedText, "%s", &cHeadText);

								// cHeadText��FRAME��������
								if (strcmp(cHeadText, "FRAME") == 0)
								{
									// m_nFrame�Ƀt���[�������i�[
									sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_motion[nCntMotion].m_KeyInfo[nCntKey].m_nFrame);
								}
								// cHeadText��KEY��������
								if (strcmp(cHeadText, "KEY") == 0)
								{
									// END_KEY�̕�����������܂�
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										// �e�L�X�g����cReedText��������ǂݍ���
										fgets(cReedText, sizeof(cReedText), pFile);
										// �ǂݍ��񂾕�������cHeadText�Ɋi�[
										sscanf(cReedText, "%s", &cHeadText);

										// cHeadText��POS��������
										if (strcmp(cHeadText, "POS") == 0)
										{
											// m_pos�ɍ��W���i�[
											sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_pos[nCntLoad].x,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_pos[nCntLoad].y,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_pos[nCntLoad].z);
										}
										// cHeadText��ROT��������
										if (strcmp(cHeadText, "ROT") == 0)
										{
											// m_rot�ɉ�]���i�[
											sscanf(cReedText, "%s %s %f %f %f", &cDie, &cDie,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_rot[nCntLoad].x,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_rot[nCntLoad].y,
												&m_motion[nCntMotion].m_KeyInfo[nCntKey].m_rot[nCntLoad].z);
										}
									}
									// �J�E���g�̉��Z
									nCntLoad++;
								}
							}
							// �ǂݍ��񂾃J�E���g�̏�����
							nCntLoad = 0;
							// �J�E���g�̉��Z
							nCntKey++;
						}
					}
					// �L�[�̐��̏�����
					nCntKey = 0;
					// �J�E���g�̉��Z
					nCntMotion++;
				}
			}
			// �t�@�C�������
			fclose(pFile);
		}
		// �J���Ȃ�������
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
	int  nCntLoad = 0;	 // �ǂݍ��񂾃J�E���g
	char cReedText[NUM_TEXT]; // �����Ƃ��ēǂݎ��p
	char cHeadText[NUM_TEXT]; // �����̔��ʗp
	char cDie[NUM_TEXT];		 // �g��Ȃ�����

	// �t�@�C�����J��
	pFile = fopen(cText, "r");

	// �J������
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

	// �J���Ȃ�������
	else
	{
		printf("�J����܂���ł���\n");
	}
}

//=============================================================================
// ���[�V�����N���X�̍X�V����
//=============================================================================
void CMotion::UpdateMotion(void)
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

		if (m_modelParent[nCntMotion].m_rot.x > D3DX_PI)
		{
			m_modelParent[nCntMotion].m_rot.x *= -1.0f;
		}
		if (m_modelParent[nCntMotion].m_rot.x < -D3DX_PI)
		{
			m_modelParent[nCntMotion].m_rot.x *= -1.0f;
		}

		if (m_modelParent[nCntMotion].m_rot.y > D3DX_PI)
		{
			m_modelParent[nCntMotion].m_rot.y *= -1.0f;
		}
		if (m_modelParent[nCntMotion].m_rot.y < -D3DX_PI)
		{
			m_modelParent[nCntMotion].m_rot.y *= -1.0f;
		}

		if (m_modelParent[nCntMotion].m_rot.x > D3DX_PI)
		{
			m_modelParent[nCntMotion].m_rot.x *= -1.0f;
		}
		if (m_modelParent[nCntMotion].m_rot.x < -D3DX_PI)
		{
			m_modelParent[nCntMotion].m_rot.x *= -1.0f;
		}
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
			m_nCntKey = m_motion[m_motionState].m_nNumKey;
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
