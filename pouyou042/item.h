//==============================================================
//
//�A�C�e������[item.h]
//Author:����������
//
//==============================================================
#ifndef _ITEM_H_		//���̃}�N����`������Ă��Ȃ�������
#define _ITEM_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object2D.h"

//�G�N���X
class CItem : public CObject2D
{
public:
	CItem();	//�R���X�g���N�^
	~CItem();	//�f�X�g���N�^

	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	bool ColisionPlayer(D3DXVECTOR3 pos);		//�v���C���[�Ƃ̓����蔻��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_pos;		//�ʒu
};

#endif