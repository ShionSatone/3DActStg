//==============================================================
//
//�e�̏���[bullet.cpp]
//Author:����������
//
//==============================================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "enemyModel.h"
#include "effect.h"
#include "particle.h"
#include "sound.h"
#include "score.h"
#include "texture.h"
#include "objectX.h"
#include "debugproc.h"
#include "bulletRemain.h"
#include "game.h"
#include "camera.h"

//�}�N����`
#define WIDTH_BULLET	(50.0f * 0.5f)		//�e�̉���
#define HEIGHT_BULLET	(50.0f * 0.5f)		//�e�̏c��
#define NUM_PATTERN		(10)				//�p�^�[����
#define MOVE_SPEED		(3.0f)				//�e�̈ړ����x
#define ANGLE_UP		(0.75f)				//��̊p�x
#define ANGLE_DOWN		(0.25f)				//���̊p�x
#define ANGLE_WIDTH		(0.5f)				//���̊p�x
#define DEST_WATER		(50)				//�������ł���܂ł̎���
#define DEST_ICE		(40)				//�X�����ł���܂ł̎���
#define DEST_VAPOR		(40)				//���C�����ł���܂ł̎���
#define DEST_ENEMY		(70)				//�G�̒e�����ł���܂ł̎���
#define RADIUS_WATER	(25.0f)				//���̔��a
#define RADIUS_ICE		(10.0f)				//�X�̔��a
#define RADIUS_VAPOR	(30.0f)				//���C�̔��a
#define RADIUS_ENEMY	(25.0f)				//�G�̒e�̔��a

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;		//�e�N�X�`��

//==============================================================
//�R���X�g���N�^
//==============================================================
CBullet::CBullet()
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu(�O��)
	m_move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);	//�ړ���
	m_nLife = DEST_WATER;		//�e���ł̎���
	m_particleType = PARTICLETYPE_NONE;		//�p�[�e�B�N���̎��
	m_fRadius = WIDTH_BULLET;		//�e�̔��a
	m_nParticleLife = 8;		//�p�[�e�B�N���̎���
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CBullet::CBullet(int particleType)
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu(�O��)
	m_particleType = particleType;		//�p�[�e�B�N���̎��

	//�e���ł̎���
	switch (m_particleType)
	{
	case PARTICLETYPE_NONE:		//�����Ȃ�

		break;

	case PARTICLETYPE_WATER:		//��

		m_nLife = DEST_WATER;
		m_fRadius = RADIUS_WATER;
		m_nParticleLife = 8;

		break;

	case PARTICLETYPE_ICE:			//�X

		m_nLife = DEST_ICE;
		m_fRadius = RADIUS_ICE;
		m_nParticleLife = 14;

		break;

	case PARTICLETYPE_VAPOR:		//���C

		m_nLife = DEST_VAPOR;
		m_fRadius = RADIUS_VAPOR;
		m_nParticleLife = 8;

		break;

	case PARTICLETYPE_ENEMY:		//�G�̒e

		m_nLife = DEST_ENEMY;
		m_fRadius = RADIUS_ENEMY;
		m_nParticleLife = 8;

		break;

	case PARTICLETYPE_WITCH:		//�����̒e

		m_nLife = DEST_ENEMY;
		m_fRadius = RADIUS_ENEMY;
		m_nParticleLife = 10;

		break;
	}
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CBullet::~CBullet()
{

}

//==============================================================
//�e�̐�������
//==============================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, int particleType)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{//���������g�p����ĂȂ�������

		//�e�̐���
		pBullet = new CBullet(particleType);
	}

	//����������
	pBullet->Init(pos, move, type);

	return pBullet;
}

//==============================================================
//�e�̏���������
//==============================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type)
{
	CTexture *pTexture = CManager::GetTexture();
	CBulletRemain *pBulletRemain = CGame::GetBulletRemain();

	m_type = type;		//���

	//�e�N�X�`���̓ǂݍ���
	switch (m_particleType)
	{
	case PARTICLETYPE_NONE:			//�����Ȃ�

		m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\bullet000.png");

		break;

	case PARTICLETYPE_WATER:		//��

		m_nIdxTexture = pTexture->TEX_WATER;

		break;

	case PARTICLETYPE_ICE:			//�X

		m_nIdxTexture = pTexture->TEX_ICE;

		break;

	case PARTICLETYPE_VAPOR:		//���C

		m_nIdxTexture = pTexture->TEX_VAPOR;

		break;

	case PARTICLETYPE_ENEMY:		//�G�̒e

		m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\bullet002.png");

		break;

	case PARTICLETYPE_WITCH:		//�����̒e

		m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\bullet003.png");

		break;
	}

	//�e�N�X�`���̊��蓖��
	CBillboard::BindTexture(m_nIdxTexture);

	//�r���{�[�h�̏���������
	CBillboard::Init(pos, move);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_BULLET);

	//�e�̑傫���ݒ�
	CBillboard::SetSize(WIDTH_BULLET, HEIGHT_BULLET);

	//�e�̈ړ��ʑ��
	CBillboard::SetMove(move);

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (m_particleType != PARTICLETYPE_ENEMY && m_particleType != PARTICLETYPE_NONE && m_particleType != PARTICLETYPE_WITCH)
		{
			//�e�̏�����Z
			pBulletRemain->SetNumBullet(10);
		}
	}

	return S_OK;
}

//==============================================================
//�e�̏I������
//==============================================================
void CBullet::Uninit(void)
{
	//�r���{�[�h�̏I������
	CBillboard::Uninit();
}

//==============================================================
//�e�̍X�V����
//==============================================================
void CBullet::Update(void)
{
	//���ł܂ł̎��Ԍ��Z
	m_nLife--;

	//�ʒu�擾
	m_pos = CBillboard::GetPosition();
	m_move = CBillboard::GetMove();

	m_posOld = m_pos;		//���݂̈ʒu		

	//�ʒu�X�V
	m_pos += m_move;

	//�ʒu�ݒ�
	CBillboard::SetPosition(CObject::TYPE_BULLET, m_pos);

	//�r���{�[�h�̍X�V����
	CBillboard::Update();

	//�e�폜
	if (m_nLife <= 0)
	{//��ʊO�ɏo���� || �e�����ł��鎞�ԂɂȂ�����

		if (m_nLife <= 0 && m_type != TYPE_ENEMY)
		{
			//�����̐���
			CParticle::Create(m_pos, D3DXCOLOR(0.0f, 0.7f, 0.5f, 1.0f), PARTICLETYPE_EXPLOSION, 0, 13);
		}

		//�e�̏I������
		CBullet::Uninit();
	}
	else
	{//�܂��e�����ł��ĂȂ�������

		//�G�Ƃ̓����蔻��
		if (CBullet::CollisionModel(&m_pos, &m_posOld) == true)
		{//�G�Ɠ���������

			//�e�̏I������
			CBullet::Uninit();
		}
	}

	//�G�t�F�N�g�̐���
	CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fRadius, m_nParticleLife, m_particleType);
}

//==============================================================
//�e�̕`�揈��
//==============================================================
void CBullet::Draw(void)
{
	//�r���{�[�h�̕`�揈��
	CBillboard::Draw();
}

//==============================================================
//�����蔻��
//==============================================================
bool CBullet::Colision(D3DXVECTOR3 pos)
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

			if (type == pObj->TYPE_ENEMY)
			{//��ނ��G�̏ꍇ

				//�G�̈ʒu�擾
				D3DXVECTOR3 posEnemy = pObj->GetPosition();

				if (pos.x >= posEnemy.x - WIDTH_ENEMY && pos.x <= posEnemy.x + WIDTH_ENEMY &&
					pos.y >= posEnemy.y - HEIGHT_ENEMY && pos.y <= posEnemy.y + HEIGHT_ENEMY)
				{//�G�ƒe����������

					//SE�Đ�
					CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE000);

					//�����̐���
					CExplosion::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//�p�[�e�B�N���̐���
					CParticle::Create(pos, D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f), m_particleType, 100, 20.0f);

					//�X�R�A���Z
					CScore::Add(50000);

					//�G�̏I������
					pObj->Uninit();

					//�e�̏I������
					CBillboard::Uninit();

					return true;
				}
			}
			else if (type == pObj->TYPE_BLOCK)
			{//��ނ��u���b�N�̂Ƃ�

				//�G�̈ʒu�擾
				D3DXVECTOR3 posBlock = pObj->GetPosition();

				//�u���b�N�̓����蔻��(����)
				if (CBullet::ColisionBlockLeft(pos, posBlock) == true)
				{//�������Ă���

					//SE�Đ�
					CSound::Play(CSound::SOUND_LABEL_SE_DAMAGE000);

					//�����̐���
					CExplosion::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//�e�̏I������
					CBillboard::Uninit();

					return true;
				}
			}

		}
	}

	return false;
}

//==============================================================
//�u���b�N�̓����蔻��(���S�F[����])
//==============================================================
bool CBullet::ColisionBlockLeft(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock)
{
	if (pos.x + WIDTH_BULLET >= posBlock.x && pos.x - WIDTH_BULLET <= posBlock.x + 100.0f &&
		pos.y >= posBlock.y && pos.y - HEIGHT_BULLET <= posBlock.y + 100.0f)
	{//����������

		return true;
	}

	return false;
}

//==============================================================
//�u���b�N�̓����蔻��(���S�F[����])
//==============================================================
bool CBullet::ColisionBlockCenter(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock)
{
	if (pos.x >= posBlock.x - 100.0f && pos.x <= posBlock.x + 100.0f &&
		pos.y >= posBlock.y - 100.0f && pos.y <= posBlock.y + 100.0f)
	{//����������

		return true;
	}

	return false;
}

//==============================================================
//���f���̓����蔻��
//==============================================================
bool CBullet::CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CCamera *pCamera = CManager::GetCamera();
	CSound *pSound = CManager::GetSound();

	for (int nCntModel = 0; nCntModel < MAX_OBJECT; nCntModel++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = GetObject(nCntModel);

		if (pObj != NULL)
		{//���������g�p����Ă���Ƃ�

			//��ނ��擾
			CObject::TYPE type = pObj->GetType();

			//�v���C���[�̒e
			if (m_type == TYPE_PLAYER)
			{
				if (type == pObj->TYPE_MODEL || type == TYPE_ENEMY || type == TYPE_SWITCH)
				{//��ނ����f���̏ꍇ

					//���f���̈ʒu�擾
					D3DXVECTOR3 posModel = pObj->GetPosition();
					D3DXVECTOR3 rotModel = pObj->GetRotation();
					D3DXVECTOR3 minModel = pObj->GetSizeMin();
					D3DXVECTOR3 maxModel = pObj->GetSizeMax();

					if (pPos->x + WIDTH_BULLET >= posModel.x + minModel.x &&
						pPos->x - WIDTH_BULLET <= posModel.x + maxModel.x &&
						pPos->y + HEIGHT_BULLET >= posModel.y + minModel.y &&
						pPos->y - HEIGHT_BULLET <= posModel.y + maxModel.y &&
						pPos->z > posModel.z + minModel.z &&
						pPos->z < posModel.z + maxModel.z)
					{
						if (type == TYPE_ENEMY)
						{//�G�̏ꍇ

							//�G�̃q�b�g����
							pObj->Hit();
						}
						else if (type == TYPE_SWITCH)
						{//�X�C�b�`�̏ꍇ

							pCamera->SetMode();

							//BGM�Đ�
							pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);
						}

						//�����̐���
						CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

						return true;
					}
				}
			}
			else if (m_type == TYPE_ENEMY)
			{
				if (type == pObj->TYPE_MODEL || type == pObj->TYPE_PLAYER || type == pObj->TYPE_SWITCH)
				{//��ނ����f���̏ꍇ

					//���f���̈ʒu�擾
					D3DXVECTOR3 posModel = pObj->GetPosition();
					D3DXVECTOR3 rotModel = pObj->GetRotation();
					D3DXVECTOR3 minModel = pObj->GetSizeMin();
					D3DXVECTOR3 maxModel = pObj->GetSizeMax();

					if (pPos->x + WIDTH_BULLET >= posModel.x + minModel.x &&
						pPos->x - WIDTH_BULLET <= posModel.x + maxModel.x &&
						pPos->y + HEIGHT_BULLET >= posModel.y + minModel.y &&
						pPos->y - HEIGHT_BULLET <= posModel.y + maxModel.y &&
						pPos->z > posModel.z + minModel.z &&
						pPos->z < posModel.z + maxModel.z)
					{
						if (type == TYPE_PLAYER)
						{//�G�̏ꍇ

							//�G�̃q�b�g����
							pObj->Hit();
						}
						else if (type == TYPE_SWITCH)
						{//�X�C�b�`�̏ꍇ

							//BGM�Đ�
							pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

							pCamera->SetMode();
						}

						//�����̐���
						CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

						return true;
					}

					//if (pPos->y + HEIGHT_BULLET > posModel.y + minModel.y
					//	&& pPos->y - HEIGHT_BULLET < posModel.y + maxModel.y)
					//{
					//	if (pPosOld->x <= posModel.x + minModel.x
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->z < posModel.z + maxModel.z)
					//	{//���ɂ߂荞�񂾏ꍇ

					//		if (type == TYPE_PLAYER)
					//		{//�G�̏ꍇ

					//			//�G�̃q�b�g����
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//�X�C�b�`�̏ꍇ

					//			//BGM�Đ�
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		//�����̐���
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		return true;

					//	}

					//	if (pPosOld->x >= posModel.x + maxModel.x
					//		&& pPos->x < posModel.x + maxModel.x
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->z < posModel.z + maxModel.z)
					//	{//�E�ɂ߂荞�񂾏ꍇ

					//		//�����̐���
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//�v���C���[�̏ꍇ

					//			//�v���C���[�̃q�b�g����
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//�X�C�b�`�̏ꍇ

					//			//BGM�Đ�
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}

					//	if (pPosOld->z <= posModel.z + minModel.z
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->x < posModel.x + maxModel.x)
					//	{//��O�ɂ߂荞�񂾏ꍇ

					//		//�����̐���
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//�v���C���[�̏ꍇ

					//			//�v���C���[�̃q�b�g����
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//�X�C�b�`�̏ꍇ

					//			//BGM�Đ�
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}

					//	if (pPosOld->z >= posModel.z + maxModel.z
					//		&& pPos->z < posModel.z + maxModel.z
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->x < posModel.x + maxModel.x)
					//	{//���ɂ߂荞�񂾏ꍇ

					//		//�����̐���
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//�v���C���[�̏ꍇ

					//			//�v���C���[�̃q�b�g����
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//�X�C�b�`�̏ꍇ

					//			//BGM�Đ�
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}

					//	if (pPosOld->y <= posModel.y + minModel.y
					//		&& pPos->y > posModel.y + minModel.y
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->x < posModel.x + maxModel.x
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->z < posModel.z + maxModel.z)
					//	{//��ɂ߂荞�񂾏ꍇ

					//		//�����̐���
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//�v���C���[�̏ꍇ

					//			//�v���C���[�̃q�b�g����
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//�X�C�b�`�̏ꍇ

					//			//BGM�Đ�
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);
					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}

					//	if (pPosOld->y >= posModel.y + maxModel.y
					//		&& pPos->y < posModel.y + maxModel.y
					//		&& pPos->x > posModel.x + minModel.x
					//		&& pPos->x < posModel.x + maxModel.x
					//		&& pPos->z > posModel.z + minModel.z
					//		&& pPos->z < posModel.z + maxModel.z)
					//	{//��ɂ߂荞�񂾏ꍇ

					//		//�����̐���
					//		CExplosion::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

					//		if (type == TYPE_PLAYER)
					//		{//�v���C���[�̏ꍇ

					//			//�v���C���[�̃q�b�g����
					//			pObj->Hit();
					//		}
					//		else if (type == TYPE_SWITCH)
					//		{//�X�C�b�`�̏ꍇ

					//			//BGM�Đ�
					//			pSound->Play(pSound->SOUND_LABEL_SE_SWITCH);

					//			pCamera->SetMode();
					//		}

					//		return true;
					//	}
					//}
				}
			}
		}
	}

	return false;
}