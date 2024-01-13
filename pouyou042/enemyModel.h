//==============================================================
//
//���f������[enemyModel.h]
//Author:����������
//
//==============================================================
#ifndef _ENEMYMODEL_H_		//���̃}�N����`������Ă��Ȃ�������
#define _ENEMYMODEL_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"objectX.h"

//�}�N����`
#define MAX_ENEMY_MODEL			(128)		//���f���̐�

//�O���錾
class CModelHier;			//���f���̊K�w�\��
class CMotion;				//���[�V����

//�G�N���X�̒�`
class CEnemyModel : public CObject
{
public:

	//�G�̎�ނ̗񋓂̒�`
	typedef enum
	{
		ENEMYTYPE_FROG = 0,			//�J�G��
		ENEMYTYPE_AQUATICA,			//�����b�p�A�N�A�e�C�J

		ENEMYTYPE_JELLY,			//�N���Q
		ENEMYTYPE_NUDI,				//�E�~�E�V

		ENEMYTYPE_WITCH,			//����
		ENEMYTYPE_MAX
	} ENEMYTYPE;

	CEnemyModel();		//�R���X�g���N�^
	CEnemyModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemyModel();		//�f�X�g���N�^

	//static HRESULT Load(const char *pFilename);		//�e�N�X�`���̓ǂݍ���
	//static void Unload(void);		//�e�N�X�`���̔j��
	static CEnemyModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE type, int nLife);		//��������

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot) = 0;
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Hit(void) = 0;
	D3DXVECTOR3 GetSizeMin(void) { return m_min; }
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�̎擾
	void SetRotaition(D3DXVECTOR3 rot) { m_rot = rot; }		//�����̐ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			//�����̎擾

protected:
	static CEnemyModel *m_apEnemyModel[MAX_ENEMY_MODEL];			//�G�̃��f��
	CMotion *m_pMotion;		//���[�V�������
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�O��̈ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_max;		//�ő�l
	D3DXVECTOR3 m_min;		//�ŏ��l
	int m_nLife;			//����
	int m_nCntDamage;		//�_���[�W�J�E���^�[
	int m_nCntAttack;		//�U���J�E���^�[
	STATE m_state;			//�G�̏��

protected:

	bool m_bAction;			//�U��������
	bool m_bJump;			//�W�����v������
	bool m_bLand;			//���n������

private:
	static LPD3DXMESH m_pMesh;						//���b�V���i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;					//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;						//�}�e���A���̐�
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	int m_nIdxTexture;			//�e�N�X�`���̔ԍ�
	static int m_nNumAll;		//�G�̑���
	int m_nID;					//�G�̔ԍ�

	ENEMYTYPE m_type;		//�G�̎��
};

//�J�G���̓G�N���X�̒�`
class CEnemyFrog : public CEnemyModel
{
public:

	//�G�̃p�[�c
	typedef enum
	{
		PARTS_BODY = 0,		//[0]��
		PARTS_LU,			//[1]���r��
		PARTS_LD,			//[2]���r��
		PARTS_HAND_L,		//[3]����
		PARTS_RU,			//[4]�E�r��
		PARTS_RD,			//[5]�E�r��
		PARTS_HAND_R,		//[6]�E��
		PARTS_LEG_LU,		//[7]��������
		PARTS_LEG_LD,		//[8]���ӂ���͂�
		PARTS_ANKLE_L,		//[9]������
		PARTS_SHOE_L,		//[10]���C
		PARTS_LEG_RU,		//[11]�E������
		PARTS_LEG_RD,		//[12]�E�ӂ���͂�
		PARTS_ANKLE_R,		//[13]�E����
		PARTS_SHOE_R,		//[14]�E�C
		PARTS_MAX
	} PARTS;

	CEnemyFrog();		//�R���X�g���N�^
	CEnemyFrog(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemyFrog();		//�f�X�g���N�^

	void LoadFile(void);	//���f���t�@�C���ǂݍ���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

private:

	static char *m_apFileName[PARTS_MAX];		//�t�@�C����
	CModelHier *m_apModel[PARTS_MAX];		//���f��(�p�[�c)�ւ̃|�C���^


};

//�����b�p�A�N�A�e�B�J�̓G�N���X�̒�`
class CEnemyAquatica : public CEnemyModel
{
public:

	//�G�̃p�[�c
	typedef enum
	{
		PARTS_BODY = 0,		//[0]��
		//PARTS_HEAD,			//[1]��
		//PARTS_HAIR,			//[2]������
		//PARTS_ARMUP_L,		//[3]���r��
		//PARTS_ARMDOWN_L,	//[4]���r��
		//PARTS_HAND_L,		//[5]����
		//PARTS_ARMUP_R,		//[6]�E�r��
		//PARTS_ARMDOWN_R,	//[7]�E�r��
		//PARTS_HAND_R,		//[8]�E��
		//PARTS_WAIST,		//[9]��
		//PARTS_SKIRT,		//[10]�X�J�[�g
		//PARTS_LEG_L,		//[11]��������
		//PARTS_CALF_L,		//[12]���ӂ���͂�
		//PARTS_FOOT_L,		//[13]���C
		//PARTS_LEG_R,		//[14]�E������
		//PARTS_CALF_R,		//[15]�E�ӂ���͂�
		//PARTS_FOOT_R,		//[16]�E�C
		//PARTS_WEAPON,		//[17]����(�b�e�b�|�E�E�I)
		PARTS_MAX
	} PARTS;

	CEnemyAquatica();		//�R���X�g���N�^
	CEnemyAquatica(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemyAquatica();		//�f�X�g���N�^

	void LoadFile(void);	//���f���t�@�C���ǂݍ���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

private:

	static char *m_apFileName[PARTS_MAX];		//�t�@�C����
	CModelHier *m_apModel[PARTS_MAX];		//���f��(�p�[�c)�ւ̃|�C���^

};

//�����̓G�N���X�̒�`
class CEnemWitch : public CEnemyModel
{
public:

	//�G�̃p�[�c
	typedef enum
	{
		PARTS_BODY = 0,		//[0]��
		PARTS_HEAD,			//[1]��
		PARTS_ARMUP_L,		//[2]���r��
		PARTS_ARMDOWN_L,	//[3]���r��
		PARTS_HAND_L,		//[4]����
		PARTS_ARMUP_R,		//[5]�E�r��
		PARTS_ARMDOWN_R,	//[6]�E�r��
		PARTS_HAND_R,		//[7]�E��
		PARTS_WAIST,		//[8]��
		PARTS_SKIRT,		//[9]�X�J�[�g
		PARTS_LEG_L,		//[10]��������
		PARTS_CALF_L,		//[11]���ӂ���͂�
		PARTS_FOOT_L,		//[12]���C
		PARTS_LEG_R,		//[13]�E������
		PARTS_CALF_R,		//[14]�E�ӂ���͂�
		PARTS_FOOT_R,		//[15]�E�C
		PARTS_MAX
	} PARTS;

	//�����̌`��
	typedef enum
	{
		FORM_FIRST = 0,		//��1�`��
		FORM_SECOND,		//��Q�`��
		FORM_MAX
	} FORM;

	//�U���̎��
	typedef enum
	{
		ATTACK_GROUND = 0,		//�n��
		ATTACK_FLY,				//��
		ATTACK_3D,				//����
		ATTACK_MAX
	} ATTACK;

	CEnemWitch();		//�R���X�g���N�^
	CEnemWitch(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CEnemWitch();		//�f�X�g���N�^

	void LoadFile(void);	//���f���t�@�C���ǂݍ���

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

	int GetForm(void) { return m_form; }		//�����̌`�Ԏ擾
	static int GetAttack(void) { return m_attack; }

private:

	static char *m_apFileName[PARTS_MAX];		//�t�@�C����
	CModelHier *m_apModel[PARTS_MAX];		//���f��(�p�[�c)�ւ̃|�C���^

	FORM m_form;		//�`��
	static ATTACK m_attack;	//�U���̎��
	int m_nCntSwitch;	//�؂�ւ��J�E���g
	bool m_bBgm;		//BGM��������
	bool m_bItem;		//�A�C�e���o�����Ă����̂�
	int m_nCntEnemy;	//�G�o���܂ł̃J�E���g
	int m_nCntItem;		//�A�C�e���o���J�E���g
	float m_fAngle;		//�p�x
};

#endif
