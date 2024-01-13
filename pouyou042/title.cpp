//==============================================================
//
//�^�C�g������[title.cpp]
//Author:����������
//
//==============================================================
#include "title.h"
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
#include "bg.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "titleTexture.h"
#include "ranking.h"

//�}�N����`
#define TRANS_TIME		(60 * 10)			//�J�ڂ���܂ł̎���

//�ÓI�����o�ϐ��錾
CEdit *CTitle::m_pEdit = NULL;				//�G�f�B�b�g�̏��
bool CTitle::bReset = true;				//���Z�b�g�������ǂ���

//==============================================================
//�R���X�g���N�^
//==============================================================
CTitle::CTitle()
{
	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//�e�N�X�`���ԍ�
	}

	m_nCntTrans = 0;				//�J�ڂ���܂ł̎���
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CTitle::~CTitle()
{

}

//==============================================================
//����������
//==============================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CCamera *pCamera = CManager::GetCamera();		//�J�����̏��擾
	CSound *pSound = CManager::GetSound();
	CTexture *pTexture = CManager::GetTexture();

	//�J�����̏���������
	pCamera->Init();

	//�G�f�B�b�g�̐���
	m_pEdit = CEdit::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�ǂ̐���
	CWall::Create(D3DXVECTOR3(350.0f, 100.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//�^�C�g���̃e�N�X�`��
	CTitleTex::Create();

	if (CManager::GetBgm() == false)
	{

		//BGM�Đ�
		pSound->Play(pSound->SOUND_LABEL_BGM000);
	}

	return S_OK;
}

//==============================================================
//�I������
//==============================================================
void CTitle::Uninit(void)
{
	//�G�f�B�b�g
	if (m_pEdit != NULL)
	{
		m_pEdit->Uninit();
		m_pEdit = NULL;
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�X�V����
//==============================================================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CFade *pFade = CManager::GetFade();		//�t�F�[�h�̏��擾

	if (m_nCntTrans >= TRANS_TIME)
	{//�J�ڂ��鎞�ԂɂȂ�����

		CManager::SetBgm(true);
		pFade->SetFade(CScene::MODE_RANKING);

		//CRanking *pRanking = CScene::GetRanking();		//�����L���O�̏��擾
		//pRanking->SetSound(true);
	}

	m_nCntTrans++;
}

//==============================================================
//�`�揈��
//==============================================================
void CTitle::Draw(void)
{
	
}