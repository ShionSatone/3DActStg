//==============================================================
//
//�̗͕\������[life.h]
//Author:����������
//
//==============================================================
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "particle.h"
#include "playerModel.h"
#include "game.h"

//�}�N����`
#define WIDTH_LIFE		(400.0f)		//�̗͕\���̉���
#define HEIGHT_LIFE		(20.0f)			//�̗͕\���̏c��

//�ÓI�����o�ϐ��錾
CObject2D *CLife::m_apObject2D[NUM_LIFE_FRAME] = {};		//�I�u�W�F�N�g2D�̏��

//==============================================================
//�R���X�g���N�^
//==============================================================
CLife::CLife()
{
	for (int nCntTex = 0; nCntTex < NUM_LIFE_FRAME; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//�e�N�X�`���̔ԍ�
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ړ���

	m_nNumCon = 0;		//�̗͏��
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CLife::CLife(D3DXVECTOR3 pos)
{
	for (int nCntTex = 0; nCntTex < NUM_LIFE_FRAME; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//�e�N�X�`���̔ԍ�
	}

	m_pos = pos;		//�ʒu

	m_nNumCon = 0;		//�̗͏��
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CLife::~CLife()
{

}

//==============================================================
//�̗͕\���̐�������
//==============================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CLife *pLife = NULL;

	if (pLife == NULL)
	{//���������g�p����ĂȂ�������

		//�̗͕\���̐���
		pLife = new CLife(pos);
	}

	if (pLife != NULL)
	{//�������m�ۂł��Ă���

		//����������
		pLife->Init(pos, rot);
	}

	return pLife;
}

//==============================================================
//�̗͕\���̏���������
//==============================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture[0] = pTexture->Regit("data\\TEXTURE\\life.jpg");
	m_nIdxTexture[1] = pTexture->Regit("data\\TEXTURE\\life01.png");

	//���������u
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		if (m_apObject2D[nCntLife] == NULL)
		{//�g�p����ĂȂ��Ƃ�

			//2D�I�u�W�F�N�g����
			m_apObject2D[nCntLife] = CObject2D::Create();

			if (m_apObject2D[nCntLife] != NULL)
			{//�����o������

				//�傫���ݒ�
				m_apObject2D[nCntLife]->SetSize(WIDTH_LIFE, HEIGHT_LIFE);

				//�e�N�X�`�����蓖��
				m_apObject2D[nCntLife]->BindTexture(m_nIdxTexture[nCntLife]);

				//�ʒu�ݒ�
				m_apObject2D[nCntLife]->SetPosition(CObject::TYPE_BLOCK, m_pos, WIDTH_LIFE - m_nNumCon, HEIGHT_LIFE);
			}
		}
	}

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_BLOCK);

	return S_OK;
}

//==============================================================
//�̗͕\���̏I������
//==============================================================
void CLife::Uninit(void)
{
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		if (m_apObject2D[nCntLife] != NULL)
		{
			m_apObject2D[nCntLife]->Uninit();
			m_apObject2D[nCntLife] = NULL;
		}
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�̗͕\���̍X�V����
//==============================================================
void CLife::Update(void)
{
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		//�I�u�W�F�N�g2D�̍X�V����
		m_apObject2D[nCntLife]->Update();

		//�ʒu�X�V
		m_apObject2D[0]->SetPosition(CObject::TYPE_BLOCK, m_pos, float(m_nMaxLife - m_nNumCon), HEIGHT_LIFE);
	}
}

//==============================================================
//�̗͕\���̕`�揈��
//==============================================================
void CLife::Draw(void)
{
	for (int nCntLife = 0; nCntLife < NUM_LIFE_FRAME; nCntLife++)
	{
		//2D�I�u�W�F�N�g�̕`�揈��
		m_apObject2D[nCntLife]->Draw();
	}
}

//==============================================================
//�̗͕\���̐ݒ菈��
//==============================================================
void CLife::SetNum(int nNumBullet)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	if (nNumBullet > 0)
	{//�񕜂̏ꍇ

		if ((m_nMaxLife - m_nNumCon) < m_nMaxLife - nNumBullet)
		{//�񕜗ʂ��̗͂�菭�Ȃ��ꍇ

			m_nNumCon -= nNumBullet;
		}
		else
		{
			m_nNumCon = 0;
		}

		//�p�[�e�B�N������
		CParticle::Create(pPlayer->GetPosition(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PARTICLETYPE_LIFE, 30, 15.0f);
	}
	else if ((m_nMaxLife - m_nNumCon) > 0)
	{//�̗͂���������

		m_nNumCon -= nNumBullet;

	}
	else
	{
		//�v���C���[�����S��Ԃɂ���
		pPlayer->SetState(STATE_DEATH);
	}
}