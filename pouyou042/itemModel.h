//==============================================================
//
//�A�C�e������[itemModel.h]
//Author:����������
//
//==============================================================
#ifndef _ITEMMODEL_H_		//���̃}�N����`������Ă��Ȃ�������
#define _ITEMMODEL_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"objectX.h"

//���f���z�u�N���X�̒�`
class CItemModel : CObjectX
{
public:

	//�A�C�e���̎��
	typedef enum
	{
		TYPEITEM_NONE = 0,
		TYPEITEM_WATER,			//��
		TYPEITEM_ICE,			//�X
		TYPEITEM_VAPOR,			//���C
		TYPEITEM_LIFE,			//�̗͉�
		//TYPEITEM_KEY,			//�{�X��Q�`�Ԃ̂��߂̃L�[�A�C�e��
		TYPE_MAX
	} TYPEITEM;

	CItemModel();		//�R���X�g���N�^
	CItemModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CItemModel();		//�f�X�g���N�^

	static CItemModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(void);

	int GetItemType(void) { return m_type; }

private:

	static int m_nNumAll;			//���f���̎��

	static LPD3DXMESH m_pMesh;			//���b�V���i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;			//�}�e���A���̐�
	static const char *m_pFilename[TYPE_MAX];		//�t�@�C����

	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	int m_nMaxModel;			//���f���̐ݒu��
	int m_nIdx;					//���f���̔ԍ�

	int m_type;			//�A�C�e���̎��
};

#endif