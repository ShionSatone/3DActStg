//==============================================================
//
//�G�̏���[enemy.cpp]
//Author:����������
//
//==============================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "explosion.h"
#include "particle.h"
#include "texture.h"

//�}�N����`
#define NUM_PATTERN		(10)				//�p�^�[����
#define MOVE_SPEED		(3.0f)				//�G�̈ړ����x
#define ANGLE_UP		(0.75f)				//��̊p�x
#define ANGLE_DOWN		(0.25f)				//���̊p�x
#define ANGLE_WIDTH		(0.5f)				//���̊p�x
#define DEST_ENEMY		(70)				//�G�����ł���܂ł̎���

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;		//�e�N�X�`��

//==============================================================
//�R���X�g���N�^
//==============================================================
CEnemy::CEnemy()
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ړ���
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CEnemy::~CEnemy()
{

}

//==============================================================
//�G�̃e�N�X�`���̓ǂݍ���
//==============================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	if (m_pTexture == NULL)
	{//�e�N�X�`���ݒ肳��ĂȂ��Ƃ�

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\enemy000.png",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//�G�̃e�N�X�`���̔j��
//==============================================================
void CEnemy::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//�G�̐�������
//==============================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = NULL;

	if (pEnemy == NULL)
	{//���������g�p����ĂȂ�������

		//�G�̐���
		pEnemy = new CEnemy;

		if (pEnemy != NULL)
		{//�������m�ۂł��Ă���

			//����������
			pEnemy->Init(pos, rot);
		}
	}

	return pEnemy;
}

//==============================================================
//�G�̏���������
//==============================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\enemy000.png");

	//�e�N�X�`���̊��蓖��
	CObject2D::BindTexture(m_nIdxTexture);

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init(pos, rot);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_ENEMY);

	///�G�̏����ݒ�
	//�G�̑傫���ݒ�
	CObject2D::SetSize(WIDTH_ENEMY, HEIGHT_ENEMY);

	return S_OK;
}

//==============================================================
//�G�̏I������
//==============================================================
void CEnemy::Uninit(void)
{
	//2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//==============================================================
//�G�̍X�V����
//==============================================================
void CEnemy::Update(void)
{
	//�I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	//�ʒu�擾
	m_pos = CObject2D::GetPosition();

	//�ʒu�ݒ�
	CObject2D::SetPosition(CObject::TYPE_ENEMY, m_pos, WIDTH_ENEMY, HEIGHT_ENEMY);
}

//==============================================================
//�G�̕`�揈��
//==============================================================
void CEnemy::Draw(void)
{
	//2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}