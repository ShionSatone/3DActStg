//==============================================================
//
//���f������[model.cpp]
//Author:����������
//
//==============================================================
#include "enemymodel.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "object.h"
#include "particle.h"
#include "modelHierarchy.h"
#include "motion.h"
#include "debugproc.h"
#include "bullet.h"
#include "playerModel.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "itemModel.h"
#include "switch.h"

//�}�N����`
#define NUM_MODEL			(2)			//�G�̎��
#define POS					(10.0f)		//pos�����l
#define MODEL_LEN			(3.0f)		//����
#define CURVE_RL			(0.5f)		//���E�̊p�x
#define CURVE_UP			(0.0f)		//��̊p�x
#define CURVE_DOWN			(1.0f)		//���̊p�x
#define MAX_STR				(128)		//�����̍ő吔
#define FILE_FROG			"data\\TEXT\\motion_frog.txt"		//�J�G���̃e�L�X�g
#define FILE_AQUATICA		"data\\TEXT\\motion_weapon.txt"		//�A�N�A�e�B�J�̃e�L�X�g
#define FILE_WITCH			"data\\TEXT\\motion_witch.txt"		//�����̃e�L�X�g
#define NUM_LEAF			(5)			//�t���܂Ƃ߂ĉ�����΂���
#define CURVE_LEAF			(D3DX_PI * 2 * 0.2f)		//�t��łp�x�̕���
#define JUMP_HEIGHT			(20.0f)		//�W�����v�̍���
#define FROG_MOVE_Y			(1.0f)		//�ړ���Y
#define LIFE_WITCH			(15)		//�����̎���
#define SWITCH_WITCH		(60 * 5)	//�����̍U���؂�ւ�����
#define SWITCH_3D			(60 * 13)	//���̐؂�ւ�����
#define SWITCH_END			(60 * 8)	//3D�I������

//�ÓI�����o�ϐ��錾
LPD3DXMESH CEnemyModel::m_pMesh = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER CEnemyModel::m_pBuffMat = NULL;				//�}�e���A���ւ̃|�C���^
DWORD CEnemyModel::m_dwNumMat = NULL;
CEnemyModel *CEnemyModel::m_apEnemyModel[MAX_ENEMY_MODEL] = {};		//�G�̏��
int CEnemyModel::m_nNumAll = 0;			//�G�̑���
CEnemWitch::ATTACK CEnemWitch::m_attack = ATTACK_GROUND;	//�U���̎��

//�J�G���̃p�[�c
char *CEnemyFrog::m_apFileName[PARTS_MAX] =
{
	"data\\MODEL\\frog\\00_body.x",
	"data\\MODEL\\frog\\01_arm_LU.x",
	"data\\MODEL\\frog\\02_arm_LD.x",
	"data\\MODEL\\frog\\03_hand_L.x",
	"data\\MODEL\\frog\\04_arm_RU.x",
	"data\\MODEL\\frog\\05_arm_RD.x",
	"data\\MODEL\\frog\\06_hand_R.x",
	"data\\MODEL\\frog\\07_leg_LU.x",
	"data\\MODEL\\frog\\08_leg_LD.x",
	"data\\MODEL\\frog\\09_ankle_L.x",
	"data\\MODEL\\frog\\10_shoe_L.x",
	"data\\MODEL\\frog\\11_leg_RU.x",
	"data\\MODEL\\frog\\12_leg_RD.x",
	"data\\MODEL\\frog\\13_ankle_R.x",
	"data\\MODEL\\frog\\14_shoe_R.x",
};

//�����b�p�A�N�A�e�B�J�̃p�[�c
char *CEnemyAquatica::m_apFileName[PARTS_MAX] =
{
	"data\\MODEL\\aqua.x",
	/*"data\\MODEL\\player\\01_head.x",
	"data\\MODEL\\player\\02_hair.x",
	"data\\MODEL\\player\\03_LU_arm.x",
	"data\\MODEL\\player\\04_LD_arm.x",
	"data\\MODEL\\player\\05_L_hand.x",
	"data\\MODEL\\player\\06_RU_arm.x",
	"data\\MODEL\\player\\07_RD_arm.x",
	"data\\MODEL\\player\\08_R_hand.x",
	"data\\MODEL\\player\\09_waist.x",
	"data\\MODEL\\player\\10_skirt.x",
	"data\\MODEL\\player\\11_LU_leg.x",
	"data\\MODEL\\player\\12_LD_leg.x",
	"data\\MODEL\\player\\13_L_shoe.x",
	"data\\MODEL\\player\\14_RU_leg.x",
	"data\\MODEL\\player\\15_RD_leg.x",
	"data\\MODEL\\player\\16_R_shoe.x",
	"data\\MODEL\\player\\17_fish.x",*/
};

//�����̃p�[�c
char *CEnemWitch::m_apFileName[PARTS_MAX] =
{
	"data\\MODEL\\witch\\00_body.x",
	"data\\MODEL\\witch\\01_head.x",
	"data\\MODEL\\witch\\02_LU_arm.x",
	"data\\MODEL\\witch\\03_LD_arm.x",
	"data\\MODEL\\witch\\04_L_hand.x",
	"data\\MODEL\\witch\\05_RU_arm.x",
	"data\\MODEL\\witch\\06_RD_arm.x",
	"data\\MODEL\\witch\\07_R_hand.x",
	"data\\MODEL\\witch\\08_waist.x",
	"data\\MODEL\\witch\\09_skirt.x",
	"data\\MODEL\\witch\\10_LU_leg.x",
	"data\\MODEL\\witch\\11_LD_leg.x",
	"data\\MODEL\\witch\\12_L_shoe.x",
	"data\\MODEL\\witch\\13_RU_leg.x",
	"data\\MODEL\\witch\\14_RD_leg.x",
	"data\\MODEL\\witch\\15_R_shoe.x",
};

//==============================================================
//�R���X�g���N�^
//==============================================================
CEnemyModel::CEnemyModel()
{
	m_pMotion = NULL;		//���[�V�����̏��

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu(�O��)
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�G�̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�G�̍ŏ��l
	m_nLife = 3;			//����
	m_nCntDamage = 0;		//�_���[�W�J�E���^�[
	m_nCntAttack = 0;		//�U���J�E���^�[
	m_state = CObject::STATE_NONE;		//�ʏ���

	m_nID = m_nNumAll;			//�G�̔ԍ��X�V
	m_nNumAll++;		//�������Z

	m_bAction = false;			//�U��������
	m_bJump = false;			//�W�����v������
	m_bLand = true;			//���n������
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CEnemyModel::CEnemyModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	m_pMotion = NULL;		//���[�V�����̏��

	m_pos = pos;		//�ʒu
	m_rot = rot;		//����
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�G�̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�G�̍ŏ��l
	m_nLife = nLife;			//����
	m_nCntDamage = 0;		//�_���[�W�J�E���^�[
	m_nCntAttack = 0;		//�U���J�E���^�[
	m_state = CObject::STATE_NONE;		//�ʏ���

	m_nID = m_nNumAll;			//�G�̔ԍ��X�V
	m_nNumAll++;		//�������Z

	m_bAction = false;			//�U��������
	m_bJump = false;			//�W�����v������
	m_bLand = true;			//���n������
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CEnemyModel::~CEnemyModel()
{
	m_nNumAll--;		//�������Z
}

//==============================================================
//�G�̐�������
//==============================================================
CEnemyModel *CEnemyModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE type, int nLife)
{
	if (m_nNumAll < MAX_ENEMY_MODEL)
	{//���f���̐����ő喢����������

		int nIdx = m_nNumAll;		//�������

		if (m_apEnemyModel[nIdx] == NULL)
		{//���������g�p����ĂȂ�������

			//�G�̐���
			switch (type)
			{
			case ENEMYTYPE_FROG:		//�J�G��

				m_apEnemyModel[nIdx] = new CEnemyFrog(pos, rot, nLife);

				break;

			case ENEMYTYPE_AQUATICA:	//�����b�p�A�N�A�e�B�J

				m_apEnemyModel[nIdx] = new CEnemyAquatica(pos, rot, nLife);

				break;

			case ENEMYTYPE_WITCH:		//����

				m_apEnemyModel[nIdx] = new CEnemWitch(pos, rot, nLife);

				break;
			}
		}

		//����������
		m_apEnemyModel[nIdx]->Init(pos, rot);

		//��ނ̐ݒ�
		m_apEnemyModel[nIdx]->SetType(CObject::TYPE_ENEMY);

		return m_apEnemyModel[nIdx];
	}

	return NULL;
}
#if 0

//==============================================================
//�G�̏���������
//==============================================================
HRESULT CEnemyModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	

	return S_OK;
}

#endif

//==============================================================
//�G�̏I������
//==============================================================
void CEnemyModel::Uninit(void)
{
	int nID = m_nID;		//�ԍ����

	if (m_apEnemyModel[nID] != NULL)
	{//���������g�p����Ă�����

		m_apEnemyModel[nID] = NULL;
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�G�̍X�V����
//==============================================================
void CEnemyModel::Update(void)
{
	/*CDebugProc *pDebugProc = CManager::GetDebugProc();

	pDebugProc->Print("\n�G�̐��F%d\n", m_nNumAll);*/

	
}

//==============================================================
//�G�̕`�揈��
//==============================================================
void CEnemyModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//****************************************************************************************
//�J�G��
//
//==============================================================
//�R���X�g���N�^[�J�G��]
//==============================================================
CEnemyFrog::CEnemyFrog()
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�G(�p�[�c)�ւ̃|�C���^
	}
}

//==============================================================
//�R���X�g���N�^[�J�G��](�I�[�o�[���[�h)
//==============================================================
CEnemyFrog::CEnemyFrog(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�G(�p�[�c)�ւ̃|�C���^
	}

	m_nLife = nLife;		//�������
}

//==============================================================
//�f�X�g���N�^[�J�G��]
//==============================================================
CEnemyFrog::~CEnemyFrog()
{

}

//==============================================================
//�J�G���̏���������
//==============================================================
HRESULT CEnemyFrog::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����

	//�G�̐����i�S�p�[�c���j
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//���[�V�����̏������E����
	m_pMotion = m_pMotion->Create(m_pMotion->MOTIONTEXT_FROG);
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();

	//�G�̃t�@�C���ǂݍ���
	CEnemyFrog::LoadFile();

	//�ő�l�E�ŏ��l���
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		//�ő�lY
		if ((nCntEnemy <= PARTS_BODY/* && nCntEnemy <= PARTS_HEAD) ||
			(nCntEnemy <= PARTS_LEG_R && nCntEnemy <= PARTS_FOOT_R*/))
		{
			m_max.y += m_apModel[nCntEnemy]->GetSizeMax().y;		//�ő�l���Z
		}

		//�ő�l����ւ�
		if (m_max.x < m_apModel[nCntEnemy]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntEnemy]->GetSizeMax().x;		//�ŏ��lX
		}
		if (m_max.z < m_apModel[nCntEnemy]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntEnemy]->GetSizeMax().z;		//�ŏ��lZ

		}

		//�ŏ��l����ւ�
		if (m_min.x > m_apModel[nCntEnemy]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntEnemy]->GetSizeMin().x;		//�ŏ��lX
		}
		if (m_min.y > m_apModel[nCntEnemy]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntEnemy]->GetSizeMin().y;		//�ŏ��lY
		}
		if (m_min.z > m_apModel[nCntEnemy]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntEnemy]->GetSizeMin().z;		//�ŏ��lZ
		}
	}

	m_max.y += 25.0f;

	return S_OK;
}

//==============================================================
//�J�G���̏I������
//==============================================================
void CEnemyFrog::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//�g�p����Ă�Ƃ�

			//�I������
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//�g�p����Ă�Ƃ�

		//���[�V�����̔j��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�G�̏I������
	CEnemyModel::Uninit();
}

//==============================================================
//�J�G���̍X�V����
//==============================================================
void CEnemyFrog::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	m_posOld = m_pos;		//���݂̈ʒu

	//�v���C���[�̌����擾
	//m_rot.x = -pPlayerModel->GetRotation().x;

	//�ړ��ʉ��Z
	m_move.y -= FROG_MOVE_Y;

	//�ʒu�X�V
	m_pos += m_move;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//�����蔻��
	if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == true)
	{//���n������

		//m_bJump = false;		//�W�����v���ĂȂ���Ԃɂ���
	}

	switch (m_state)
	{
	case STATE_NONE:		//�ʏ���

		m_bJump = false;

		if (pPlayer->GetPosition().x > m_pos.x - (SCREEN_WIDTH * 0.5f) &&
			pPlayer->GetPosition().x < m_pos.x + (SCREEN_WIDTH * 0.5f))
		{//�v���C���[���G�̋߂��ɗ�����

			if (m_nCntAttack >= 60 * 3)
			{//��莞�Ԍo������

				m_state = STATE_ATTACK;		//�U����Ԃɂ���
				m_nCntAttack = 0;			//�U���J�E���^�[������
			}
			else
			{//���Ԃ��o���ĂȂ�������

				m_nCntAttack++;		//�U���J�E���^�[���Z
			}
		}
		break;

	case STATE_ATTACK:		//�U�����

		//�W�����v����
		m_move.x = -10.0f;
		m_move.y = JUMP_HEIGHT;

		if (m_bJump == false)
		{//�W�����v���ĂȂ�������

			m_bJump = true;		//�W�����v��Ԃɂ���

			//�W�����v���[�V����
			m_pMotion->Set(m_pMotion->MOTIONTYPE_JUMP);

			//�p�[�e�B�N������
			CParticle::Create(m_pos, D3DXCOLOR(0.7f, 0.5f, 0.4f, 1.0f), PARTICLETYPE_JUMP, 30, 20);
		}

		//�U������(��ōU��)
		//�e�̐���(��)
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_ENEMY);

		m_state = STATE_NONE;		//�ʏ��Ԃɂ���

		break;

	case STATE_DAMAGE:		//�_���[�W���

		m_nCntDamage--;		//�_���[�W���Ԍ��Z

		if (m_nCntDamage <= 0)
		{//�_���[�W���Ԃ��I�������

			m_state = CObject::STATE_NONE;

			//��Ԑݒ�
			for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
			{
				m_apModel[nCntEnemy]->SetState(m_state);		//�ʏ��Ԃɂ���

			}
		}

		break;
	}

	if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_pMotion->IsFinish() == true) && m_bJump == false)
	{//���[�V�������I��������

		//�ҋ@��Ԃɖ߂�
		m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);
	}

	//���[�V�����̍X�V����
	m_pMotion->Update();

	//�G�̍X�V����
	CEnemyModel::Update();
}

//==============================================================
//�J�G���̕`�揈��
//==============================================================
void CEnemyFrog::Draw(void)
{
	//�G�̕`�揈��
	CEnemyModel::Draw();

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//�G�̕`��
		m_apModel[nCntPlayer]->Draw();
	}
}

//==============================================================
//�J�G���̃q�b�g����
//==============================================================
void CEnemyFrog::Hit(void)
{
	CSound *pSound = CManager::GetSound();

	//BGM�Đ�
	pSound->Play(pSound->SOUND_LABEL_SE_DAMAGE000);

	m_nLife--;

	if (m_nLife > 0)
	{//�܂��������c���Ă���

		m_state = CObject::STATE_DAMAGE;

		for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
		{
			m_apModel[nCntEnemy]->SetState(m_state);		//�_���[�W��Ԃɂ���
		}

		m_nCntDamage = 5;					//�_���[�W��Ԃ�ۂ��Ԑݒ�
	}
	else if (m_nLife <= 0)
	{//�������Ȃ�������

		//�X�R�A���Z
		CScore::Add(10520);

		//�����̐���
		CParticle::Create(m_pos, D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f), PARTICLETYPE_EXPLOSION, 0, 13);

		//�I������
		CEnemyModel::Uninit();
	}
}

//==============================================================
//�J�G���̃��f���t�@�C���ǂݍ��ݏ���
//==============================================================
void CEnemyFrog::LoadFile(void)
{
	FILE *pFile;				//�t�@�C���|�C���^
	char aString[MAX_STR];		//�����ǂݍ���
	int nIndex = 0, nParent = 0;	//�p�[�cNo.,�e�ԍ�
	D3DXVECTOR3 pos, rot;

	//�t�@�C���J��
	pFile = fopen(FILE_FROG, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]����܂ł̊�

			fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]��������

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]������܂ł̊�

				fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]��������

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]������܂ł̊�

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

						if (strcmp(&aString[0], "INDEX") == 0)
						{//�p�[�cNo.

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nIndex);			//�p�[�cNo.�ǂݍ���

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//�e���

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nParent);			//�e�ԍ��ǂݍ���

							if (nParent == -1)
							{//�e�����Ȃ�������

								m_apModel[nIndex]->SetParent(NULL);		//NULL������
							}
							else
							{//�e��������

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//�e�ԍ������
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//�ʒu���

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &pos.x);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.y);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.z);		//�ʒu�ǂݍ���

							m_apModel[nIndex]->SetPosition(pos);		//�ʒu�ݒ�
							m_apModel[nIndex]->SetDefaultPosition(pos);	//�����ʒu�ݒ�

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//�������

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &rot.x);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.y);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.z);		//�����ǂݍ���

							m_apModel[nIndex]->SetRotation(rot);		//�����ݒ�
							m_apModel[nIndex]->SetDefaultRotation(rot);	//���������ݒ�
						}
					}
				}
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
}

//****************************************************************************************
//�����b�p�A�N�A�e�B�J
//
//==============================================================
//�R���X�g���N�^[�����b�p�A�N�A�e�B�J]
//==============================================================
CEnemyAquatica::CEnemyAquatica()
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�G(�p�[�c)�ւ̃|�C���^
	}
}

//==============================================================
//�R���X�g���N�^[�����b�p�A�N�A�e�B�J](�I�[�o�[���[�h)
//==============================================================
CEnemyAquatica::CEnemyAquatica(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�G(�p�[�c)�ւ̃|�C���^
	}

	m_nLife = nLife;		//�������
}

//==============================================================
//�f�X�g���N�^[�����b�p�A�N�A�e�B�J]
//==============================================================
CEnemyAquatica::~CEnemyAquatica()
{

}

//==============================================================
//�����b�p�A�N�A�e�B�J�̏���������
//==============================================================
HRESULT CEnemyAquatica::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����

	//�G�̐����i�S�p�[�c���j
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	////���[�V�����̏������E����
	//m_pMotion = m_pMotion->Create(m_pMotion->MOTIONTEXT_PLAYER);
	//m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	//m_pMotion->Init();

	////�G�̃t�@�C���ǂݍ���
	//CEnemyAquatica::LoadFile();

	//�ő�l�E�ŏ��l���
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		//�ő�lY
		if ((nCntEnemy <= PARTS_BODY/* && nCntEnemy <= PARTS_HEAD) ||
			(nCntEnemy <= PARTS_LEG_R && nCntEnemy <= PARTS_FOOT_R*/))
		{
			m_max.y += m_apModel[nCntEnemy]->GetSizeMax().y;		//�ő�l���Z
		}

		//�ő�l����ւ�
		if (m_max.x < m_apModel[nCntEnemy]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntEnemy]->GetSizeMax().x;		//�ŏ��lX
		}
		if (m_max.z < m_apModel[nCntEnemy]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntEnemy]->GetSizeMax().z;		//�ŏ��lZ

		}

		//�ŏ��l����ւ�
		if (m_min.x > m_apModel[nCntEnemy]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntEnemy]->GetSizeMin().x;		//�ŏ��lX
		}
		if (m_min.y > m_apModel[nCntEnemy]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntEnemy]->GetSizeMin().y;		//�ŏ��lY
		}
		if (m_min.z > m_apModel[nCntEnemy]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntEnemy]->GetSizeMin().z;		//�ŏ��lZ
		}
	}

	m_max.y += 25.0f;

	return S_OK;
}

//==============================================================
//�����b�p�A�N�A�e�B�J�̏I������
//==============================================================
void CEnemyAquatica::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//�g�p����Ă�Ƃ�

		 //�I������
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//�g�p����Ă�Ƃ�

		//���[�V�����̔j��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�G�̏I������
	CEnemyModel::Uninit();
}

//==============================================================
//�����b�p�A�N�A�e�B�J�̍X�V����
//==============================================================
void CEnemyAquatica::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	m_posOld = m_pos;		//���݂̈ʒu

	//�����蔻��
	CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max);

	switch (m_state)
	{
	case STATE_NONE:		//�ʏ���

		if (pPlayer->GetPosition().x >= m_pos.x - (SCREEN_WIDTH * 0.5f) &&
			pPlayer->GetPosition().x <= m_pos.x + (SCREEN_WIDTH * 0.5f))
		{//�v���C���[���G�̋߂��ɗ�����

			if (m_nCntAttack >= 60 * 1)
			{//��莞�Ԍo������

				m_state = STATE_ATTACK;		//�U����Ԃɂ���
				m_nCntAttack = 0;			//�U���J�E���^�[������
			}
			else
			{//���Ԃ��o���ĂȂ�������

				m_nCntAttack++;		//�U���J�E���^�[���Z
			}
		}

		break;

	case STATE_ATTACK:		//�U�����

		//�U������(�t���΂�)
		for (int nCntBullet = 0; nCntBullet < NUM_LEAF; nCntBullet++)
		{
			CBullet::Create(D3DXVECTOR3(m_pos.x, (m_pos.y + m_max.y) * 0.5f, m_pos.z - 10.0f),
				D3DXVECTOR3(sinf((float)(nCntBullet * CURVE_LEAF) + CURVE_LEAF) * 1.0f,
					cosf((float)(nCntBullet * CURVE_LEAF) + CURVE_LEAF) * 1.0f,
					0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_ENEMY);

		}

		m_state = STATE_NONE;		//�ʏ��Ԃɂ���

		break;

	case STATE_DAMAGE:		//�_���[�W���

		m_nCntDamage--;		//�_���[�W���Ԍ��Z

		if (m_nCntDamage <= 0)
		{//�_���[�W���Ԃ��I�������

			m_state = CObject::STATE_NONE;

			//��Ԑݒ�
			for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
			{
				m_apModel[nCntEnemy]->SetState(m_state);		//�ʏ��Ԃɂ���

			}
		}

		break;
	}

	pDebugProc->Print("�G�̈ʒu(%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);

	//�G�̍X�V����
	CEnemyModel::Update();
}

//==============================================================
//�����b�p�A�N�A�e�B�J�̕`�揈��
//==============================================================
void CEnemyAquatica::Draw(void)
{
	//�G�̕`�揈��
	CEnemyModel::Draw();

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//�G�̕`��
		m_apModel[nCntPlayer]->Draw();
	}
}

//==============================================================
//�����b�p�A�N�A�e�B�J�̃q�b�g����
//==============================================================
void CEnemyAquatica::Hit(void)
{
	CSound *pSound = CManager::GetSound();

	//BGM�Đ�
	pSound->Play(pSound->SOUND_LABEL_SE_DAMAGE000);
	
	m_nLife--;

	if (m_nLife > 0)
	{//�܂��������c���Ă���

		m_state = CObject::STATE_DAMAGE;

		for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
		{
			m_apModel[nCntEnemy]->SetState(m_state);		//�_���[�W��Ԃɂ���
		}

		m_nCntDamage = 5;					//�_���[�W��Ԃ�ۂ��Ԑݒ�
	}
	else if (m_nLife <= 0)
	{//�������Ȃ�������

		//�X�R�A���Z
		CScore::Add(15000);

		//�����̐���
		CParticle::Create(m_pos, D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f), PARTICLETYPE_EXPLOSION, 0, 13);

		//�I������
		CEnemyModel::Uninit();
	}
}

//==============================================================
//�����b�p�A�N�A�e�B�J�̃��f���t�@�C���ǂݍ��ݏ���
//==============================================================
void CEnemyAquatica::LoadFile(void)
{
	FILE *pFile;				//�t�@�C���|�C���^
	char aString[MAX_STR];		//�����ǂݍ���
	int nIndex = 0, nParent = 0;	//�p�[�cNo.,�e�ԍ�
	D3DXVECTOR3 pos, rot;

	//�t�@�C���J��
	pFile = fopen(FILE_AQUATICA, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]����܂ł̊�

			fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]��������

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]������܂ł̊�

				fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]��������

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]������܂ł̊�

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

						if (strcmp(&aString[0], "INDEX") == 0)
						{//�p�[�cNo.

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nIndex);			//�p�[�cNo.�ǂݍ���

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//�e���

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nParent);			//�e�ԍ��ǂݍ���

							if (nParent == -1)
							{//�e�����Ȃ�������

								m_apModel[nIndex]->SetParent(NULL);		//NULL������
							}
							else
							{//�e��������

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//�e�ԍ������
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//�ʒu���

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &pos.x);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.y);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.z);		//�ʒu�ǂݍ���

							m_apModel[nIndex]->SetPosition(pos);		//�ʒu�ݒ�
							m_apModel[nIndex]->SetDefaultPosition(pos);	//�����ʒu�ݒ�

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//�������

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &rot.x);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.y);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.z);		//�����ǂݍ���

							m_apModel[nIndex]->SetRotation(rot);		//�����ݒ�
							m_apModel[nIndex]->SetDefaultRotation(rot);	//���������ݒ�
						}
					}
				}
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
}

//****************************************************************************************
//����
//
//==============================================================
//�R���X�g���N�^[����]
//==============================================================
CEnemWitch::CEnemWitch()
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�G(�p�[�c)�ւ̃|�C���^
	}

	m_nCntEnemy = 0;	//�G�o���܂ł̃J�E���g
	m_fAngle = 0.0f;		//�p�x
	m_bItem = false;		//�A�C�e���o�����Ă����̂�
}

//==============================================================
//�R���X�g���N�^[����](�I�[�o�[���[�h)
//==============================================================
CEnemWitch::CEnemWitch(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�G(�p�[�c)�ւ̃|�C���^
	}

	m_nLife = nLife;		//�������
	m_form = FORM_FIRST;	//��P�`��
	m_attack = ATTACK_GROUND;		//�U���̎��
	m_nCntSwitch = 0;	//�؂�ւ��J�E���g
	m_bBgm = false;		//BGM��������
	m_rot = rot;	//����
	m_nCntEnemy = 0;	//�G�o���܂ł̃J�E���g
	m_fAngle = 0.0f;		//�p�x
	m_nCntItem = 0;		//�A�C�e���o���J�E���g
	m_bItem = false;		//�A�C�e���o�����Ă����̂�
}

//==============================================================
//�f�X�g���N�^[����]
//==============================================================
CEnemWitch::~CEnemWitch()
{

}

//==============================================================
//�����̏���������
//==============================================================
HRESULT CEnemWitch::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����

	//�G�̐����i�S�p�[�c���j
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//���[�V�����̏������E����
	m_pMotion = m_pMotion->Create(CMotion::MOTIONTEXT_WITCH);
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();

	//�G�̃t�@�C���ǂݍ���
	CEnemWitch::LoadFile();

	//�ő�l�E�ŏ��l���
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		//�ő�lY
		if ((nCntEnemy <= PARTS_BODY && nCntEnemy <= PARTS_HEAD) ||
			(nCntEnemy <= PARTS_LEG_R && nCntEnemy <= PARTS_FOOT_R))
		{
			m_max.y += m_apModel[nCntEnemy]->GetSizeMax().y;		//�ő�l���Z
		}

		//�ő�l����ւ�
		if (m_max.x < m_apModel[nCntEnemy]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntEnemy]->GetSizeMax().x;		//�ŏ��lX
		}
		if (m_max.z < m_apModel[nCntEnemy]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntEnemy]->GetSizeMax().z;		//�ŏ��lZ

		}

		//�ŏ��l����ւ�
		if (m_min.x > m_apModel[nCntEnemy]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntEnemy]->GetSizeMin().x;		//�ŏ��lX
		}
		if (m_min.y > m_apModel[nCntEnemy]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntEnemy]->GetSizeMin().y;		//�ŏ��lY
		}
		if (m_min.z > m_apModel[nCntEnemy]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntEnemy]->GetSizeMin().z;		//�ŏ��lZ
		}
	}

	m_max.y += 10.0f;
	m_min.y = 0.0f;

	return S_OK;
}

//==============================================================
//�����̏I������
//==============================================================
void CEnemWitch::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//�g�p����Ă�Ƃ�

		 //�I������
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//�g�p����Ă�Ƃ�

		//���[�V�����̔j��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�G�̏I������
	CEnemyModel::Uninit();
}

//==============================================================
//�����̍X�V����
//==============================================================
void CEnemWitch::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CPlayerModel *pPlayer = CGame::GetPlayerModel();
	CCamera *pCamera = CManager::GetCamera();
	CGame *pGame = CScene::GetGame();

	m_posOld = m_pos;		//���݂̈ʒu

	m_nCntSwitch++;
	m_nCntEnemy++;

	//�����蔻��
	CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max);

	if ((pGame->GetGameMode() == pGame->GAMEMODE_BOSS && pPlayer->GetPosition().x >= 10452.0f) || m_bBgm == true)
	{//�{�X��̎�

		if (m_bBgm == false)
		{//BGM���Ȃ����Ƃ�

			CSound *pSound = CManager::GetSound();

			//BGM�̒�~
			pSound->Stop(pSound->SOUND_LABEL_BGM002);

			//BGM�Đ�
			pSound->Play(pSound->SOUND_LABEL_BGMBOSS);

			m_bBgm = true;
		}

		switch (m_state)
		{
		case STATE_NONE:		//�ʏ���

			if (pCamera->GetMode() == false)
			{
				m_attack = ATTACK_3D;
			}

			if (m_bAction == true && m_pMotion->IsFinish() == true)
			{//�U�����I�������

				//�ҋ@��Ԃɖ߂�
				m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);

				m_bAction = false;		//�U�����ĂȂ���Ԃɂ���
			}

			if (m_nCntAttack >= 60 * 2)
			{//��莞�Ԍo������

				m_state = STATE_ATTACK;		//�U����Ԃɂ���
				m_nCntAttack = 0;			//�U���J�E���^�[������
			}
			else
			{//���Ԃ��o���ĂȂ�������

				m_nCntAttack++;		//�U���J�E���^�[���Z
			}

			break;

		case STATE_ATTACK:		//�U�����

			m_state = STATE_NONE;		//�ʏ��Ԃɂ���

			if (m_form == FORM_FIRST)
			{//��P�`�Ԃ̂Ƃ�

				if (m_attack == ATTACK_GROUND)
				{
					//�e�̐���
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(sinf(m_rot.y) * -2.0f, 0.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
				}
				else if (m_attack == ATTACK_FLY)
				{
					//�e�̐���
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(sinf(m_rot.y) * -2.0f, -2.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
				}
				else if (m_attack == ATTACK_3D)
				{
					int nBulletRand = rand() % 4;

					switch (nBulletRand)
					{
					case 0:

						for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
						{
							//�e�̐���
							CBullet::Create(D3DXVECTOR3(10200.0f + (nCntBullet * 100.0f), -4800.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
						}

						break;

					case 1:

						for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
						{
							//�e�̐���
							CBullet::Create(D3DXVECTOR3(10400.0f + (nCntBullet * 100.0f), -4800.0f, 0.0f), D3DXVECTOR3(0.0f, -2.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
						}

						break;

					case 2:

						for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
						{
							//�e�̐���
							CBullet::Create(D3DXVECTOR3(10200.0f, -4900.0f + (nCntBullet * 100.0f), 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
						}

						break;

					case 3:

						for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
						{
							//�e�̐���
							CBullet::Create(D3DXVECTOR3(10650.0f, -4900.0f + (nCntBullet * 100.0f), 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
						}

						break;
					}

					
				}

				if (m_bAction == false)
				{//�U�����ĂȂ��Ƃ�

					//�U������
					m_pMotion->Set(m_pMotion->MOTIONTYPE_ACTION);
					m_bAction = true;
				}
			}
			else
			{
				//�e�̐���
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, -10.0f), CObject::TYPE_ENEMY, PARTICLETYPE_WITCH);
			}

			break;

		case STATE_DAMAGE:		//�_���[�W���

			m_nCntDamage--;		//�_���[�W���Ԍ��Z

			if (m_nCntDamage <= 0)
			{//�_���[�W���Ԃ��I�������

				m_state = CObject::STATE_NONE;

				//��Ԑݒ�
				for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
				{
					m_apModel[nCntEnemy]->SetState(m_state);		//�ʏ��Ԃɂ���

				}
			}

			break;

		case STATE_DEATH:		//���S���

			if (m_form == FORM_FIRST)
			{//��P�`�Ԃ̂Ƃ�

				m_pos = D3DXVECTOR3(0.0f, -4990.0f, 1000.0f);
				m_nLife = LIFE_WITCH;
				m_form = FORM_SECOND;		//��Q�`��
				pPlayer->SetPosition(D3DXVECTOR3(0.0f, -5000.0f, 0.0f));
				m_state = STATE_NONE;
			}

			break;
		}

		switch (m_attack)
		{
		case ATTACK_GROUND:		//�n��

			if ((m_nCntSwitch % SWITCH_WITCH) == 0)
			{
				m_attack = ATTACK_FLY;		//�󒆍U��
				m_pos.y = -4800.0f;
				m_fAngle = 0.0f;
			}

			if (m_pos.x > pPlayer->GetPosition().x)
			{
				m_rot.y = 0.5f * D3DX_PI;		//����������
			}
			else if (m_pos.x < pPlayer->GetPosition().x)
			{
				m_rot.y = 0.5f * -D3DX_PI;		//�E��������
			}

			if ((m_nCntSwitch % SWITCH_3D) == 0)
			{//3D�؂�ւ�����

				pCamera->SetMode(true);
				m_pos = D3DXVECTOR3(10500.0f, -4800.0f, 80.0f);
				m_rot.y = 0.0f;
				m_attack = ATTACK_3D;
			}


			break;

		case ATTACK_FLY:		//��

			m_fAngle += 0.05f;
			m_pos.y = m_pos.y + sinf(m_fAngle) * 0.5f;

			if ((m_nCntSwitch % SWITCH_WITCH) == 0)
			{
				m_attack = ATTACK_GROUND;	//�n�ʍU��
				m_pos.y = -4990.0f;

			}

			if (m_pos.x > pPlayer->GetPosition().x)
			{
				m_rot.y = 0.5f * D3DX_PI;		//����������
			}
			else if (m_pos.x < pPlayer->GetPosition().x)
			{
				m_rot.y = 0.5f * -D3DX_PI;		//�E��������
			}

			if ((m_nCntSwitch % SWITCH_3D) == 0)
			{//3D�؂�ւ�����

				pCamera->SetMode(false);
				m_pos = D3DXVECTOR3(10500.0f, -4800.0f, 80.0f);
				m_rot.y = 0.0f;
				m_attack = ATTACK_3D;
			}

			break;
			
		case ATTACK_3D:			//3D

			if (pCamera->GetMode() == true)
			{
				m_nCntItem = 0;
				m_pos.y = -4990.0f;
				m_pos.z = 0.0f;
				m_attack = ATTACK_GROUND;
			}

			if ((m_nCntItem == 60 * 9) && m_bItem == false)
			{
				CSwitch::Create(D3DXVECTOR3(10600.0f, -4800.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				CItemModel::Create(D3DXVECTOR3(10300.0f, -4900.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);

				m_bItem = true;
			}

			m_nCntItem++;

			break;
		}

		//�ʒu�ύX����
		if ((m_nCntEnemy % 480) == 0)
		{
			float randPos = float(rand() % 200);

			if (m_pos.x > 10500.0f)
			{
				m_pos.x -= randPos;
			}
			else if (m_pos.x <= 10500.0f)
			{
				m_pos.x += randPos;
			}
		}

		/*if (m_bItem == true)
		{
			if (m_nCntItem >= 60 * 20)
			{
				CItemModel::Create(D3DXVECTOR3(10300.0f, -4900.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);

				m_nCntItem = 0;
			}

			m_nCntItem++;
		}*/

		m_pos += m_move;

		pDebugProc->Print("�G�̈ʒu(%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);
		pDebugProc->Print("�G�̌���( %f )\n", m_rot.y);

	}

	//���[�V�����̍X�V����
	m_pMotion->Update();

	//�G�̍X�V����
	CEnemyModel::Update();
}

//==============================================================
//�����̕`�揈��
//==============================================================
void CEnemWitch::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	//�G�̕`�揈��
	CEnemyModel::Draw();

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//�G�̕`��
		m_apModel[nCntPlayer]->Draw();
	}

	//�ʏ�
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//==============================================================
//�����̃q�b�g����
//==============================================================
void CEnemWitch::Hit(void)
{
	CSound *pSound = CManager::GetSound();

	m_nLife--;

	//BGM�Đ�
	pSound->Play(pSound->SOUND_LABEL_SE_DAMAGE000);

	if (m_nLife > 0)
	{//�܂��������c���Ă���

		m_state = CObject::STATE_DAMAGE;

		for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
		{
			m_apModel[nCntEnemy]->SetState(m_state);		//�_���[�W��Ԃɂ���
		}

		m_nCntDamage = 5;					//�_���[�W��Ԃ�ۂ��Ԑݒ�
	}
	else if (m_nLife <= 0)
	{//�������Ȃ�������

		CScore *pScore = CGame::GetScore();		//�X�R�A�̏��

		//�X�R�A���Z
		CScore::Add(1055000);

		//�����̐���
		CParticle::Create(m_pos, D3DXCOLOR(0.7f, 0.0f, 0.7f, 1.0f), PARTICLETYPE_EXPLOSION, 0, 13);

		//�X�R�A�ݒ�
		CManager::SetNumScore(pScore->Get());

		//if (m_form == FORM_SECOND)
		{//��2�`�Ԃ̂Ƃ�

			CFade *pFade = CManager::GetFade();		//�t�F�[�h�̏��擾

			//���U���g�̔���
			CManager::SetResult(true);

			//�I������
			CEnemyModel::Uninit();

			//���U���g���
			pFade->SetFade(CScene::MODE_RESULT);
		}
	}
}

//==============================================================
//�����̃��f���t�@�C���ǂݍ��ݏ���
//==============================================================
void CEnemWitch::LoadFile(void)
{
	FILE *pFile;				//�t�@�C���|�C���^
	char aString[MAX_STR];		//�����ǂݍ���
	int nIndex = 0, nParent = 0;	//�p�[�cNo.,�e�ԍ�
	D3DXVECTOR3 pos, rot;

	//�t�@�C���J��
	pFile = fopen(FILE_WITCH, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]����܂ł̊�

			fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]��������

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]������܂ł̊�

				fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]��������

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]������܂ł̊�

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

						if (strcmp(&aString[0], "INDEX") == 0)
						{//�p�[�cNo.

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nIndex);			//�p�[�cNo.�ǂݍ���

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//�e���

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nParent);			//�e�ԍ��ǂݍ���

							if (nParent == -1)
							{//�e�����Ȃ�������

								m_apModel[nIndex]->SetParent(NULL);		//NULL������
							}
							else
							{//�e��������

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//�e�ԍ������
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//�ʒu���

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &pos.x);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.y);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.z);		//�ʒu�ǂݍ���

							m_apModel[nIndex]->SetPosition(pos);		//�ʒu�ݒ�
							m_apModel[nIndex]->SetDefaultPosition(pos);	//�����ʒu�ݒ�

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//�������

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &rot.x);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.y);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.z);		//�����ǂݍ���

							m_apModel[nIndex]->SetRotation(rot);		//�����ݒ�
							m_apModel[nIndex]->SetDefaultRotation(rot);	//���������ݒ�
						}
					}
				}
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
}