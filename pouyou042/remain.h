//==============================================================
//
//�c�@����[remain.h]
//Author:����������
//
//==============================================================
#ifndef _REMAIN_H_		//���̃}�N����`������Ă��Ȃ�������
#define _REMAIN_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object2D.h"

//�c�@�N���X
class CRemain : public CObject2D
{
public:
	CRemain();	//�R���X�g���N�^
	~CRemain();	//�f�X�g���N�^

	static CRemain *Create(D3DXVECTOR3 pos, int nIdx);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	void SetMax(int nMaxRemain) { m_nNum = nMaxRemain; }		//�c�@�̍ő吔
	int GetNum(void) { return m_nNum; }							//�c�@

private:
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	static int m_nNum;		//�c�@�̐�
	D3DXVECTOR3 m_pos;		//�ʒu
};

#endif