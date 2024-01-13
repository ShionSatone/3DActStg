//==============================================================
//
//����̎�ޕ\������[weapon.h]
//Author:����������
//
//==============================================================
#ifndef _WEAPON_H_		//���̃}�N����`������Ă��Ȃ�������
#define _WEAPON_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�}�N����`
#define NUM_WEAPON		(3)		//����̎��

//�O���錾
class CObject2D;		//�I�u�W�F�N�g2D

//����\���N���X
class CWeapon : public CObject
{
public:
	CWeapon();	//�R���X�g���N�^
	~CWeapon();	//�f�X�g���N�^

	static CWeapon *Create(D3DXVECTOR3 pos);		//��������

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual void Draw(void);		//�`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount);		//�O������e�N�X�`���w��

private:
	static CObject2D *m_apObject2D[NUM_WEAPON];		//�I�u�W�F�N�g2D�̃|�C���^

	static LPDIRECT3DTEXTURE9 m_pTexture[NUM_WEAPON];	//�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture[NUM_WEAPON];		//�e�N�X�`���̔ԍ�
	//D3DXVECTOR3 m_pos;			//�ʒu

	//float m_aTexV[NUM_WEAPON];			//�ʒu(�c)
	//float m_aTexU[NUM_WEAPON];			//�ʒu(��)
	//D3DXVECTOR3 m_move[NUM_WEAPON];		//�ړ���
};

#endif
