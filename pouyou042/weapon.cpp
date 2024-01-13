//==============================================================
//
//����̎�ޕ\������[weapon.cpp]
//Author:����������
//
//==============================================================
#include "weapon.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "object.h"
#include "texture.h"
#include "playerModel.h"
#include "game.h"

//�}�N����`
#define WIDTH_WEAPON		(100.0f * 0.5f)		//����
#define HEIGHT_WEAPON		(100.0f * 0.5f)		//�c��

//�ÓI�����o�ϐ��錾
CObject2D *CWeapon::m_apObject2D[NUM_WEAPON] = {};
LPDIRECT3DTEXTURE9 CWeapon::m_pTexture[NUM_WEAPON] = {};		//�e�N�X�`��

//==============================================================
//�R���X�g���N�^
//==============================================================
CWeapon::CWeapon()
{
	//�ϐ�������
	//m_pos = D3DXVECTOR3(WIDTH_WEAPON, HEIGHT_WEAPON, 0.0f);		//�ʒu

	for (int nCntBg = 0; nCntBg < NUM_WEAPON; nCntBg++)
	{
		m_nIdxTexture[nCntBg] = -1;		//�e�N�X�`���̔ԍ�
	}
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CWeapon::~CWeapon()
{

}

//==============================================================
//����̎�ޕ\���̃e�N�X�`���̓ǂݍ���
//==============================================================
//HRESULT CWeapon::Load(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
//
//	if (m_pTexture[0] == NULL || m_pTexture[1] == NULL || m_pTexture[2] == NULL)
//	{//�e�N�X�`���ݒ肳��ĂȂ��Ƃ�
//
//		//�e�N�X�`���̓ǂݍ���
//		D3DXCreateTextureFromFile(pDevice,
//			"data\\TEXTURE\\bg100.png",
//			&m_pTexture[0]);
//
//		D3DXCreateTextureFromFile(pDevice,
//			"data\\TEXTURE\\bg101.png",
//			&m_pTexture[1]);
//
//		D3DXCreateTextureFromFile(pDevice,
//			"data\\TEXTURE\\bg102.png",
//			&m_pTexture[2]);
//	}
//
//	return S_OK;
//}

//==============================================================
//����̎�ޕ\���̃e�N�X�`���̔j��
//==============================================================
//void CWeapon::Unload(void)
//{
//	//�e�N�X�`���̔j��
//	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
//	{
//		if (m_pTexture[nCntBg] != NULL)
//		{
//			m_pTexture[nCntBg]->Release();
//			m_pTexture[nCntBg] = NULL;
//		}
//	}
//}

//==============================================================
//��������
//==============================================================
CWeapon *CWeapon::Create(D3DXVECTOR3 pos)
{
	CWeapon *pWeapon = NULL;

	if (pWeapon == NULL)
	{//���������g�p����ĂȂ�������

		//����̎�ޕ\���̐���
		pWeapon = new CWeapon;

		//����������
		pWeapon->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//��ސݒ�
		pWeapon->SetType(TYPE_NONE);
	}

	return pWeapon;
}

//==============================================================
//����̎�ޕ\���̏���������
//==============================================================
HRESULT CWeapon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture[0] = pTexture->Regit("data\\TEXTURE\\weapon00.png");
	m_nIdxTexture[1] = pTexture->Regit("data\\TEXTURE\\weapon01.png");
	m_nIdxTexture[2] = pTexture->Regit("data\\TEXTURE\\weapon02.png");

	//���������u
	for (int nCntBg = 0; nCntBg < NUM_WEAPON; nCntBg++)
	{
		if (m_apObject2D[nCntBg] == NULL)
		{//�g�p����ĂȂ��Ƃ�

			//2D�I�u�W�F�N�g����
			m_apObject2D[nCntBg] = CObject2D::Create();

			if (m_apObject2D[nCntBg] != NULL)
			{//�����o������

				//�傫���ݒ�
				m_apObject2D[nCntBg]->SetSize(WIDTH_WEAPON, HEIGHT_WEAPON);

				//�ʒu�ݒ�
				m_apObject2D[nCntBg]->SetPosition(CObject::TYPE_ITEM, pos, WIDTH_WEAPON, HEIGHT_WEAPON);

				if ((pPlayer->GetWeaponType() - 1) != nCntBg)
				{//���݂̕���̎�ނƉ摜�̔ԍ����Ⴄ

					//�F�����ɂ���
					m_apObject2D[nCntBg]->SetColor(CObject::TYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}

				//�e�N�X�`�����蓖��
				m_apObject2D[nCntBg]->BindTexture(m_nIdxTexture[nCntBg]);
			}
		}
	}

	//��ސݒ�
	CObject::SetType(CObject::TYPE_ITEM);

	return S_OK;
}

//==============================================================
//����̎�ޕ\���̏I������
//==============================================================
void CWeapon::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < NUM_WEAPON; nCntBg++)
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
//����̎�ޕ\���̍X�V����
//==============================================================
void CWeapon::Update(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();

	for (int nCntBg = 0; nCntBg < NUM_WEAPON; nCntBg++)
	{
		if (m_apObject2D[nCntBg] != NULL)
		{
			if ((pPlayer->GetWeaponType() - 1) != nCntBg)
			{//���݂̕���̎�ނƉ摜�̔ԍ����Ⴄ

				//�F�����ɂ���
				m_apObject2D[nCntBg]->SetColor(CObject::TYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
			else if((pPlayer->GetWeaponType() - 1) == nCntBg)
			{
				//�F�������ɂ���
				m_apObject2D[nCntBg]->SetColor(CObject::TYPE_ITEM, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
}

//==============================================================
//����̎�ޕ\���̕`�揈��
//==============================================================
void CWeapon::Draw(void)
{
	
}

//==============================================================
//�e�N�X�`�����蓖�ď���
//==============================================================
void CWeapon::BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount)
{
	m_pTexture[nCount] = pTexture;		//�e�N�X�`�����蓖��
}