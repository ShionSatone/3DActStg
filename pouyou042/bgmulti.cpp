//==============================================================
//
//���d�w�i����[bgmulti.cpp]
//Author:����������
//
//==============================================================
#include "bgmulti.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "object.h"
#include "texture.h"

//�}�N����`
#define WIDTH_MULTI		(SCREEN_WIDTH * 0.5f)		//����
#define HEIGHT_MULTI	(SCREEN_HEIGHT * 0.5f)		//�c��

//�ÓI�����o�ϐ��錾
CObject2D *CBgMulti::m_apObject2D[NUM_BG] = {};
LPDIRECT3DTEXTURE9 CBgMulti::m_pTexture[NUM_BG] = {};		//�e�N�X�`��

//==============================================================
//�R���X�g���N�^
//==============================================================
CBgMulti::CBgMulti()
{
	//�ϐ�������
	//m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		//�ʒu

	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		m_nIdxTexture[nCntBg] = -1;		//�e�N�X�`���̔ԍ�
		m_aTexV[nCntBg] = 0.0f;
		m_aTexU[nCntBg] = 0.0f;
		m_move[nCntBg] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	}
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBgMulti::~CBgMulti()
{

}

//==============================================================
//���d�w�i�̃e�N�X�`���̓ǂݍ���
//==============================================================
HRESULT CBgMulti::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	if (m_pTexture[0] == NULL || m_pTexture[1] == NULL || m_pTexture[2] == NULL)
	{//�e�N�X�`���ݒ肳��ĂȂ��Ƃ�

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg100.png",
			&m_pTexture[0]);

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg101.png",
			&m_pTexture[1]);

		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\bg102.png",
			&m_pTexture[2]);
	}

	return S_OK;
}

//==============================================================
//���d�w�i�̃e�N�X�`���̔j��
//==============================================================
void CBgMulti::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}
}

//==============================================================
//��������
//==============================================================
CBgMulti *CBgMulti::Create(void)
{
	CBgMulti *pBgMulti = NULL;

	if (pBgMulti == NULL)
	{//���������g�p����ĂȂ�������

		//���d�w�i�̐���
		pBgMulti = new CBgMulti;

		//����������
		pBgMulti->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//��ސݒ�
		pBgMulti->SetType(TYPE_NONE);
	}

	return pBgMulti;
}

//==============================================================
//���d�w�i�̏���������
//==============================================================
HRESULT CBgMulti::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture[0] = pTexture->Regit("data\\TEXTURE\\bg100.png");
	m_nIdxTexture[1] = pTexture->Regit("data\\TEXTURE\\bg101.png");
	m_nIdxTexture[2] = pTexture->Regit("data\\TEXTURE\\bg102.png");

	//���������u
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		if (m_apObject2D[nCntBg] == NULL)
		{//�g�p����ĂȂ��Ƃ�

			//2D�I�u�W�F�N�g����
			m_apObject2D[nCntBg] = CObject2D::Create();

			if (m_apObject2D[nCntBg] != NULL)
			{//�����o������

				//�傫���ݒ�
				m_apObject2D[nCntBg]->SetSize(WIDTH_MULTI, HEIGHT_MULTI);

				//�e�N�X�`�����蓖��
				m_apObject2D[nCntBg]->BindTexture(m_nIdxTexture[nCntBg]);
			}
		}
	}

	//�ړ��ʐݒ�
	m_move[0].x = 0.001f;
	m_move[1].x = 0.005f;
	m_move[2].x = 0.002f;

	m_move[0].y = 0.001f;
	m_move[1].y = 0.005f;
	m_move[2].y = 0.002f;

	//��ސݒ�
	CObject::SetType(CObject::TYPE_NONE);

	return S_OK;
}

//==============================================================
//���d�w�i�̏I������
//==============================================================
void CBgMulti::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		if (m_apObject2D[nCntBg] != NULL)
		{//�g�p����Ă�Ƃ�

			//�I������
			m_apObject2D[nCntBg]->Uninit();
			m_apObject2D[nCntBg] = NULL;
		}
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//���d�w�i�̍X�V����
//==============================================================
void CBgMulti::Update(void)
{
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		if (m_apObject2D[nCntBg] != NULL)
		{
			m_aTexU[nCntBg] += m_move[nCntBg].x;
			//m_aTexV[nCntBg] += m_move[nCntBg].y;

			//�ʒu�̐ݒ�
			m_apObject2D[nCntBg]->SetPosition(CObject::TYPE_NONE, D3DXVECTOR3(0.0f,0.0f,0.0f), WIDTH_MULTI, HEIGHT_MULTI);
			m_apObject2D[nCntBg]->SetType(m_aTexU[nCntBg], m_aTexV[nCntBg]);

			//�ʒu��������߂�
			if (m_aTexU[nCntBg] > 1.0f)
			{
				m_aTexV[nCntBg] = 0.0f;

			}
			else if (m_aTexV[nCntBg] < 0.0f)
			{
				m_aTexV[nCntBg] = 1.0f;
			}
			else if (m_aTexV[nCntBg] > 1.0f)
			{
				m_aTexV[nCntBg] = 0.0f;

			}
			else if (m_aTexU[nCntBg] < 0.0f)
			{
				m_aTexV[nCntBg] = 1.0f;
			}
		}
	}

}

//==============================================================
//���d�w�i�̕`�揈��
//==============================================================
void CBgMulti::Draw(void)
{
	
}

//==============================================================
//�e�N�X�`�����蓖�ď���
//==============================================================
void CBgMulti::BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount)
{
	m_pTexture[nCount] = pTexture;		//�e�N�X�`�����蓖��
}