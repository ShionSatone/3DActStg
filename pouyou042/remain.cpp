//==============================================================
//
//�c�@����[remain.cpp]
//Author:����������
//
//==============================================================
#include "remain.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "texture.h"

//�}�N����`
#define WIDTH_REMAIN	(50.0f * 0.5f)		//�c�@�̉���
#define HEIGHT_REMAIN	(50.0f * 0.5f)		//�c�@�̏c��
#define NUM_PATTERN		(10)				//�p�^�[����
#define MOVE_SPEED		(3.0f)				//�c�@�̈ړ����x
#define ANGLE_UP		(0.75f)				//��̊p�x
#define ANGLE_DOWN		(0.25f)				//���̊p�x
#define ANGLE_WIDTH		(0.5f)				//���̊p�x

//�ÓI�����o�ϐ��錾
int CRemain::m_nNum = 0;		//�c�@�̐�

//==============================================================
//�R���X�g���N�^
//==============================================================
CRemain::CRemain()
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ړ���
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CRemain::~CRemain()
{

}

//==============================================================
//�c�@�̐�������
//==============================================================
CRemain *CRemain::Create(D3DXVECTOR3 pos, int nIdx)
{
	CRemain *pRemain = NULL;

	if (pRemain == NULL)
	{//���������g�p����ĂȂ�������

		//�c�@�̐���
		pRemain = new CRemain;
	}

	if (pRemain != NULL)
	{//�������m�ۂł��Ă���

		//����������
		pRemain->Init(pos, D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	return pRemain;
}

//==============================================================
//�c�@�̏���������
//==============================================================
HRESULT CRemain::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\item000.png");

	//�e�N�X�`���̊��蓖��
	CObject2D::BindTexture(m_nIdxTexture);

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init(pos, rot);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_ITEM);

	///�c�@�̏����ݒ�
	//�c�@�̑傫���ݒ�
	CObject2D::SetSize(WIDTH_REMAIN, HEIGHT_REMAIN);

	return S_OK;
}

//==============================================================
//�c�@�̏I������
//==============================================================
void CRemain::Uninit(void)
{
	//2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//==============================================================
//�c�@�̍X�V����
//==============================================================
void CRemain::Update(void)
{
	//�I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	////�ʒu�擾
	//m_pos = CObject2D::GetPosition();

	////�ʒu�ݒ�
	//CObject2D::SetPosition(CObject::TYPE_ITEM, m_pos, WIDTH_REMAIN, HEIGHT_REMAIN);
}

//==============================================================
//�c�@�̕`�揈��
//==============================================================
void CRemain::Draw(void)
{
	//2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}