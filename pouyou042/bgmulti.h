//==============================================================
//
//���d�w�i����[bgmulti.h]
//Author:����������
//
//==============================================================
#ifndef _BGMULTI_H_		//���̃}�N����`������Ă��Ȃ�������
#define _BGMULTI_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�}�N����`
#define NUM_BG		(3)		//�w�i�̐�

//�O���錾
class CObject2D;		//�I�u�W�F�N�g2D

//���d�w�i�N���X
class CBgMulti : public CObject
{
public:
	CBgMulti();	//�R���X�g���N�^
	~CBgMulti();	//�f�X�g���N�^

	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��
	static CBgMulti *Create(void);		//��������

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual void Draw(void);		//�`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount);		//�O������e�N�X�`���w��

private:
	static CObject2D *m_apObject2D[NUM_BG];		//�I�u�W�F�N�g2D�̃|�C���^

	static LPDIRECT3DTEXTURE9 m_pTexture[NUM_BG];	//�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture[NUM_BG];		//�e�N�X�`���̔ԍ�

	float m_aTexV[NUM_BG];			//�ʒu(�c)
	float m_aTexU[NUM_BG];			//�ʒu(��)
	D3DXVECTOR3 m_move[NUM_BG];		//�ړ���
};

#endif
