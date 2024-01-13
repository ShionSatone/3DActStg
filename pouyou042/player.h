//==============================================================
//
//�v���C���[����[player.h]
//Author:����������
//
//==============================================================
#ifndef _PLAYER_H_		//���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object2D.h"

//�}�N����`
#define WIDTH_PLAYER	(100.0f * 0.5f)		//�v���C���[�̉���
#define HEIGHT_PLAYER	(150.0f)			//�v���C���[�̏c��

//�v���C���[�N���X
class CPlayer : public CObject2D
{
public:
	CPlayer();	//�R���X�g���N�^
	CPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�R���X�g���N�^�i�I�[�o�[���[�h�j
	~CPlayer();	//�f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void Control(void);		//���͏���
	void Screen(void);		//��ʊO����

	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//�ʒu�̎擾

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�ʒu�i�O��j
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_move;		//�ړ���

	int m_nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;		//�p�^�[��No.�J�E���^�[
	int m_nRandSpeed;		//�ʒu�̃����_���ȑ���	
	float m_fRandCol;		//�����_���ȐF
	float m_fRandRot;		//�����_���Ȍ���
	bool m_bJump;			//�W�����v�������̔���
};

#endif