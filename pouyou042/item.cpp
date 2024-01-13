//==============================================================
//
//�A�C�e������[item.h]
//Author:����������
//
//==============================================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "texture.h"

//�}�N����`
#define WIDTH_ITEM		(50.0f * 0.5f)		//�A�C�e���̉���
#define HEIGHT_ITEM		(50.0f * 0.5f)		//�A�C�e���̏c��
#define NUM_PATTERN		(10)				//�p�^�[����
#define MOVE_SPEED		(3.0f)				//�A�C�e���̈ړ����x
#define ANGLE_UP		(0.75f)				//��̊p�x
#define ANGLE_DOWN		(0.25f)				//���̊p�x
#define ANGLE_WIDTH		(0.5f)				//���̊p�x

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CItem::m_pTexture = NULL;		//�e�N�X�`��

//==============================================================
//�R���X�g���N�^
//==============================================================
CItem::CItem()
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ړ���
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CItem::~CItem()
{

}

//==============================================================
//�A�C�e���̃e�N�X�`���̓ǂݍ���
//==============================================================
HRESULT CItem::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	if (m_pTexture == NULL)
	{//�e�N�X�`���ݒ肳��ĂȂ��Ƃ�

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\item000.png",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//�A�C�e���̃e�N�X�`���̔j��
//==============================================================
void CItem::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//�A�C�e���̐�������
//==============================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CItem *pItem = NULL;

	if (pItem == NULL)
	{//���������g�p����ĂȂ�������

		//�A�C�e���̐���
		pItem = new CItem;
	}

	if (pItem != NULL)
	{//�������m�ۂł��Ă���

		//����������
		pItem->Init(pos, rot);
	}

	return pItem;
}

//==============================================================
//�A�C�e���̏���������
//==============================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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

	///�A�C�e���̏����ݒ�
	//�A�C�e���̑傫���ݒ�
	CObject2D::SetSize(WIDTH_ITEM, HEIGHT_ITEM);

	return S_OK;
}

//==============================================================
//�A�C�e���̏I������
//==============================================================
void CItem::Uninit(void)
{
	//2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//==============================================================
//�A�C�e���̍X�V����
//==============================================================
void CItem::Update(void)
{
	//�I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	//�ʒu�擾
	m_pos = CObject2D::GetPosition();

	//�ʒu�ݒ�
	CObject2D::SetPosition(CObject::TYPE_ITEM, m_pos, WIDTH_ITEM, HEIGHT_ITEM);

	//�v���C���[�Ƃ̓����蔻��
	CItem::ColisionPlayer(m_pos);
}

//==============================================================
//�A�C�e���̕`�揈��
//==============================================================
void CItem::Draw(void)
{
	//2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}

//==============================================================
//�v���C���[�Ƃ̓����蔻��
//==============================================================
bool CItem::ColisionPlayer(D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject *pObj;

		//�I�u�W�F�N�g���擾
		pObj = GetObject(nCntObj);

		if (pObj != NULL)
		{//���������g�p����Ă���Ƃ�

			CObject::TYPE type;

			//��ނ��擾
			type = pObj->GetType();

			if (type == pObj->TYPE_PLAYER)
			{//��ނ��v���C���[�̏ꍇ

				//�v���C���[�̈ʒu�擾
				D3DXVECTOR3 posPlayer = pObj->GetPosition();

				if (pos.x >= posPlayer.x - WIDTH_PLAYER && pos.x <= posPlayer.x + WIDTH_PLAYER &&
					pos.y >= posPlayer.y - HEIGHT_PLAYER && pos.y <= posPlayer.y)
				{//�A�C�e���ƃv���C��[����������

					//SE�Đ�
					//CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE000);

					//�e�̏I������
					CObject2D::Uninit();

					return true;
				}
			}

		}
	}

	return false;
}