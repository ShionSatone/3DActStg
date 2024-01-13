//==============================================================
//
//�Q�[������[game.cpp]
//Author:����������
//
//==============================================================
#include "game.h"
#include "manager.h"
#include "playerModel.h"
#include "enemyModel.h"
#include "model.h"
#include "field.h"
#include "wall.h"
#include "score.h"
#include "edit.h"
#include "input.h"
#include "camera.h"
#include "weapon.h"
#include "bulletRemain.h"
#include "itemModel.h"
#include "switch.h"
#include "ranking.h"
#include "life.h"
#include "pause.h"
#include "fade.h"
#include "sound.h"

//�ÓI�����o�ϐ��錾
CPlayerModel *CGame::m_pPlayerModel = NULL;	//�v���C���[�̏��
CEdit *CGame::m_pEdit = NULL;				//�G�f�B�b�g�̏��
CBulletRemain *CGame::m_pBulletRemain = NULL;			//�c�e���̏��
CScore *CGame::m_pScore = NULL;				//�X�R�A�̏��
CLife *CGame::m_pLife = NULL;				//�����\���̏��
bool CGame::m_bReset = true;					//���Z�b�g�������ǂ���
bool CGame::m_bPause = false;					//�|�[�Y��ʂ�
CPause *CGame::m_pPause = NULL;				//�|�[�Y��ʂ̏��
CGame::GAMEMODE CGame::m_gameMode = GAMEMODE_GROUND;	//�Q�[�����[�h

//==============================================================
//�R���X�g���N�^
//==============================================================
CGame::CGame()
{
	m_nCntEnemy = 0;				//�G�o���J�E���g
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CGame::~CGame()
{

}

//==============================================================
//����������
//==============================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CCamera *pCamera = CManager::GetCamera();		//�J�����̏��擾
	CSound *pSound = CManager::GetSound();

	m_bReset = true;		//���Z�b�g���Ă��Ԃɂ���
	m_bPause = false;		//�|�[�Y���ĂȂ�

	//�J�����̏���������
	pCamera->Init();

	//�G�f�B�b�g�̐���
	m_pEdit = CEdit::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���e�X�C�b�`�̐���
	CSwitch::Create(D3DXVECTOR3(2488.0f, 185.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(2790.0f, 190.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(3440.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(3876.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(4934.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(5356.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(5650.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(6364.0f, 278.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(6690.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(7567.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CSwitch::Create(D3DXVECTOR3(9850.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�ǂ̐���
	for (int nCntWall = 0; nCntWall < 7; nCntWall++)
	{
		//�n��̐���
		CWall::Create(D3DXVECTOR3(150.0f + 1500.0f * nCntWall, 100.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	}

	//�n��̐���
	CWall::Create(D3DXVECTOR3(-250.0f, 1000.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);

	//�����̐���
	CWall::Create(D3DXVECTOR3(10300.0f, -4900.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

	//�����̕\��
	m_pLife = CLife::Create(D3DXVECTOR3(10.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�v���C���[�̐���
	m_pPlayerModel = CPlayerModel::Create(D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f));

	//�G�̐���
	CEnemyModel::Create(D3DXVECTOR3(445.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(1420.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(2230.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(9100.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(5700.0f, 280.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(6500.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);
	CEnemyModel::Create(D3DXVECTOR3(4480.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_FROG, 2);

	CEnemyModel::Create(D3DXVECTOR3(9700.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemyModel::ENEMYTYPE_AQUATICA, 3);
	CEnemyModel::Create(D3DXVECTOR3(7640.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemyModel::ENEMYTYPE_AQUATICA, 3);

	//��������
	CEnemyModel::Create(D3DXVECTOR3(10740.0f, -4990.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), CEnemyModel::ENEMYTYPE_WITCH, 40);

	//�A�C�e������
	CItemModel::Create(D3DXVECTOR3(1540.0f, 68.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_VAPOR);
	CItemModel::Create(D3DXVECTOR3(2060.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_ICE);
	CItemModel::Create(D3DXVECTOR3(3917.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_VAPOR);
	CItemModel::Create(D3DXVECTOR3(4450.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);
	CItemModel::Create(D3DXVECTOR3(5520.0f, 230.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_ICE);
	CItemModel::Create(D3DXVECTOR3(6400.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_ICE);
	CItemModel::Create(D3DXVECTOR3(3640.0f, 262.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_LIFE);
	CItemModel::Create(D3DXVECTOR3(3640.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);
	CItemModel::Create(D3DXVECTOR3(4730.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_LIFE);
	CItemModel::Create(D3DXVECTOR3(6770.0f, 266.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_LIFE);
	CItemModel::Create(D3DXVECTOR3(9500.0f, 120.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_ICE);
	CItemModel::Create(D3DXVECTOR3(10200.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_LIFE);
	CItemModel::Create(D3DXVECTOR3(8488.0f, 310.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItemModel::TYPEITEM_WATER);

	//�����̉Ɛ���
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\roof.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\wall00.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\wall01.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\wall02.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\floor01.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\floor02.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\floor03.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\floor04.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\well00.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\well01.x");
	CModel::Create(D3DXVECTOR3(10270.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\home\\well02.x");

	//����̎�ނ̕\��
	CWeapon::Create(D3DXVECTOR3(450.0f, 70.0f, 0.0f));

	//�c�e���̕\��
	m_pBulletRemain = CBulletRemain::Create(D3DXVECTOR3(10.0f, 50.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�X�R�A�̐���
	m_pScore = CScore::Create();

	//�|�[�Y��ʂ̐���
	m_pPause = CPause::Create();

	//BGM�Đ�
	pSound->Play(pSound->SOUND_LABEL_BGM002);

	CObject::SetType(CObject::TYPE_SCENE);

	return S_OK;
}

//==============================================================
//�I������
//==============================================================
void CGame::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	//BGM�̒�~
	pSound->Stop();

	//�����̔j��
	if (m_pLife != NULL)
	{
		m_pLife->Uninit();
		m_pLife = NULL;
	}

	//�c�e���̔j��
	if (m_pBulletRemain != NULL)
	{
		m_pBulletRemain->Uninit();
		m_pBulletRemain = NULL;
	}

	//�G�f�B�b�g�̔j��
	if (m_pEdit != NULL)
	{
		m_pEdit->Uninit();
		m_pEdit = NULL;
	}

	//�v���C���[�̔j��
	if (m_pPlayerModel != NULL)
	{
		m_pPlayerModel->Uninit();
		m_pPlayerModel = NULL;
	}

	//�|�[�Y�̔j��
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�X�V����
//==============================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//�p�b�h�̏��擾
	CFade *pFade = CManager::GetFade();			//�t�F�[�h�̏��擾

	if (pInputKeyboard->GetTrigger(DIK_P) == true || 
		pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_START, 0) == true)
	{//P�L�[����������

		m_bPause = m_bPause ? false : true;		//�|�[�Y�؂�ւ�
	}

	if (m_bPause == true)
	{//�|�[�Y���Ă�Ƃ�

		if (pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_B, 0) == true)
		{
			m_bPause = false;
		}
	}

}

//==============================================================
//�`�揈��
//==============================================================
void CGame::Draw(void)
{

}

//==============================================================
//�|�[�Y��ʂ̐ݒ菈��
//==============================================================
void CGame::SetEnablePauseMenu(bool bPouse)
{
	m_bPause = bPouse;
}