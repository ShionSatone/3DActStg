//==============================================================
//
//�����̏���[explosion.h]
//Author:����������
//
//==============================================================
#ifndef _EXPLOSION_H_		//���̃}�N����`������Ă��Ȃ�������
#define _EXPLOSION_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "billboard.h"

//�v���C���[�N���X
class CExplosion : public CBillboard
{
public:
	CExplosion();	//�R���X�g���N�^
	~CExplosion();	//�f�X�g���N�^

	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_pos;		//�ʒu
	int m_nCntdest;			//������������܂ł̎���
	int m_nCounterAnim;
	int m_nPatternAnim;
};

#endif