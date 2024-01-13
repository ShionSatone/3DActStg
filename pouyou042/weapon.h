//==============================================================
//
//武器の種類表示処理[weapon.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _WEAPON_H_		//このマクロ定義がされていなかったら
#define _WEAPON_H_		//2重インクルード防止のマクロを定義する

#include "object.h"

//マクロ定義
#define NUM_WEAPON		(3)		//武器の種類

//前方宣言
class CObject2D;		//オブジェクト2D

//武器表示クラス
class CWeapon : public CObject
{
public:
	CWeapon();	//コンストラクタ
	~CWeapon();	//デストラクタ

	static CWeapon *Create(D3DXVECTOR3 pos);		//生成処理

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void);		//更新処理
	virtual void Draw(void);		//描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount);		//外部からテクスチャ指定

private:
	static CObject2D *m_apObject2D[NUM_WEAPON];		//オブジェクト2Dのポインタ

	static LPDIRECT3DTEXTURE9 m_pTexture[NUM_WEAPON];	//テクスチャへのポインタ
	int m_nIdxTexture[NUM_WEAPON];		//テクスチャの番号
	//D3DXVECTOR3 m_pos;			//位置

	//float m_aTexV[NUM_WEAPON];			//位置(縦)
	//float m_aTexU[NUM_WEAPON];			//位置(横)
	//D3DXVECTOR3 m_move[NUM_WEAPON];		//移動量
};

#endif
