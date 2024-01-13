//==============================================================
//
//�e�̏���[bullet.h]
//Author:����������
//
//==============================================================
#ifndef _BULLET_H_		//���̃}�N����`������Ă��Ȃ�������
#define _BULLET_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "billboard.h"

//�e�N���X�̒�`
class CBullet : public CBillboard
{
public:

	CBullet();	//�R���X�g���N�^
	CBullet(int particleType);	//�R���X�g���N�^(�I�[�o�[���[�h)
	~CBullet();	//�f�X�g���N�^

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type, int particleType);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	bool Colision(D3DXVECTOR3 pos);		//�����蔻��
	bool ColisionBlockLeft(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock);		//�u���b�N�̓����蔻��(���S�F[����])
	bool ColisionBlockCenter(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock);	//�u���b�N�̓����蔻��(���S�F[����])
	bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld);		//���f���̓����蔻��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�ʒu(�O��)
	int m_nLife;			//�e��������܂ł̎���
	int m_nParticleLife;	//�p�[�e�B�N���̎���
	float m_fRadius;		//�e�̔��a
	TYPE m_type;			//�N�̒e��
	int m_particleType;	//�p�[�e�B�N���̎��
};

#endif