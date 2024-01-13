//==============================================================
//
//�`���[�g���A������[tutorial.cpp]
//Author:����������
//
//==============================================================
#include "tutorial.h"
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
#include "bg.h"
#include "sound.h"
#include "fade.h"
#include "object2D.h"
#include "texture.h"
#include "switch.h"

//�ÓI�����o�ϐ��錾
CPlayerModel *CTutorial::m_pPlayerModel = NULL;	//�v���C���[�̏��
CEdit *CTutorial::m_pEdit = NULL;				//�G�f�B�b�g�̏��
bool CTutorial::bReset = true;					//���Z�b�g�������ǂ���
CBulletRemain *CTutorial::m_pBulletRemain = NULL;		//�c�e���̏��
int CTutorial::m_step = STEP_SYNOP_FIRST;		//���݂̃X�e�b�v
CObject2D *CTutorial::m_pObject2D[NUM_TUTORIAL_TEX] = {};		//�I�u�W�F�N�g2D�̏��

char *CTutorial::m_apFileName[STEP_MAX] =
{
	"data\\TEXTURE\\tutorial00.jpg",
	"data\\TEXTURE\\tutorial01.jpg",
	"data\\TEXTURE\\tutorial02.jpg",
	"data\\TEXTURE\\tutorial03.jpg",
	"data\\TEXTURE\\tutorial00.png",
	"data\\TEXTURE\\tutorial01.png",
	"data\\TEXTURE\\tutorial02.png",
	"data\\TEXTURE\\tutorial04.jpg",
};

//==============================================================
//�R���X�g���N�^
//==============================================================
CTutorial::CTutorial()
{
	m_step = STEP_SYNOP_FIRST;		//���݂̃X�e�b�v

	for (int nCntTex = 0; nCntTex < NUM_TUTORIAL_TEX; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//�e�N�X�`���ԍ�
	}

	m_nNumBullet = 0;		//�e����������
	m_bMoveR = false;		//�E�ړ�
	m_bMoveL = false;		//���ړ�
	m_bPad = false;				//�p�b�h�̃X�e�B�b�N��|������
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CTutorial::~CTutorial()
{

}

//==============================================================
//����������
//==============================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();
	CCamera *pCamera = CManager::GetCamera();		//�J�����̏��擾
	CSound *pSound = CManager::GetSound();

	//�J�����̏���������
	pCamera->Init();

	//�G�f�B�b�g�̐���
	m_pEdit = CEdit::Create(D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture[0] = pTexture->Regit(m_apFileName[m_step]);
	m_nIdxTexture[1] = pTexture->Regit("data\\TEXTURE\\enter.png");
	m_nIdxTexture[2] = pTexture->Regit("data\\TEXTURE\\tutorialskip.png");

	for (int nCntTex = 0; nCntTex < NUM_TUTORIAL_TEX; nCntTex++)
	{
		//���������u
		if (m_pObject2D[nCntTex] == NULL)
		{//�g�p����ĂȂ��Ƃ�

			//2D�I�u�W�F�N�g����
			m_pObject2D[nCntTex] = CObject2D::Create();

			if (m_pObject2D[nCntTex] != NULL)
			{//�����o������

				//�傫���ݒ�
				m_pObject2D[nCntTex]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

				//�e�N�X�`�����蓖��
				m_pObject2D[nCntTex]->BindTexture(m_nIdxTexture[nCntTex]);

				//�ʒu�ݒ�
				if (nCntTex == 0)
				{
					m_pObject2D[nCntTex]->SetPosition(CObject::TYPE_NONE, pos, SCREEN_WIDTH, SCREEN_HEIGHT);

				}
				else if (nCntTex == 1)
				{//Enter
					m_pObject2D[nCntTex]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(1180.0f, 680.0f, 0.0f), 90.0f, 45.0f);
				}
				else if (nCntTex == 2)
				{//�X�L�b�v
					m_pObject2D[nCntTex]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(1100.0f, 60.0f, 0.0f), 150.0f, 40.0f);
				}
			}
		}
	}

	//BGM�Đ�
	pSound->Play(pSound->SOUND_LABEL_BGM001);

	return S_OK;
}

//==============================================================
//�I������
//==============================================================
void CTutorial::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	//BGM�̒�~
	pSound->Stop();

	//�I�u�W�F�N�g2D�̔j��
	for (int nCntTex = 0; nCntTex < NUM_TUTORIAL_TEX; nCntTex++)
	{
		if (m_pObject2D[nCntTex] != NULL)
		{
			m_pObject2D[nCntTex]->Uninit();
			m_pObject2D[nCntTex] = NULL;
		}
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

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�X�V����
//==============================================================
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//�p�b�h�̏��擾
	CFade *pFade = CManager::GetFade();			//�t�F�[�h�̏��擾

	//�X�e�b�v����
	CTutorial::Step();

	if (((pInputKeyboard->GetTrigger(DIK_RETURN) == true || 
		pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true) && 
		bReset == false && m_step >= STEP_MAX) ||
		(pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true ||
		pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_START, 0) == true))
	{//ENTER�L�[��������

		//�Q�[�����
		pFade->SetFade(CScene::MODE_GAME);

		bReset = true;
	}
	else
	{
		bReset = false;
	}

}

//==============================================================
//�`�揈��
//==============================================================
void CTutorial::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	for (int nCntTex = 0; nCntTex < NUM_TUTORIAL_TEX; nCntTex++)
	{
		m_pObject2D[nCntTex]->Draw();
	}
}

//==============================================================
//�X�e�b�v����
//==============================================================
void CTutorial::Step(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//�p�b�h�̏��擾
	CTexture *pTexture = CManager::GetTexture();
	CSound *pSound = CManager::GetSound();

	switch (m_step)
	{
	case STEP_SYNOP_FIRST:		//���炷��1

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true)
		{//ENTER�L�[����������

			//BGM�Đ�
			pSound->Play(pSound->SOUND_LABEL_SE_ENTER001);

			m_step++;

			for (int nCntTex = 0; nCntTex < NUM_TUTORIAL_TEX; nCntTex++)
			{
				//�e�N�X�`���̓ǂݍ���
				m_nIdxTexture[0] = pTexture->Regit(m_apFileName[m_step]);

				//�e�N�X�`�����蓖��
				m_pObject2D[nCntTex]->BindTexture(m_nIdxTexture[nCntTex]);
			}
		}

		break;

	case STEP_SYNOP_SECOND:		//���炷��2

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true)
		{//ENTER�L�[����������

			m_step++;

			//BGM�Đ�
			pSound->Play(pSound->SOUND_LABEL_SE_ENTER001);

			for (int nCntTex = 0; nCntTex < NUM_TUTORIAL_TEX; nCntTex++)
			{
				//�e�N�X�`���̓ǂݍ���
				m_nIdxTexture[0] = pTexture->Regit(m_apFileName[m_step]);

				//�e�N�X�`�����蓖��
				m_pObject2D[nCntTex]->BindTexture(m_nIdxTexture[nCntTex]);
			}
		}

		break;

	case STEP_SYNOP_THIRD:		//���炷��3

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true)
		{//ENTER�L�[����������

			//BGM�Đ�
			pSound->Play(pSound->SOUND_LABEL_SE_ENTER001);

			m_step++;

			for (int nCntTex = 0; nCntTex < NUM_TUTORIAL_TEX; nCntTex++)
			{
				//�e�N�X�`���̓ǂݍ���
				m_nIdxTexture[0] = pTexture->Regit(m_apFileName[m_step]);

				//�e�N�X�`�����蓖��
				m_pObject2D[nCntTex]->BindTexture(m_nIdxTexture[nCntTex]);
			}
		}

		break;

	case STEP_SYNOP_FORTH:		//���炷��4

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true)
		{//ENTER�L�[����������

			//BGM�Đ�
			pSound->Play(pSound->SOUND_LABEL_SE_ENTER001);

			m_step++;

			//�e�N�X�`���̓ǂݍ���
			m_nIdxTexture[0] = pTexture->Regit(m_apFileName[m_step]);

			//�e�N�X�`�����蓖��
			m_pObject2D[0]->BindTexture(m_nIdxTexture[0]);

			//�ʒu�ݒ�
			m_pObject2D[0]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(800.0f, 200.0f, 0.0f), 300.0f, 100.0f);
			m_pObject2D[1]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(800.0f, 1000.0f, 0.0f), 300.0f, 100.0f);
			m_pObject2D[2]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(800.0f, 1000.0f, 0.0f), 300.0f, 100.0f);

			//�G�f�B�b�g�̐���
			m_pEdit = CEdit::Create(D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			//�v���C���[�̐���
			m_pPlayerModel = CPlayerModel::Create(D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f));

			//�n��̐���
			CWall::Create(D3DXVECTOR3(300.0f, 100.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		}

		break;

	case STEP_MOVE:		//�ړ����@

		if (pInputKeyboard->GetTrigger(DIK_D) == true ||
			pInputJoyPad->GetPressLX(0).x > 0.0f)
		{//D�L�[����������

			m_bMoveR = true;		//�E�ړ�������Ԃɂ���
			
		}
		else if (pInputKeyboard->GetTrigger(DIK_A) == true ||
			pInputJoyPad->GetPressLX(0).x < 0.0f)
		{//D�L�[����������

			m_bMoveL = true;		//�E�ړ�������Ԃɂ���

		}

		if (m_bMoveR == true && m_bMoveL == true)
		{//�ړ�������

			m_step++;

			//�e�N�X�`���̓ǂݍ���
			m_nIdxTexture[0] = pTexture->Regit(m_apFileName[m_step]);

			//�e�N�X�`�����蓖��
			m_pObject2D[0]->BindTexture(m_nIdxTexture[0]);
		}

		break;

	case STEP_JUMP:		//�W�����v���@

		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
			pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_B, 0) == true)
		{//SPACE�L�[����������

			m_step++;

			//�e�N�X�`���̓ǂݍ���
			m_nIdxTexture[0] = pTexture->Regit(m_apFileName[m_step]);

			//�e�N�X�`�����蓖��
			m_pObject2D[0]->BindTexture(m_nIdxTexture[0]);
		}

		break;

	case STEP_BULLET:		//������

		if (pInputJoyPad->GetPressRX(0).y == 0.0f && pInputJoyPad->GetPressRX(0).x == 0.0f)
		{
			m_bPad = false;		//�X�e�B�b�N��|���ĂȂ���Ԃɂ���
		}

		if (pInputKeyboard->GetTrigger(DIK_J) == true ||
			pInputKeyboard->GetTrigger(DIK_I) == true ||
			pInputKeyboard->GetTrigger(DIK_K) == true ||
			pInputKeyboard->GetTrigger(DIK_L) == true ||
			pInputKeyboard->GetTrigger(DIK_U) == true ||
			pInputKeyboard->GetTrigger(DIK_M) == true ||
			pInputKeyboard->GetTrigger(DIK_O) == true ||
			pInputKeyboard->GetTrigger(DIK_PERIOD) == true ||
			(pInputJoyPad->GetPressRX(0).x < 0.0f && m_bPad == false) ||
			(pInputJoyPad->GetPressRX(0).x > 0.0f && m_bPad == false) ||
			(pInputJoyPad->GetPressLX(0).y > 0.0f && m_bPad == false) ||
			(pInputJoyPad->GetPressLX(0).y < 0.0f && m_bPad == false))
		{//J�L�[����������

			m_bPad = true;
			m_nNumBullet++;
		}

		if (m_nNumBullet >= 5)
		{
			m_step++;

			//�e�N�X�`���̓ǂݍ���
			m_nIdxTexture[0] = pTexture->Regit(m_apFileName[m_step]);

			//�e�N�X�`�����蓖��
			m_pObject2D[0]->BindTexture(m_nIdxTexture[0]);

			//�ʒu�ݒ�
			m_pObject2D[0]->SetPosition(CObject::TYPE_NONE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
			m_pObject2D[1]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(1180.0f, 680.0f, 0.0f), 90.0f, 45.0f);
			m_pObject2D[2]->SetPosition(CObject::TYPE_EFFECT, D3DXVECTOR3(1100.0f, 60.0f, 0.0f), 150.0f, 40.0f);

		}

		break;

	case STEP_RULE:		//���[��

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true)
		{//ENTER�L�[����������

			//BGM�Đ�
			pSound->Play(pSound->SOUND_LABEL_SE_ENTER001);

			m_step++;
		}

		break;
	}
}