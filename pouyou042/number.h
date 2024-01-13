//==============================================================
//
//��������[number.h]
//Author:����������
//
//==============================================================
#ifndef _NUMBER_H_		//���̃}�N����`������Ă��Ȃ�������
#define _NUMBER_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�����N���X
class CNumber : public CObject
{
public:
	CNumber();	//�R���X�g���N�^
	//CNumber(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�R���X�g���N�^�i�I�[�o�[���[�h�j
	~CNumber();	//�f�X�g���N�^

	static CNumber *Create(void);		//��������

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual void Draw(void);		//�`�揈��

	void BindTexture(int nIdxTexture);		//�O������e�N�X�`���w��
	void SetSize(float fWidth, float fHeight) { m_fHeight = fHeight; m_fWidth = fWidth; }	//�I�u�W�F�N�g�̃T�C�Y�ݒ�

	void SetTex(TYPE type, int nPatternAnim, float nDigitX);		//�A�j���[�V����
	void SetType(float fTexU, float fTexV);			//���d�w�i

	void SetPosition(TYPE type, D3DXVECTOR3 pos, float fWidth, float fHeight);	//�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//�ʒu�擾
	void SetColor(TYPE type, D3DXCOLOR col);		//�F�ݒ�
	D3DXCOLOR GetColor(void) { return m_col; }		//�F�擾

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXCOLOR m_col;		//�F
	float m_fHeight;		//�c��
	float m_fWidth;			//����
	TYPE m_type;			//���
};

#endif
