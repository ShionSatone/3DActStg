//==============================================================
//
//多重背景処理[bgmulti.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _BGMULTI_H_		//このマクロ定義がされていなかったら
#define _BGMULTI_H_		//2重インクルード防止のマクロを定義する

#include "object.h"

//マクロ定義
#define NUM_BG		(3)		//背景の数

//前方宣言
class CObject2D;		//オブジェクト2D

//多重背景クラス
class CBgMulti : public CObject
{
public:
	CBgMulti();	//コンストラクタ
	~CBgMulti();	//デストラクタ

	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの破棄
	static CBgMulti *Create(void);		//生成処理

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void);		//更新処理
	virtual void Draw(void);		//描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture, int nCount);		//外部からテクスチャ指定

private:
	static CObject2D *m_apObject2D[NUM_BG];		//オブジェクト2Dのポインタ

	static LPDIRECT3DTEXTURE9 m_pTexture[NUM_BG];	//テクスチャへのポインタ
	int m_nIdxTexture[NUM_BG];		//テクスチャの番号

	float m_aTexV[NUM_BG];			//位置(縦)
	float m_aTexU[NUM_BG];			//位置(横)
	D3DXVECTOR3 m_move[NUM_BG];		//移動量
};

#endif
