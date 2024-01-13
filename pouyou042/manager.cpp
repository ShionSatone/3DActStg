//==============================================================
//
//�}�l�[�W������[manager.cpp]
//Author:����������
//
//==============================================================
#include "manager.h"
#include "object.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "texture.h"
#include "material.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "fade.h"

//�ÓI�����o�ϐ��錾
CRenderer *CManager::m_pRenderer = NULL;		//�����_���[�̏��
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	//�L�[�{�[�h�̏��
CInputJoyPad *CManager::m_pInputJoyPad = NULL;		//�Q�[���p�b�h�̏��
CTexture *CManager::m_pTexture = NULL;			//�e�N�X�`���̏��
CMaterial *CManager::m_pMaterial = NULL;		//�}�e���A���̏��

CPlayer *CManager::m_pPlayer = NULL;			//�v���C���[�̏��
CSound *CManager::m_pSound = NULL;				//�T�E���h�̏��
CDebugProc *CManager::m_pDebugProc = NULL;		//�f�o�b�O�\���̏��

CCamera *CManager::m_pCamera = NULL;			//�J�����̏��
CLight *CManager::m_pLight = NULL;				//���C�g�̏��
CScene *CManager::m_pScene = NULL;				//�V�[���̏��
CFade *CManager::m_pFade = NULL;				//�t�F�[�h�̏��

int CManager::m_nScore = 0;						//�X�R�A
bool CManager::m_bBgm = false;					//BGM�X�g�b�v���邩
bool CManager::m_bResult = true;				//���U���g�̔���

CTitle *CScene::m_pTitle = NULL;			//�^�C�g����ʂ̏��
CTutorial *CScene::m_pTutorial = NULL;		//�`���[�g���A�����
CGame *CScene::m_pGame = NULL;				//�Q�[����ʂ̏��
CResult *CScene::m_pResult = NULL;			//���U���g��ʂ̏��
CRanking *CScene::m_pRanking = NULL;		//�����L���O��ʂ̏��
//==============================================================
//�V�[���̃R���X�g���N�^
//==============================================================
CScene::CScene()
{
	m_mode = MODE_TITLE;		//�Q�[�����[�h
}

//==============================================================
//�V�[���̃R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CScene::CScene(MODE mode)
{
	m_mode = mode;		//�Q�[�����[�h
}

//==============================================================
//�V�[���̃f�X�g���N�^
//==============================================================
CScene::~CScene()
{

}

//==============================================================
//�V�[���̐�������
//==============================================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = NULL;

	if (pScene == NULL)
	{//���������g�p����ĂȂ�������

		//�w�肳�ꂽ���[�h�𐶐�
		pScene = new CScene(mode);
	}

	////����������
	//pScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pScene;
}

//==============================================================
//�V�[���̏���������
//==============================================================
HRESULT CScene::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	switch (m_mode)
	{
	case MODE_TITLE:		//�^�C�g�����

		//�^�C�g����ʂ̐���
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;

			if (m_pTitle != NULL)
			{
				//�Q�[����ʂ̏�����
				if (FAILED(m_pTitle->Init(pos, rot)))
				{//���������������s�����ꍇ

					return E_FAIL;
				}
			}
		}

		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����

		//�`���[�g���A����ʂ̐���
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;

			if (m_pTutorial != NULL)
			{
				//�Q�[����ʂ̏�����
				if (FAILED(m_pTutorial->Init(pos, rot)))
				{//���������������s�����ꍇ

					return E_FAIL;
				}
			}
		}

		break;

	case MODE_GAME:			//�Q�[�����

		//�Q�[����ʂ̐���
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;

			if (m_pGame != NULL)
			{
				//�Q�[����ʂ̏�����
				if (FAILED(m_pGame->Init(pos, rot)))
				{//���������������s�����ꍇ

					return E_FAIL;
				}
			}
		}

		break;

	case MODE_RESULT:		//���U���g���

		//���U���g��ʂ̐���
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;

			if (m_pResult != NULL)
			{
				//�Q�[����ʂ̏�����
				if (FAILED(m_pResult->Init(pos, rot)))
				{//���������������s�����ꍇ

					return E_FAIL;
				}
			}
		}

		break;

	case MODE_RANKING:		//�����L���O���

		//�����L���O��ʂ̐���
		if (m_pRanking == NULL)
		{
			m_pRanking = new CRanking;

			if (m_pRanking != NULL)
			{
				//�Q�[����ʂ̏�����
				if (FAILED(m_pRanking->Init(pos, rot)))
				{//���������������s�����ꍇ

					return E_FAIL;
				}
			}
		}

		break;
	}


	return S_OK;
}

//==============================================================
//�V�[���̏I������
//==============================================================
void CScene::Uninit(void)
{
	switch (m_mode)
	{
	case MODE_TITLE:		//�^�C�g�����

		//�^�C�g����ʂ̔j��
		if (m_pTitle != NULL)
		{
			//�I������
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}

		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����

		//�`���[�g���A����ʂ̔j��
		if (m_pTutorial != NULL)
		{
			//�I������
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}

		break;

	case MODE_GAME:			//�Q�[�����

		//�Q�[����ʂ̔j��
		if (m_pGame != NULL)
		{
			//�I������
			m_pGame->Uninit();
			m_pGame = NULL;
		}

		break;

	case MODE_RESULT:		//���U���g���

		//���U���g��ʂ̔j��
		if (m_pResult != NULL)
		{
			//�I������
			m_pResult->Uninit();
			m_pResult = NULL;
		}

		break;

	case MODE_RANKING:		//�����L���O���

		//�����L���O��ʂ̔j��
		if (m_pRanking != NULL)
		{
			//�I������
			m_pRanking->Uninit();
			m_pRanking = NULL;
		}

		break;
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�V�[���̍X�V����
//==============================================================
void CScene::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	switch (m_mode)
	{
	case MODE_TITLE:		//�^�C�g�����

		pDebugProc->Print("<<<<<<�^�C�g��>>>>>>\n");

		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����

		pDebugProc->Print("<<<<<<�`���[�g���A��>>>>>>\n");

		break;

	case MODE_GAME:			//�Q�[�����

		pDebugProc->Print("<<<<<<�Q�[��>>>>>>\n");

		break;

	case MODE_RESULT:		//���U���g���

		pDebugProc->Print("<<<<<<���U���g>>>>>>\n");

		break;

	case MODE_RANKING:		//�����L���O���

		pDebugProc->Print("<<<<<<�����L���O>>>>>>\n");

		break;
	}
}

//==============================================================
//�V�[���̕`�揈��
//==============================================================
void CScene::Draw(void)
{

}

//==============================================================
//�}�l�[�W���̃R���X�g���N�^
//==============================================================
CManager::CManager()
{

}

//==============================================================
//�}�l�[�W���̃f�X�g���N�^
//==============================================================
CManager::~CManager()
{

}

//==============================================================
//�}�l�[�W���̏���������
//==============================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{//���������g�p����ĂȂ��Ƃ�

		m_pRenderer = new CRenderer;
	}

	//�����_���[�̏���������
	if (m_pRenderer != NULL)
	{//�������m�ۂł��Ă���

		//�����_���[�̏�����
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�f�o�b�O�\���̐���
	if (m_pDebugProc == NULL)
	{//���������g�p����ĂȂ��Ƃ�

		m_pDebugProc = new CDebugProc;
	}

	if (m_pDebugProc != NULL)
	{//���������m�ۂ��ꂽ�Ƃ�

		//�f�o�b�O�\���̏���������
		m_pDebugProc->Init();
	}

	//�L�[�{�[�h�̐���
	if (m_pInputKeyboard == NULL)
	{//�L�[�{�[�h���g�p����ĂȂ��Ƃ�

		m_pInputKeyboard = new CInputKeyboard;
	}

	if (m_pInputKeyboard != NULL)
	{//�������m�ۂł��Ă���

		//�L�[�{�[�h�̏�����
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�Q�[���p�b�h�̐���
	if (m_pInputJoyPad == NULL)
	{
		m_pInputJoyPad = new CInputJoyPad;
	}

	if (m_pInputJoyPad != NULL)
	{//�������m�ۂł��Ă���

		//�p�b�h�̏�����
		if (FAILED(m_pInputJoyPad->Init(hInstance, hWnd)))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
	}

	if (m_pCamera != NULL)
	{//�������m�ۂł��Ă���

		//�J�����̏�����
		if (FAILED(m_pCamera->Init()))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
	}

	if (m_pLight != NULL)
	{//�������m�ۂł��Ă���

		//���C�g�̏�����
		if (FAILED(m_pLight->Init()))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�T�E���h�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	if (m_pSound != NULL)
	{//�������m�ۂł��Ă���

		//�T�E���h�̏�����
		if (FAILED(m_pSound->Init(hWnd)))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�e�N�X�`���̐���
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;
	}

	if (m_pTexture != NULL)
	{//�������m�ۂł��Ă���

		//�e�N�X�`���̓ǂݍ���
		if (FAILED(m_pTexture->Load()))
		{//�ǂݍ��݂����s�����ꍇ

			return E_FAIL;
		}
	}

	//�}�e���A���̐���
	if (m_pMaterial == NULL)
	{
		m_pMaterial = new CMaterial;
	}

	if (m_pMaterial != NULL)
	{//�������m�ۂł��Ă���

		//�}�e���A���̓ǂݍ���
		if (FAILED(m_pMaterial->Load()))
		{//�ǂݍ��݂����s�����ꍇ

			return E_FAIL;
		}
	}

	//�V�[���̐�������
	if (m_pScene == NULL)
	{
#if _DEBUG

		m_pScene = CScene::Create(CScene::MODE_TITLE);

#else

		m_pScene = CScene::Create(CScene::MODE_TITLE);

#endif
	}

	if (m_pScene != NULL)
	{//�������m�ۂł�����

		//�V�[���̏���������
		if (FAILED(m_pScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f))))
		{//�ǂݍ��݂����s�����ꍇ

			return E_FAIL;
		}
	}

	//�t�F�[�h�̐�������
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create();
	}
	
	return S_OK;
}

//==============================================================
//�}�l�[�W���̏I������
//==============================================================
void CManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	//�S�Ẵe�N�X�`���̔j��
	if (m_pMaterial != NULL)
	{
		//�e�N�X�`���̏I������
		m_pMaterial->Unload();

		delete m_pMaterial;
		m_pMaterial = NULL;
	}

	//�S�Ẵe�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̏I������
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}

	//�t�F�[�h�̔j��
	//if (m_pFade != NULL)
	//{
	//	//�t�F�[�h�̏I������
	//	m_pFade->Uninit();

	//	delete m_pFade;
	//	m_pFade = NULL;
	//}

	//�V�[���̔j��
	//if (m_pScene != NULL)
	//{
	//	//�V�[���̏I������
	//	m_pScene->Uninit();

	//	delete m_pScene;
	//	m_pScene = NULL;
	//}

	//�T�E���h�̔j��
	if (m_pSound != NULL)
	{
		//�T�E���h�̏I������
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	//�L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		//�L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�Q�[���p�b�h�̔j��
	if (m_pInputJoyPad != NULL)
	{
		//�Q�[���p�b�h�̏I������
		m_pInputJoyPad->Uninit();

		delete m_pInputJoyPad;
		m_pInputJoyPad = NULL;
	}

	//���C�g�̔j��
	if (m_pLight != NULL)
	{
		//���C�g�̏I������
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	//�J�����̔j��
	if (m_pCamera != NULL)
	{
		//�J�����̏I������
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	//�f�o�b�O�\���̔j��
	if (m_pDebugProc != NULL)
	{
		//�f�o�b�O�\���̏I������
		m_pDebugProc->Uninit();

		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		//�����_���[�̏I������
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//==============================================================
//�}�l�[�W���̍X�V����
//==============================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	//�Q�[���p�b�h�̍X�V����
	m_pInputJoyPad->Update();

	//�f�o�b�O�\���̍X�V����
	m_pDebugProc->Update();

	//�}�b�v�̍Đ���
	CManager::ResetMap();

	//�����_���[�̍X�V����
	m_pRenderer->Update();

	//�J�����̍X�V����
	m_pCamera->Update();
}

//==============================================================
//�}�l�[�W���̕`�揈��
//==============================================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//==============================================================
//�Q�[�����[�h�̐ݒ菈��
//==============================================================
void CManager::SetMode(CScene::MODE mode)
{
	//if (CManager::GetMode() != CScene::MODE_RESULT && )
	//{
	//	//�T�E���h�̒�~
	//	m_pSound->Stop();
	//}

	//���݂̃��[�h�̔j��
	if (m_pScene != NULL)
	{
		//�S�Ă̏I������
		CObject::DeathAll();
	}

	//�V�������[�h�̐���
	m_pScene = CScene::Create(mode);

	//����������
	m_pScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�t�F�[�h�̐�������
	m_pFade = CFade::Create();
}

//==============================================================
//�Q�[�����[�h�̎擾����
//==============================================================
CScene::MODE CManager::GetMode(void)
{
	return m_pScene->GetMode();
}

//==============================================================
//�}�b�v�̔z�u���Z�b�g
//==============================================================
void CManager::ResetMap(void)
{
	//���Z�b�g
	if (m_pInputKeyboard->GetPress(DIK_F2) == true)
	{//F2���������Ƃ�

		//�}�b�v�̃I�u�W�F�N�g�̃��Z�b�g
		CObject::ResetMapAll();

		////�I�u�W�F�N�g3D�̐���
		//CManager::Create3DAll();
	}
}