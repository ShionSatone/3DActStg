//==============================================================
//
//�u���b�N�̏���[block.h]
//Author:����������
//
//==============================================================
#ifndef _BLOCK_H_		//���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object2D.h"

//�u���b�N�N���X
class CBlock : public CObject2D
{
public:
	CBlock();	//�R���X�g���N�^
	~CBlock();	//�f�X�g���N�^

	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	void Set(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight);
	static bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight/*, Block **pBlock*/);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	//D3DXVECTOR3 m_move;		//�ړ���
	static D3DXVECTOR3 m_pos;	//�ʒu
	static float m_fWidth;		//��
	static float m_fHeight;		//����
	int m_nType;			//���
	int m_nCounterMove;	//�u���b�N�̓����̃J�E���^�[
};

#endif