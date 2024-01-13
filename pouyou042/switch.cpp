//==============================================================
//
//���e�X�C�b�`����[switch.cpp]
//Author:����������
//
//==============================================================
#include "switch.h"
#include "game.h"
#include "model.h"
#include "playerModel.h"
#include "material.h"
#include "sound.h"

//�}�N����`
#define SWITCH_NAME		"data\\MODEL\\map\\switch.x"		//�X�C�b�`�̃t�@�C����

//�ÓI�����o�ϐ��錾
LPD3DXMESH CSwitch::m_pMesh = NULL;				//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER CSwitch::m_pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
DWORD CSwitch::m_dwNumMat = NULL;
const char *CSwitch::m_pFilename = {}; 			//�t�@�C���̖��O

//==============================================================
//�R���X�g���N�^
//==============================================================
CSwitch::CSwitch()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_nIdx = -1;				//���f���̔ԍ�
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CSwitch::CSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����
	m_nIdx = -1;		//���f���̔ԍ�
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CSwitch::~CSwitch()
{

}

//==============================================================
//���e�X�C�b�`�̐�������
//==============================================================
CSwitch *CSwitch::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSwitch *pSwitch = NULL;

	if (pSwitch == NULL)
	{//���������g�p����ĂȂ�������

		//���e�X�C�b�`�̐���
		pSwitch = new CSwitch(pos, rot);
	}

	//����������
	pSwitch->Init(pos, rot);

	return pSwitch;
}

//==============================================================
//���e�X�C�b�`�̏���������
//==============================================================
HRESULT CSwitch::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CMaterial *pMaterial = CManager::GetMaterial();

	//���f���̓ǂݍ���
	m_nIdx = pMaterial->Regit(SWITCH_NAME);

	//�}�e���A���̊��蓖��
	CObjectX::BindMaterial(m_nIdx);

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init(pos, rot);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_SWITCH);

	return S_OK;
}

//==============================================================
//���e�X�C�b�`�̏I������
//==============================================================
void CSwitch::Uninit(void)
{
	//�I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();
}

//==============================================================
//���e�X�C�b�`�̍X�V����
//==============================================================
void CSwitch::Update(void)
{
	//�I�u�W�F�N�gX�̍X�V����
	CObjectX::Update();
}

//==============================================================
//���e�X�C�b�`�̕`�揈��
//==============================================================
void CSwitch::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}

//==============================================================
//���e�X�C�b�`�̃q�b�g����
//==============================================================
void CSwitch::Hit(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	//����̎�ޕύX����
	pPlayer->SetWeaponType(m_type);

	//�I������
	CSwitch::Uninit();
}