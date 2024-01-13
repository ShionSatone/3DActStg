//==============================================================
//
//残弾数表示処理[bulletRemain.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _BULLETREMAIN_H_		//このマクロ定義がされていなかったら
#define _BULLETREMAIN_H_		//2重インクルード防止のマクロを定義する

#include "object2D.h"

//残弾数クラス
class CBulletRemain : public CObject2D
{
public:
	CBulletRemain();	//コンストラクタ
	CBulletRemain(D3DXVECTOR3 pos);	//コンストラクタ(オーバーロード)
	~CBulletRemain();	//デストラクタ

	static CBulletRemain *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	void SetNumBullet(int nNumBullet);		//弾消費数設定
	int GetNumBullet(void) { return m_nNumBullet; }							//弾消費数取得

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//テクスチャの番号

	D3DXVECTOR3 m_pos;		//位置
	int m_nNumBullet;		//弾消費数
	int m_nCntLife;			//体力減らすカウンター
};

#endif