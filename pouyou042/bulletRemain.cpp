//==============================================================
//
//�c�e���\������[bulletRemain.h]
//Author:����������
//
//==============================================================
#include "bulletRemain.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "game.h"
#include "life.h"

//�}�N����`
#define WIDTH_BR		(400.0f)		//�c�e���̉���
#define HEIGHT_BR		(50.0f)			//�c�e���̏c��
#define NUM_PATTERN		(10)			//�p�^�[����
#define MOVE_SPEED		(3.0f)			//�c�e���̈ړ����x
#define LIFE_CNT		(60)			//���C�t���炷�J�E���g

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CBulletRemain::m_pTexture = NULL;		//�e�N�X�`��

//==============================================================
//�R���X�g���N�^
//==============================================================
CBulletRemain::CBulletRemain()
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ړ���

	m_nNumBullet = 0;		//�e���
	m_nCntLife = LIFE_CNT;			//�̗͌��炷�J�E���^�[
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CBulletRemain::CBulletRemain(D3DXVECTOR3 pos)
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�

	m_pos = pos;		//�ʒu

	m_nCntLife = LIFE_CNT;			//�̗͌��炷�J�E���^�[
	m_nNumBullet = 0;		//�e���
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBulletRemain::~CBulletRemain()
{

}

//==============================================================
//�c�e���̐�������
//==============================================================
CBulletRemain *CBulletRemain::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBulletRemain *pBulletRemain = NULL;

	if (pBulletRemain == NULL)
	{//���������g�p����ĂȂ�������

		//�c�e���̐���
		pBulletRemain = new CBulletRemain(pos);
	}

	if (pBulletRemain != NULL)
	{//�������m�ۂł��Ă���

		//����������
		pBulletRemain->Init(pos, rot);
	}

	return pBulletRemain;
}

//==============================================================
//�c�e���̏���������
//==============================================================
HRESULT CBulletRemain::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\BR00.png");

	//�e�N�X�`���̊��蓖��
	CObject2D::BindTexture(m_nIdxTexture);

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init(m_pos, rot);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_BLOCK);

	///�c�e���̏����ݒ�
	//�c�e���̑傫���ݒ�
	CObject2D::SetSize(WIDTH_BR, HEIGHT_BR);

	//�ʒu�ݒ�
	CObject2D::SetPosition(CObject::TYPE_BLOCK, m_pos, WIDTH_BR - m_nNumBullet, HEIGHT_BR);

	return S_OK;
}

//==============================================================
//�c�e���̏I������
//==============================================================
void CBulletRemain::Uninit(void)
{
	//2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�c�e���̍X�V����
//==============================================================
void CBulletRemain::Update(void)
{
	CLife *pLife = CGame::GetLife();

	//�I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	//�ʒu�ݒ�
	CObject2D::SetPosition(CObject::TYPE_BLOCK, m_pos, WIDTH_BR - m_nNumBullet, HEIGHT_BR);

	if (m_nNumBullet >= WIDTH_BR)
	{//�e���Ȃ��Ȃ�����

		if (m_nCntLife >= LIFE_CNT)
		{
			//�̗͌��炷
			pLife->SetNum(-40);

			m_nCntLife = 0;
		}

		m_nCntLife++;
	}
}

//==============================================================
//�c�e���̕`�揈��
//==============================================================
void CBulletRemain::Draw(void)
{
	//2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}

//==============================================================
//�e���ݒ菈��
//==============================================================
void CBulletRemain::SetNumBullet(int nNumBullet)
{
	if (nNumBullet < 0)
	{//�񕜂���Ƃ�

		if ((m_nNumBullet + nNumBullet) > 0)
		{//�e�̏���ȓ��̏ꍇ

			m_nNumBullet += nNumBullet;
		}
		else if ((m_nNumBullet + nNumBullet) <= 0)
		{//�e�̏��������ꍇ

			m_nNumBullet = 0;
		}
	}
	else if (nNumBullet >= 0)
	{//�����Ƃ�

		m_nNumBullet += nNumBullet;
	}
}