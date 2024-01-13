//==============================================================
//
//�G�̏���[enemy.h]
//Author:����������
//
//==============================================================
#ifndef _ENEMY_H_		//���̃}�N����`������Ă��Ȃ�������
#define _ENEMY_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object2D.h"

//�}�N����`
#define WIDTH_ENEMY		(100.0f * 0.5f)		//�G�̉���
#define HEIGHT_ENEMY	(100.0f * 0.5f)		//�G�̏c��

//�G�N���X
class CEnemy : public CObject2D
{
public:
	CEnemy();	//�R���X�g���N�^
	~CEnemy();	//�f�X�g���N�^

	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	//D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_pos;		//�ʒu
};

#endif