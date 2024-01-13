//==============================================================
//
//ブロックの処理[block.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _BLOCK_H_		//このマクロ定義がされていなかったら
#define _BLOCK_H_		//2重インクルード防止のマクロを定義する

#include "object2D.h"

//ブロッククラス
class CBlock : public CObject2D
{
public:
	CBlock();	//コンストラクタ
	~CBlock();	//デストラクタ

	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの破棄
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	void Set(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight);
	static bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight/*, Block **pBlock*/);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//テクスチャの番号

	//D3DXVECTOR3 m_move;		//移動量
	static D3DXVECTOR3 m_pos;	//位置
	static float m_fWidth;		//幅
	static float m_fHeight;		//高さ
	int m_nType;			//種類
	int m_nCounterMove;	//ブロックの動きのカウンター
};

#endif