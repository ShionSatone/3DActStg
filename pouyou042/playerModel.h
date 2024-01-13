//==============================================================
//
//�v���C���[�̃��f������[playerModel.h]
//Author:����������
//
//==============================================================
#ifndef _PLAYERMODEL_H_		//���̃}�N����`������Ă��Ȃ�������
#define _PLAYERMODEL_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

class CModelHier;	//���f���̊K�w�\��
class CMotion;		//���[�V�����̊K�w�\��

//�v���C���[�N���X�̒�`
class CPlayerModel : public CObject
{
public:

	//�v���C���[�̎��
	typedef enum
	{
		PLAYERTYPE_HUMAN = 0,		//�l�Ԃ̎p
		PLAYERTYPE_GOLDFISH,		//�����̎p
		PLAYERTYPE_MAX
	} PLAYERTYPE;

	//�v���C���[�̃p�[�c
	typedef enum
	{
		PARTS_BODY = 0,		//[0]��
		PARTS_HEAD,			//[1]��
		PARTS_HAIR,			//[2]������
		PARTS_ARMUP_L,		//[3]���r��
		PARTS_ARMDOWN_L,	//[4]���r��
		PARTS_HAND_L,		//[5]����
		PARTS_ARMUP_R,		//[6]�E�r��
		PARTS_ARMDOWN_R,	//[7]�E�r��
		PARTS_HAND_R,		//[8]�E��
		PARTS_WAIST,		//[9]��
		PARTS_SKIRT,		//[10]�X�J�[�g
		PARTS_LEG_L,		//[11]��������
		PARTS_CALF_L,		//[12]���ӂ���͂�
		PARTS_FOOT_L,		//[13]���C
		PARTS_LEG_R,		//[14]�E������
		PARTS_CALF_R,		//[15]�E�ӂ���͂�
		PARTS_FOOT_R,		//[16]�E�C
		PARTS_WEAPON,		//[17]����(�e�b�|�E�E�I)

		PARTS_MAX
	} PARTS;

	CPlayerModel();		//�R���X�g���N�^
	CPlayerModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CPlayerModel();		//�f�X�g���N�^

	static CPlayerModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void UpdateHuman(void);
	void UpdataFish(void);

	void Hit(void);

	void ControlHumanKeyboard(void);		//�v���C���[�L�[�{�[�h����(�l��)
	void ControlHumanPad(void);		//�v���C���[�R���g���[���[����(�l��)
	void ControlGoldFish(void);		//�v���C���[����(����)
	void Screen(void);		//��ʊO����
	void LoadFile(void);	//���f���t�@�C���ǂݍ���
	void RotCorrection(void);	//�����̕␳����

	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�擾
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu�ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			//�����擾
	PLAYERTYPE GetType(void) { return m_Type; }				//��ގ擾
	void SetWeaponType(int type) { m_particleType = type; }		//����̎�ސݒ�
	int GetWeaponType(void) { return m_particleType; }		//����̎�ގ擾
	D3DXVECTOR3 GetSizeMin(void) { return m_min; }
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }
	void SetState(STATE state) { m_state = state; }			//��Ԑݒ�

private:
	static char *m_apFileName[PARTS_MAX];		//�t�@�C����

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�O��̈ʒu
	D3DXVECTOR3 m_posSave;		//�����p�̈ʒu
	D3DXVECTOR3 m_posKeepHuman;	//�l�Ԃ̈ʒu�ۑ��p
	D3DXVECTOR3 m_posKeepFish;	//�����̈ʒu�ۑ��p
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_max;		//�l�Ԃ̍ő�l
	D3DXVECTOR3 m_min;		//�l�Ԃ̍ŏ��l
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	CModelHier *m_apModel[PARTS_MAX];		//���f��(�p�[�c)�ւ̃|�C���^
	int m_nNumModel;		//���f��(�p�[�c)�̑���
	int m_nCntDamage;		//�_���[�W�J�E���^�[
	bool m_bJump;			//�W�����v�������̔���
	bool m_bMove;			//�����Ă邩�̔���
	bool m_bLand;			//���n������
	bool m_bAction;			//�U�����Ă邩

	float m_fRotDest;		//�ڕW
	float m_fRotDiff;		//����
	float m_fMoveBulet;		//�e�̈ړ���

	STATE m_state;			//�v���C���[�̏��
	PLAYERTYPE m_Type;		//�v���C���[�̎��
	int m_particleType;		//�p�[�e�B�N���̎��
	int m_nType;			//���Ԗڂ̃p�[�e�B�N����
	int m_nParticleLife;	//�p�[�e�B�N���̎���
	int m_nCntHit;			//�q�b�g�ł���܂ł̃J�E���^�[
	int m_nCntMove;			//�����̃J�E���^�[
	int m_nCntSand;			//���̃p�[�e�B�N���J�E���^�[

	bool m_bPad;			//�p�b�h�̃X�e�B�b�N��|���Ă邩

	CMotion *m_pMotion;		//���[�V�������
};

#endif
