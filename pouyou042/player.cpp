//==============================================================
//
//�v���C���[����[player.cpp]
//Author:����������
//
//==============================================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "effect.h"
#include "sound.h"
#include "block.h"
#include "debugproc.h"
#include "texture.h"

//�}�N����`
#define NUM_PATTERN		(10)				//�p�^�[����
#define MOVE_SPEED		(1.0f)				//�v���C���[�̈ړ����x
#define ANGLE_UP		(0.75f)				//��̊p�x
#define ANGLE_DOWN		(0.25f)				//���̊p�x
#define ANGLE_WIDTH		(0.5f)				//���̊p�x
#define MOVE_Y			(0.5f)				//�ړ���Y
#define JUMP_HEIGHT		(-14.0f)			//�W�����v�̍���

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//==============================================================
//�R���X�g���N�^
//==============================================================
CPlayer::CPlayer()
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_nCounterAnim = 0;		//�A�j���[�V�����J�E���^�[
	m_nPatternAnim = 0;		//�p�^�[��No.�J�E���^�[
	m_nRandSpeed = rand() % 4 + 1;
	m_fRandCol = (float)(rand() % 10) * 0.1f;
	m_fRandRot = (float)(rand() % 10) * 0.01f;
	m_bJump = false;		//�W�����v������
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CPlayer::CPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�
	m_pos = pos;			//�ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = rot;			//����
	m_nCounterAnim = 0;		//�A�j���[�V�����J�E���^�[
	m_nPatternAnim = 0;		//�p�^�[��No.�J�E���^�[
	m_nRandSpeed = rand() % 4 + 1;		//�ʒu�𓮂�������
	m_fRandCol = (float)(rand() % 10) * 0.1f;	//�F
	m_fRandRot = (float)(rand() % 10) * 0.01f;	//����
	m_bJump = false;		//�W�����v������
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CPlayer::~CPlayer()
{

}

//==============================================================
//�v���C���[�̐�������
//==============================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{//���������g�p����ĂȂ�������

		//�v���C���[�̐���
		pPlayer = new CPlayer(pos, rot);
	}

	//����������
	pPlayer->Init(pos, rot);

	return pPlayer;
}

//==============================================================
//�v���C���[�̏���������
//==============================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\player000.png");

	//�e�N�X�`���̊��蓖��
	CObject2D::BindTexture(m_nIdxTexture);

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init(pos, rot);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_PLAYER);

	//�v���C���[�̑傫���ݒ�
	CObject2D::SetSize(WIDTH_PLAYER, HEIGHT_PLAYER);

	return S_OK;
}

//==============================================================
//�v���C���[�̏I������
//==============================================================
void CPlayer::Uninit(void)
{
	//�T�E���h��~
	CSound::Stop();

	//2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//==============================================================
//�v���C���[�̍X�V����
//==============================================================
void CPlayer::Update(void)
{
	m_nCounterAnim++;

	//�ʒu�擾
	m_pos = CObject2D::GetPosition();

	//�O��̈ʒu���
	m_posOld = m_pos;

	//�ړ�����
	CPlayer::Control();

	//�ړ��ʉ��Z
	m_move.y += MOVE_Y;

	//�ʒu�X�V
	m_pos += m_move;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//�u���b�N�Ƃ̓����蔻�菈��
	if (CBlock::Collision(&m_pos, &m_posOld, &m_move, WIDTH_PLAYER, HEIGHT_PLAYER) == true)
	{//���n������

		m_bJump = false;	//���n��Ԃɂ���
	}
	else
	{
		m_bJump = true;		//�W�����v��Ԃɂ���
	}

	//��ʊO����
	CPlayer::Screen();

	//�ʒu�ݒ�
	CObject2D::SetPosition(CObject::TYPE_PLAYER, m_pos, WIDTH_PLAYER, HEIGHT_PLAYER);

	////�G�t�F�N�g�̐���
	//CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), 
	//	D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 40.0f * 0.5f, 8, CObject::TYPE_PLAYER);
}

//==============================================================
//�v���C���[�̓��͏���
//==============================================================
void CPlayer::Control(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//�Q�[���p�b�h�̏��擾

	//�ړ�
	if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoyPad->GetPress(pInputJoyPad->BUTTON_X, 0) || pInputJoyPad->GetPressRX(0).x < -0.0f)
	{//A�L�[�������ꂽ��

		m_move.x += sinf(-D3DX_PI * ANGLE_WIDTH) * MOVE_SPEED;
		m_move.y += cosf(-D3DX_PI * ANGLE_WIDTH) * MOVE_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoyPad->GetPress(pInputJoyPad->BUTTON_B, 0) || pInputJoyPad->GetPressRX(0).x > 0.0f)
	{//D�L�[�������ꂽ��

		m_move.x += sinf(D3DX_PI * ANGLE_WIDTH) * MOVE_SPEED;
		m_move.y += cosf(D3DX_PI * ANGLE_WIDTH) * MOVE_SPEED;
	}

	//�W�����v
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
	{//SPACE�L�[�������Ă��� && �W�����v���ĂȂ�������

		//�W�����v����
		m_move.y = JUMP_HEIGHT;

		//�W�����v������Ԃɂ���
		m_bJump = true;
	}

	//�e����
	if (pInputKeyboard->GetTrigger(DIK_UP) == true)
	{//���L�[����������

		//SE�Đ�
		CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

		//�e�̐���
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), D3DXVECTOR3(0.0f, 10.0f, 0.0f), CObject::TYPE_PLAYER, CBullet::BULLETTYPE_WATER);
	}
	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{//���L�[����������

		//SE�Đ�
		CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

		//�e�̐���
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CObject::TYPE_PLAYER, CBullet::BULLETTYPE_WATER);
	}
	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{//���L�[����������

		//SE�Đ�
		CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

		//�e�̐���
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), CObject::TYPE_PLAYER, CBullet::BULLETTYPE_WATER);
	}
	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{//���L�[����������

		//SE�Đ�
		CSound::Play(CSound::SOUND_LABEL_SE_SHOT000);

		//�e�̐���
		//CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - HEIGHT_PLAYER * 0.5f, m_pos.z), D3DXVECTOR3(10.0f, 0.0f, 0.0f), CObject::TYPE_PLAYER, CBullet::BULLETTYPE_WATER);
	}

}

//==============================================================
//��ʊO���菈��
//==============================================================
void CPlayer::Screen(void)
{
	//��ʊO����(��)
	if (m_pos.x < WIDTH_PLAYER)
	{//��ʍ��ɏo����

		m_pos.x = WIDTH_PLAYER;

	}
	else if (m_pos.x > SCREEN_WIDTH - WIDTH_PLAYER)
	{//��ʉE�ɏo����

		m_pos.x = SCREEN_WIDTH - WIDTH_PLAYER;

	}

	//��ʊO����(�c)
	if (m_pos.y < HEIGHT_PLAYER)
	{//��ʏ�ɏo����

		m_pos.y = HEIGHT_PLAYER;
	}
	else if (m_pos.y > SCREEN_HEIGHT)
	{//��ʉ��ɏo����

		m_pos.y = SCREEN_HEIGHT;
		m_move.y = 0.0f;

		m_bJump = false;
	}
}

//==============================================================
//�v���C���[�̕`�揈��
//==============================================================
void CPlayer::Draw(void)
{
	//2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}