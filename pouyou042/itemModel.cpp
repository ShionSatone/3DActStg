//==============================================================
//
//�A�C�e������[itemModel.cpp]
//Author:����������
//
//==============================================================
#include "itemModel.h"
#include "game.h"
#include "model.h"
#include "playerModel.h"
#include "material.h"
#include "life.h"
#include "bulletRemain.h"
#include "sound.h"
#include "score.h"

//�ÓI�����o�ϐ��錾
LPD3DXMESH CItemModel::m_pMesh = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER CItemModel::m_pBuffMat = NULL;					//�}�e���A���ւ̃|�C���^
DWORD CItemModel::m_dwNumMat = NULL;
const char *CItemModel::m_pFilename[TYPE_MAX] = 			//�t�@�C���̖��O
{
	NULL,
	"data\\MODEL\\item_water.x",		//��
	"data\\MODEL\\item_ice.x",			//�X
	"data\\MODEL\\item_vepor.x",		//���C
	"data\\MODEL\\recovery.x",			//��
	//NULL
};

//==============================================================
//�R���X�g���N�^
//==============================================================
CItemModel::CItemModel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_type = TYPEITEM_NONE;	//���
	m_nIdx = -1;				//���f���̔ԍ�
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CItemModel::CItemModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����
	m_type = type;		//���
	m_nIdx = -1;		//���f���̔ԍ�
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CItemModel::~CItemModel()
{

}

//==============================================================
//�A�C�e���̐�������
//==============================================================
CItemModel *CItemModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type)
{
	CItemModel *pItemModel = NULL;

	if (pItemModel == NULL)
	{//���������g�p����ĂȂ�������

		//�A�C�e���̐���
		pItemModel = new CItemModel(pos, rot, type);
	}

	//����������
	pItemModel->Init(pos, rot);

	return pItemModel;
}

//==============================================================
//�A�C�e���̏���������
//==============================================================
HRESULT CItemModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CMaterial *pMaterial = CManager::GetMaterial();

	//���f���̓ǂݍ���
	m_nIdx = pMaterial->Regit(m_pFilename[m_type]);

	//�}�e���A���̊��蓖��
	CObjectX::BindMaterial(m_nIdx);

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init(pos, rot);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_ITEM);

	return S_OK;
}

//==============================================================
//�A�C�e���̏I������
//==============================================================
void CItemModel::Uninit(void)
{
	//�I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();
}

//==============================================================
//�A�C�e���̍X�V����
//==============================================================
void CItemModel::Update(void)
{
	//�I�u�W�F�N�gX�̍X�V����
	CObjectX::Update();
}

//==============================================================
//�A�C�e���̕`�揈��
//==============================================================
void CItemModel::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}

//==============================================================
//�A�C�e���̃q�b�g����
//==============================================================
void CItemModel::Hit(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();
	CLife *pLife = CGame::GetLife();
	CBulletRemain *pBR = CGame::GetBulletRemain();
	CSound *pSound = CManager::GetSound();
	CScore *pScore = CGame::GetScore();

	if (m_type != TYPEITEM_LIFE/* && m_type != TYPEITEM_KEY*/)
	{//����̎�ނ̃A�C�e���̎�

		//SE�Đ�
		pSound->Play(pSound->SOUND_LABEL_SE_ITEM000);

		//����̎�ޕύX����
		pPlayer->SetWeaponType(m_type);

		//�e��
		pBR->SetNumBullet(-100);

		//�X�R�A���Z
		pScore->Add(1050);
	}
	else if (m_type == TYPEITEM_LIFE)
	{//�񕜃A�C�e���̎�

		//SE�Đ�
		pSound->Play(pSound->SOUND_LABEL_SE_ITEM100);

		//�̗͑��₷
		pLife->SetNum(60);

		//�X�R�A���Z
		pScore->Add(700);
	}

	//�I������
	CItemModel::Uninit();
}