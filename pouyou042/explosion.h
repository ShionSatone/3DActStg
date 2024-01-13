//==============================================================
//
//爆発の処理[explosion.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _EXPLOSION_H_		//このマクロ定義がされていなかったら
#define _EXPLOSION_H_		//2重インクルード防止のマクロを定義する

#include "billboard.h"

//プレイヤークラス
class CExplosion : public CBillboard
{
public:
	CExplosion();	//コンストラクタ
	~CExplosion();	//デストラクタ

	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの破棄
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	int m_nIdxTexture;		//テクスチャの番号

	D3DXVECTOR3 m_pos;		//位置
	int m_nCntdest;			//爆発が消えるまでの時間
	int m_nCounterAnim;
	int m_nPatternAnim;
};

#endif