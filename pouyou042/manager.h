//==============================================================
//
//�}�l�[�W������[manager.h]
//Author:����������
//
//==============================================================
#ifndef _MANAGER_H_		//���̃}�N����`������Ă��Ȃ�������
#define _MANAGER_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object.h"

//�O���錾
class CRenderer;		//�����_���[
class CInputKeyboard;	//�L�[�{�[�h����
class CInputJoyPad;		//�Q�[���p�b�h�̓���
class CPlayer;			//�v���C���[
class CEnemy;			//�G
class CSound;			//�T�E���h
class CCamera;			//�J����
class CLight;			//���C�g
class CDebugProc;		//�f�o�b�O�\��
class CTexture;			//�e�N�X�`��
class CMaterial;		//�}�e���A��
class CTitle;			//�^�C�g�����
class CTutorial;		//�`���[�g���A�����
class CGame;			//�Q�[�����
class CResult;			//���U���g���
class CRanking;			//�����L���O���
class CFade;			//�t�F�[�h

//�V�[���N���X�̒�`
class CScene : public CObject
{
public:

	//�Q�[�����[�h
	typedef enum
	{
		MODE_TITLE = 0,		//�^�C�g�����
		MODE_TUTORIAL,		//�`���[�g���A�����
		MODE_GAME,			//�Q�[�����
		MODE_RESULT,		//���U���g���
		MODE_RANKING,		//�����L���O���

	} MODE;

	CScene();
	CScene(MODE mode);
	~CScene();

	static CScene *Create(MODE mode);		//��������

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	virtual void Uninit(void);			//�I������
	virtual void Update(void);			//�X�V����
	virtual void Draw(void);			//�`�揈��
	MODE GetMode(void) { return m_mode; }			//���[�h�擾
	void SetMode(MODE mode) { m_mode = mode; }		//���[�h�ݒ�

	static CGame *GetGame(void) { return m_pGame; }		//�Q�[����ʎ擾
	static CRanking *GetRanking(void) { return m_pRanking; }		//�����L���O��ʎ擾

private:
	MODE m_mode;			//�Q�[�����[�h

	static CTitle *m_pTitle;			//�^�C�g����ʂ̏��
	static CTutorial *m_pTutorial;		//�`���[�g���A�����
	static CGame *m_pGame;				//�Q�[����ʂ̏��
	static CResult *m_pResult;			//���U���g��ʂ̏��
	static CRanking *m_pRanking;		//�����L���O��ʂ̏��
};

//�}�l�[�W���N���X�̒�`
class CManager
{
public:

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance,
		HWND hWnd,
		BOOL bWindow);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void ResetMap(void);	//�}�b�v�̍Đ���

	static CRenderer *GetRenderer(void) { return m_pRenderer; }		//�����_���[�̎擾
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }		//�L�[�{�[�h�̎擾
	static CInputJoyPad *GetInputJoyPad(void) { return m_pInputJoyPad; }			//�Q�[���p�b�h�̎擾
	static CTexture *GetTexture(void) { return m_pTexture; }		//�e�N�X�`���̎擾
	static CMaterial *GetMaterial(void) { return m_pMaterial; }		//�}�e���A���̎擾

	static CPlayer *GetPlayer(void) { return m_pPlayer; }			//�v���C���[�̎擾
	static CEnemy *GetEnemy(void) { return m_pEnemy; }				//�G�̏��
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }	//�f�o�b�O�\���̎擾
	static CSound *GetSound(void) { return m_pSound; }				//�T�E���h�̎擾

	static CCamera *GetCamera(void) { return m_pCamera; }			//�J�����̏��
	static CLight *GetLight(void) { return m_pLight; }				//���C�g�̏��
	static CScene *GetScene(void) { return m_pScene; }				//�V�[���̏��
	static CFade *GetFade(void) { return m_pFade; }					//�t�F�[�h�̏��

	static void SetMode(CScene::MODE mode);		//�Q�[�����[�h�ݒ�
	static CScene::MODE GetMode(void);			//�Q�[�����[�h�擾
	static void SetNumScore(int nNum) { m_nScore = nNum; }		//�X�R�A�̐ݒ�
	static int GetNumScore(void) { return m_nScore; }			//�X�R�A�̎擾
	static void SetBgm(bool bBgm) { m_bBgm = bBgm; }		//BGM�̐ݒ�
	static bool GetBgm(void) { return m_bBgm; }				//BGM�̎擾
	static void SetResult(bool bResult) { m_bResult = bResult; }	//���U���g�̔���̐ݒ�
	static bool GetResult(void) { return m_bResult; }				//���U���g�̔���擾

private:
	static CRenderer *m_pRenderer;		//�����_���[�̏��
	static CInputKeyboard *m_pInputKeyboard;	//�L�[�{�[�h�̏��
	static CInputJoyPad *m_pInputJoyPad;		//�Q�[���p�b�h�̏��
	static CTexture *m_pTexture;				//�e�N�X�`���̏��
	static CMaterial *m_pMaterial;		//�}�e���A���̏��

	static CPlayer *m_pPlayer;			//�v���C���[�̏��
	static CEnemy *m_pEnemy;			//�G�̏��
	static CSound *m_pSound;			//�T�E���h�̏��
	static CDebugProc *m_pDebugProc;	//�f�o�b�O�\���̏��

	static CCamera *m_pCamera;			//�J�����̏��
	static CLight *m_pLight;			//���C�g�̏��
	static CScene *m_pScene;			//�V�[���̏��
	static CFade *m_pFade;				//�t�F�[�h�̏��

	static int m_nScore;				//�X�R�A
	static bool m_bBgm;					//BGM�X�g�b�v���邩
	static bool m_bResult;				//���U���g�̔���
};

#endif
