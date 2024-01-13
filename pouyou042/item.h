//==============================================================
//
//アイテム処理[item.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _ITEM_H_		//このマクロ定義がされていなかったら
#define _ITEM_H_		//2重インクルード防止のマクロを定義する

#include "object2D.h"

//敵クラス
class CItem : public CObject2D
{
public:
	CItem();	//コンストラクタ
	~CItem();	//デストラクタ

	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの破棄
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	bool ColisionPlayer(D3DXVECTOR3 pos);		//プレイヤーとの当たり判定

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//テクスチャの番号

	D3DXVECTOR3 m_pos;		//位置
};

#endif