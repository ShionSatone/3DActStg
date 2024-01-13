//==============================================================
//
//�Q�[������[game.h]
//Author:����������
//
//==============================================================
#ifndef _GAME_H_		//���̃}�N����`������Ă��Ȃ�������
#define _GAME_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "manager.h"

//�O���錾
class CScore;			//�X�R�A�̏��
class CPlayerModel;		//�v���C���[�̏��
class CEnemyModel;		//�G�̏��
class CModel;			//���f���̏��
class CWall;			//�ǂ̏��
class CField;			//���̏��
class CEdit;			//�G�f�B�b�g�̏��
class CBulletRemain;	//�c�e���̏��
class CLife;			//�����\���̏��
class CPause;			//�|�[�Y��ʂ̏��
class CFade;			//�t�F�[�h

//�Q�[����ʃN���X�̒�`
class CGame : public CScene
{
public:

	//�Q�[�����[�h�̎��
	typedef enum
	{
		GAMEMODE_START = 0,			//�J�n
		GAMEMODE_GROUND,			//�n��
		GAMEMODE_UNDER,				//����
		GAMEMODE_BOSS,				//�{�X��
		GAMEMODE_OVER,				//�I��

	} GAMEMODE;

	CGame();
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEnablePauseMenu(bool bPouse);			//�|�[�Y�؂�ւ�

	static CPlayerModel *GetPlayerModel(void) { return m_pPlayerModel; }				//�v���C���[�̏��
	static CBulletRemain *GetBulletRemain(void) { return m_pBulletRemain; }				//�c�e���̏��
	static CScore *GetScore(void) { return m_pScore; }			//�X�R�A�̏��
	static CLife *GetLife(void) { return m_pLife; }				//�����\���̏��
	static void SetGameMode(GAMEMODE gameMode) { m_gameMode = gameMode; }		//�Q�[�����[�h�̐ݒ�
	static GAMEMODE GetGameMode(void) { return m_gameMode; }					//�Q�[�����[�h�̐ݒ�
	static CPause *GetPause(void) { return m_pPause; }			//�|�[�Y��ʂ̏��
	static bool GetPauseDisp(void) { return m_bPause; }			//�|�[�Y���Ă邩�擾

private:
	static CScore *m_pScore;		//�X�R�A�̏��
	static CPlayerModel *m_pPlayerModel;	//�v���C���[�̏��
	static CEnemyModel *m_pEnemyModel;		//�G�̏��
	static CModel *m_pModel;		//���f���̏��
	static CWall *m_pWall;			//�ǂ̏��
	static CField *m_pField;		//���̏��
	static CEdit *m_pEdit;			//�G�f�B�b�g�̏��
	static CBulletRemain *m_pBulletRemain;		//�c�e���̏��
	static CLife *m_pLife;			//�����\���̏��
	static CPause *m_pPause;		//�|�[�Y��ʂ̏��

	static bool m_bReset;				//���Z�b�g������
	static bool m_bPause;				//�|�[�Y��ʂ�

	static GAMEMODE m_gameMode;		//�Q�[�����[�h
	int m_nCntEnemy;				//�G�o���J�E���g
};

#endif

