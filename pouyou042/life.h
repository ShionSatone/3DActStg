//==============================================================
//
//体力表示処理[life.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _LIFE_H_		//このマクロ定義がされていなかったら
#define _LIFE_H_		//2重インクルード防止のマクロを定義する

#include "object2D.h"

#define NUM_LIFE_FRAME		(2)		//枠組みの数

class CObject2D;		//オブジェクト2Dの情報

//体力クラス
class CLife : public CObject
{
public:
	CLife();	//コンストラクタ
	CLife(D3DXVECTOR3 pos);	//コンストラクタ(オーバーロード)
	~CLife();	//デストラクタ

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	void SetMax(int nMaxLife) { m_nMaxLife = nMaxLife; }			//体力設定
	void SetNum(int nNumBullet);		//体力消費数設定
	void SetNumCon(int nNumCon) { m_nNumCon = nNumCon; }			//消費初期値設定
	int GetNum(void) { return m_nNumCon; }							//体力消費数取得
	int GetMax(void) { return (m_nMaxLife - m_nNumCon); }

private:
	static CObject2D *m_apObject2D[NUM_LIFE_FRAME];		//オブジェクト2Dの情報
	int m_nIdxTexture[NUM_LIFE_FRAME];		//テクスチャの番号


	D3DXVECTOR3 m_pos;		//位置
	int m_nNumCon;			//体力消費数
	int m_nMaxLife;			//最大体力
};

#endif