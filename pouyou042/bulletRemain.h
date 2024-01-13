//==============================================================
//
//�c�e���\������[bulletRemain.h]
//Author:����������
//
//==============================================================
#ifndef _BULLETREMAIN_H_		//���̃}�N����`������Ă��Ȃ�������
#define _BULLETREMAIN_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object2D.h"

//�c�e���N���X
class CBulletRemain : public CObject2D
{
public:
	CBulletRemain();	//�R���X�g���N�^
	CBulletRemain(D3DXVECTOR3 pos);	//�R���X�g���N�^(�I�[�o�[���[�h)
	~CBulletRemain();	//�f�X�g���N�^

	static CBulletRemain *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	void SetNumBullet(int nNumBullet);		//�e����ݒ�
	int GetNumBullet(void) { return m_nNumBullet; }							//�e����擾

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_pos;		//�ʒu
	int m_nNumBullet;		//�e���
	int m_nCntLife;			//�̗͌��炷�J�E���^�[
};

#endif