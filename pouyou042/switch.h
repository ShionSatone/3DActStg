//==============================================================
//
//���e�X�C�b�`����[switch.h]
//Author:����������
//
//==============================================================
#ifndef _SWITCH_H_		//���̃}�N����`������Ă��Ȃ�������
#define _SWITCH_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"objectX.h"

//���e�X�C�b�`�N���X�̒�`
class CSwitch : CObjectX
{
public:

	CSwitch();		//�R���X�g���N�^
	CSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CSwitch();		//�f�X�g���N�^

	static CSwitch *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

private:

	static int m_nNumAll;			//���f���̎��

	static LPD3DXMESH m_pMesh;			//���b�V���i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;			//�}�e���A���̐�
	static const char *m_pFilename;		//�t�@�C����

	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	int m_nMaxModel;			//���f���̐ݒu��
	int m_nIdx;					//���f���̔ԍ�

	int m_type;			//�A�C�e���̎��
};

#endif