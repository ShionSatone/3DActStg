//==============================================================
//
//�����̏���[explosion.cpp]
//Author:����������
//
//==============================================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"

//�}�N����`
#define WIDTH_EXPLOSION		(60.0f * 0.5f)		//�����̉���
#define HEIGHT_EXPLOSION	(60.0f * 0.5f)		//�����̏c��
#define NUM_PATTERN			(10)				//�p�^�[����
#define MOVE_SPEED			(3.0f)				//�����̈ړ����x
#define ANGLE_UP			(0.75f)				//��̊p�x
#define ANGLE_DOWN			(0.25f)				//���̊p�x
#define ANGLE_WIDTH			(0.5f)				//���̊p�x
#define DEST_EXPLOSION		(10)				//���������ł���܂ł̎���

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;		//�e�N�X�`��

//==============================================================
//�R���X�g���N�^
//==============================================================
CExplosion::CExplosion()
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_nCntdest = DEST_EXPLOSION;		//�������ł̎���
	m_nPatternAnim = 0;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CExplosion::~CExplosion()
{

}

//==============================================================
//�����̃e�N�X�`���̓ǂݍ���
//==============================================================
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	if (m_pTexture == NULL)
	{//�e�N�X�`���ݒ肳��ĂȂ��Ƃ�

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\explosion000.png",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//�����̃e�N�X�`���̔j��
//==============================================================
void CExplosion::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//�����̐�������
//==============================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CExplosion *pExplosion = NULL;

	if (pExplosion == NULL)
	{//���������g�p����ĂȂ�������

		//�����̐���
		pExplosion = new CExplosion;
	}

	//����������
	pExplosion->Init(pos, rot);

	return pExplosion;
}

//==============================================================
//�����̏���������
//==============================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\explosion000.png");

	//�e�N�X�`���̊��蓖��
	CBillboard::BindTexture(m_nIdxTexture);

	//�r���{�[�h�̏���������
	CBillboard::Init(pos, rot);

	///�����̏����ݒ�
	//�����̑傫���ݒ�
	CBillboard::SetSize(WIDTH_EXPLOSION, HEIGHT_EXPLOSION);

	return S_OK;
}

//==============================================================
//�����̏I������
//==============================================================
void CExplosion::Uninit(void)
{
	//�r���{�[�h�̏I������
	CBillboard::Uninit();
}

//==============================================================
//�����̍X�V����
//==============================================================
void CExplosion::Update(void)
{
	//�ʒu�擾
	m_pos = CBillboard::GetPosition();

	//�ʒu�ݒ�
	CBillboard::SetPosition(CObject::TYPE_EXPLOSION, m_pos);

	//�r���{�[�h�̍X�V����
	CBillboard::Update();

	if ((m_nCounterAnim % 1) == 0)
	{//��莞�Ԍo��

		//�p�^�[��No.���X�V����
		m_nPatternAnim++;
	
		CBillboard::SetType(TYPE_EXPLOSION, m_nPatternAnim);
	}

	if (m_nPatternAnim == NUM_PATTERN)
	{//�p�^�[���̍ő�ɒB������

		//�����폜
		CExplosion::Uninit();
	}
}

//==============================================================
//�����̕`�揈��
//==============================================================
void CExplosion::Draw(void)
{
	//�r���{�[�h�̕`�揈��
	CBillboard::Draw();
}