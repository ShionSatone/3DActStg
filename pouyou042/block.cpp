//==============================================================
//
//�u���b�N�̏���[block.h]
//Author:����������
//
//==============================================================
#include "block.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//�}�N����`
#define NUM_PATTERN		(10)				//�p�^�[����
#define WIDTH_BLOCK		(100.0f)			//�u���b�N�̉���
#define HEIGHT_BLOCK	(100.0f)			//�u���b�N�̏c��
#define MOVE_SPEED		(3.0f)				//�u���b�N�̈ړ����x
#define ANGLE_UP		(0.75f)				//��̊p�x
#define ANGLE_DOWN		(0.25f)				//���̊p�x
#define ANGLE_WIDTH		(0.5f)				//���̊p�x
#define BLOCK_LIFE		(70)				//�u���b�N�����ł���܂ł̎���

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CBlock::m_pTexture = NULL;		//�e�N�X�`��
D3DXVECTOR3 CBlock::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
float CBlock::m_fWidth = 0.0f;
float CBlock::m_fHeight = 0.0f;

//==============================================================
//�R���X�g���N�^
//==============================================================
CBlock::CBlock()
{
	m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	//m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//�ړ���
	m_fWidth = WIDTH_BLOCK;			//��
	m_fHeight = HEIGHT_BLOCK;		//����
	m_nType = 0;				//���
	m_nCounterMove = 0;			//�u���b�N�̓����̃J�E���^�[
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBlock::~CBlock()
{

}

//==============================================================
//�u���b�N�̃e�N�X�`���̓ǂݍ���
//==============================================================
HRESULT CBlock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	if (m_pTexture == NULL)
	{//�e�N�X�`���ݒ肳��ĂȂ��Ƃ�

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\block000.jpg",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//�u���b�N�̃e�N�X�`���̔j��
//==============================================================
void CBlock::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//�u���b�N�̐�������
//==============================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBlock *pBlock = NULL;

	if (pBlock == NULL)
	{//���������g�p����ĂȂ�������

		//�u���b�N�̐���
		pBlock = new CBlock;


		if (pBlock != NULL)
		{//�������m�ۂł��Ă���

			//����������
			pBlock->Init(pos, rot);
		}
	}

	return pBlock;
}

//==============================================================
//�u���b�N�̏���������
//==============================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;

	CTexture *pTexture = CManager::GetTexture();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\block000.jpg");

	//�e�N�X�`���̊��蓖��
	CObject2D::BindTexture(m_nIdxTexture);

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init(pos, rot);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_BLOCK);

	///�u���b�N�̏����ݒ�
	//�u���b�N�̑傫���ݒ�
	CObject2D::SetSize(WIDTH_BLOCK, HEIGHT_BLOCK);

	return S_OK;
}

//==============================================================
//�u���b�N�̏I������
//==============================================================
void CBlock::Uninit(void)
{
	//2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//==============================================================
//�u���b�N�̍X�V����
//==============================================================
void CBlock::Update(void)
{
	//�I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();

	//�ʒu�擾
	m_pos = CObject2D::GetPosition();

	//�ʒu�ݒ�
	CObject2D::SetPosition(CObject::TYPE_BLOCK, m_pos, WIDTH_BLOCK, HEIGHT_BLOCK);
}

//==============================================================
//�u���b�N�̕`�揈��
//==============================================================
void CBlock::Draw(void)
{
	//2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}

//==============================================================
//�u���b�N�̐ݒ菈��
//==============================================================
void CBlock::Set(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight)
{
	m_pos = pos;			//�ʒu
	m_nType = nType;		//���
	m_fWidth = fWidth;		//����
	m_fHeight = fHeight;	//�c��

	//�ʒu�ݒ菈��
	CObject2D::SetPosition(CObject::TYPE_BLOCK, pos, m_fWidth, m_fHeight);
}

//==============================================================
//�u���b�N�̓����蔻��
//==============================================================
bool CBlock::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight/*, Block **pBlock*/)
{
	CPlayer *pPlayer = CManager::GetPlayer();
	bool bLand = false;

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

			if (type == pObj->TYPE_BLOCK)
			{//��ނ��u���b�N�̏ꍇ

				//�u���b�N�̈ʒu�擾
				D3DXVECTOR3 posBlock = pObj->GetPosition();

				if (pPosOld->y <= posBlock.y && pPos->y > posBlock.y &&
					pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
				{//�u���b�N�̏�ɂ߂荞��

					if (pPosOld->x + fWidth <= posBlock.x && pPos->x + fWidth > posBlock.x &&
						pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
					{//�u���b�N�̍��ɂ߂荞��

					}
					else if (pPosOld->x - fWidth >= posBlock.x + m_fWidth && pPos->x - fWidth < posBlock.x + m_fWidth &&
						pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
					{//�u���b�N�̉E�ɂ߂荞��

					}
					else
					{//�ǂ��ɂ��������ĂȂ��ꍇ

						//�u���b�N�̏�Ɉړ�
						pPos->y = posBlock.y;

						pMove->y = 0.0f;

						//���n����
						bLand = true;
					}
				}

				if (pPosOld->y - fHeight >= posBlock.y + m_fHeight && pPos->y - fHeight < posBlock.y + m_fHeight &&
					pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
				{//�u���b�N�̉��ɂ߂荞��

					if (pPosOld->x + fWidth <= posBlock.x && pPos->x + fWidth > posBlock.x &&
						pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
					{//�u���b�N�̍��ɂ߂荞��

					}
					else if (pPosOld->x - fWidth >= posBlock.x + m_fWidth && pPos->x - fWidth < posBlock.x + m_fWidth &&
						pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
					{//�u���b�N�̉E�ɂ߂荞��

					}
					else
					{//�ǂ��ɂ��������ĂȂ��ꍇ

						//�u���b�N�̉��Ɉړ�
						pPos->y = posBlock.y + m_fHeight + fHeight;

						pMove->y = 0.0f;

						//���n���ĂȂ�
						bLand = false;
					}
				}

				if (pPosOld->x + fWidth <= posBlock.x && pPos->x + fWidth > posBlock.x &&
					pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
				{//�u���b�N�̍��ɂ߂荞��

					if (pPosOld->y <= posBlock.y && pPos->y > posBlock.y &&
						pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
					{//�u���b�N�̏�ɂ߂荞��

					}
					else if (pPosOld->y - fHeight >= posBlock.y + m_fHeight && pPos->y - fHeight < posBlock.y + m_fHeight &&
						pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
					{//�u���b�N�̉��ɂ߂荞��

					}
					else
					{//�ǂ��ɂ��������ĂȂ��ꍇ

						//�u���b�N�̍��Ɉړ�
						pPos->x = posBlock.x - fWidth;

						pMove->x = 0.0f;

						//���n���ĂȂ�
						bLand = false;
					}
				}

				if (pPosOld->x - fWidth >= posBlock.x + m_fWidth && pPos->x - fWidth < posBlock.x + m_fWidth &&
					pPos->y > posBlock.y && pPos->y - fHeight < posBlock.y + m_fHeight)
				{//�u���b�N�̉E�ɂ߂荞��

					if (pPosOld->y <= posBlock.y && pPos->y > posBlock.y &&
						pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
					{//�u���b�N�̏�ɂ߂荞��

					}
					else if (pPosOld->y - fHeight >= posBlock.y + m_fHeight && pPos->y - fHeight < posBlock.y + m_fHeight &&
						pPos->x + fWidth > posBlock.x && pPos->x - fWidth < posBlock.x + m_fWidth)
					{//�u���b�N�̉��ɂ߂荞��

					}
					else
					{//�ǂ��ɂ��������ĂȂ��ꍇ

						//�u���b�N�̉E�Ɉړ�
						pPos->x = posBlock.x + m_fWidth + fWidth;

						pMove->x = 0.0f;

						//���n���ĂȂ�
						bLand = false;
					}
				}
			}

		}
	}

	return bLand;
}